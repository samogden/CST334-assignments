#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>

#define NUM_THREADS 2
#define INITIAL_SEMAPHORE_VALUE 0

sem_t semaphores[NUM_THREADS];
sem_t semA;
sem_t semB;

volatile int counter = 0;

typedef struct args_t {
  int thread_number;
}
args_t;

void* A(void* args) {
  usleep(rand() % 10000); // Do something slow

  // A1
  printf("%c1\n", 'A');

  // todo

  // A2
  printf("%c2\n", 'A');
  return NULL;
}

void* B(void* args) {
  usleep(rand() % 10000); // Do something slow

  // A1
  printf("%c1\n", 'B');

  // todo

  // A2
  printf("%c2\n", 'B');
  return NULL;
}

void* GENERIC_THREAD_FUNCTION(void* args) {
  int thread_number = ((args_t*)args)->thread_number;
  usleep(rand() % 10000); // Do something slow

  // STEP 1
  printf("%c1\n", 'A' + thread_number);

  // Todo!

  // STEP 2
  printf("%c2\n", 'A' + thread_number);
  return NULL;
}

void run_AB() {

  sem_init(&semA, 0, INITIAL_SEMAPHORE_VALUE);
  sem_init(&semB, 0, INITIAL_SEMAPHORE_VALUE);

  pthread_t threadA, threadB;

  pthread_create(&threadA, NULL, A, NULL);
  pthread_create(&threadB, NULL, B, NULL);

  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);
}

void run_many() {
  pthread_t threads[NUM_THREADS];
  args_t args[NUM_THREADS];

  // Initialize Semaphore
  for (int i = 0; i< NUM_THREADS; i++) {
    sem_init(&semaphores[i], 0, INITIAL_SEMAPHORE_VALUE);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].thread_number = i;
    pthread_create(&threads[i], NULL, GENERIC_THREAD_FUNCTION, &args[i]);
    sleep(1);
  }
  for (char i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[(size_t)i], NULL);
  }
}

int main() {

  run_AB();

  return 0;
}
