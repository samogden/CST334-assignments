#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>

/*
 * Stolen from an LLM
 */
// Initialize macro
#define sem_init_wrapper(sem, value) sem_init(&(sem), 0, value)

// Method-like macros
#define sem_wait_method(sem) sem_wait(&(sem))
#define sem_post_method(sem) sem_post(&(sem))

// Optional: Define a "dot" operator for more OO-like syntax
#define init(sem, value) sem_init_wrapper(sem, value)
#define wait(sem) sem_wait_method(sem)
#define signal(sem) sem_post_method(sem)

#define print_sem_value(sem) do { \
    int temp_val; \
    sem_getvalue(&(sem), &temp_val); \
    printf("Semaphore %s = %d\n", #sem, temp_val); \
} while(0)
/* End of stolen code */


#define NUM_THREADS 26
#define INITIAL_SEMAPHORE_VALUE 0

sem_t semaphores[NUM_THREADS];
sem_t semA;
sem_t semB;

typedef struct barrier_t {
  int N; // number of threads
  int count; // how many have arrived
  sem_t lock;
  sem_t barrier;
}barrier_t;

barrier_t my_first_barrier;

volatile int counter = 0;

typedef struct args_t {
  int thread_number;
}
args_t;

void* A(void* args) {
  usleep(rand() % 10000); // Do something slow

  // A1
  printf("A1\n");

  signal(semA);
  wait(semB);

  // A2
  printf("A2\n");
  return NULL;
}

void* B(void* args) {
  usleep(rand() % 10000); // Do something slow

  // A1
  printf("B1\n");

  signal(semB);
  wait(semA);

  // A2
  printf("B2\n");
  return NULL;
}

void* GENERIC_THREAD_FUNCTION(void* args) {
  int thread_number = ((args_t*)args)->thread_number;
  usleep(rand() % 10000); // Do something slow

  int curr_val;

  // STEP 1
  printf("%c1 rendezvous\n", 'A' + thread_number);

  // STOP ALL THREADS HERE


  // STEP 2
  printf("%c2 critical\n", 'A' + thread_number);

  return NULL;
}

void run_AB() {

  init(semA, 1);
  init(semB, 1);

  pthread_t threadA, threadB;

  pthread_create(&threadA, NULL, A, NULL);
  pthread_create(&threadB, NULL, B, NULL);

  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);
}

void run_many() {
  pthread_t threads[NUM_THREADS];
  args_t args[NUM_THREADS];

  Initialize Semaphore
  for (int i = 0; i< NUM_THREADS; i++) {
    init(semaphores[i], INITIAL_SEMAPHORE_VALUE);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].thread_number = i;
    pthread_create(&threads[i], NULL, GENERIC_THREAD_FUNCTION, &args[i]);
  }
  for (char i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[(size_t)i], NULL);
  }
}

int main() {

  run_AB();
  // run_many();
  // printf("-------\n");
  // run_many();

  return 0;
}
