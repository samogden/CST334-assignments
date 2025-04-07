#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>

#define NUM_THREADS 20
#define fsleep(seconds) usleep((unsigned int)((seconds) * 1000000))

#define INITIAL_SEMAPHORE_VALUE 0
sem_t semaphores[NUM_THREADS];

typedef struct args_t {
  int thread_number;
}
args_t;

void* THREAD_FUNCTION(void* args) {
  int thread_number = ((args_t*)args)->thread_number;
  fsleep(0.00000001); // Do something slow
  printf("%c1\n", 'A' + thread_number);

  for (int i = 0; i < NUM_THREADS; i++) {
    if (i == thread_number) continue;
    sem_post(&semaphores[thread_number]);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    if (i == thread_number) continue;
    printf("%c1: wait on %c\n", 'A' + thread_number, 'A' + i);
    sem_wait(&semaphores[i]);
  }
  printf("%c2\n", 'A' + thread_number);
  return NULL;
}

int main() {

  pthread_t threads[NUM_THREADS];
  args_t args[NUM_THREADS];

  for (int i = 0; i< NUM_THREADS; i++) {
    sem_init(&semaphores[i], 0, INITIAL_SEMAPHORE_VALUE);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].thread_number = i;
    pthread_create(&threads[i], NULL, THREAD_FUNCTION, &args[i]);
  }
  for (char i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[(size_t)i], NULL);
  }

  return 0;
}
