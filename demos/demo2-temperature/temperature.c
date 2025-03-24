#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_API_READER_THREADS 12
#define fsleep(seconds) usleep((unsigned int)((seconds) * 1000000))

volatile int temperature;
pthread_mutex_t mutex;
pthread_cond_t temperature_changed;

void *API_provider(void* threadid) {
  int sensed_temp;
  
  // Loop forever
  while (true) {
    // Generate a random, reasonable, temperature
    sensed_temp = 70 + rand() % 5;
    
    // Lock before we get to the critical section
    pthread_mutex_lock(&mutex);
    printf("API_provider: sense_temp = %d\n", sensed_temp);
    temperature = sensed_temp;
    pthread_cond_broadcast(&temperature_changed);
    pthread_mutex_unlock(&mutex);
    
    // Sleep because we don't need to 
    // update the temperature 100 million 
    // times per second
    fsleep(1);
  }
}

void *API_reader__polling(void* threadid) {
  // Loop forever
  while (true) {
    // Lock before we grab the new value (critical section)
    pthread_mutex_lock(&mutex);
    printf("Reader(%02ld) current temp: %d\n", (long)threadid, temperature);
    pthread_mutex_unlock(&mutex);
    fsleep(0.5);
  }
}

void *API_reader__cv(void *threadid) {
  // Loop forever
  while (true) {
    // Lock for the critical section
    pthread_mutex_lock(&mutex);
    // Wait until the temperature is changed
    pthread_cond_wait(&temperature_changed, &mutex);
    printf("Reader(%02ld) current temp: %d\n", (long)threadid, temperature);
    // Unlock
    pthread_mutex_unlock(&mutex);
 }
}

int main() {

  // init our concurrency primatives
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&temperature_changed, NULL);

  // Start API writer thread
  pthread_t api_writer_thread;
  pthread_create(&api_writer_thread, NULL, API_provider, NULL);

  // Start all the reader threads
  pthread_t reader_thread[NUM_API_READER_THREADS];
  for (long i = 0; i < NUM_API_READER_THREADS; i++) {
    pthread_create(&reader_thread[i], NULL, API_reader__polling, (void*)i);
  }
  
  // Wait forever (since this will be running in the background)
  pthread_join(api_writer_thread, NULL);

  return 0;
}
