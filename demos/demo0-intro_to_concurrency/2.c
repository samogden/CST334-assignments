#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
pthread_mutex_t mutex;


void* add_to_counter(void* arg) {
  printf("%s: begin\n", (char*) arg);
  int i;
  pthread_mutex_lock(&mutex);
  for (i = 0; i < 1e7; i++) {
    counter++;
  }
  pthread_mutex_unlock(&mutex);
  printf("%s: done\n", (char*) arg);
  return NULL;
}

#define NUM_THREADS 4

int main(int argc, char* argv[]) {

  pthread_t* p[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);

  printf("main: begin (counter = %d)\n", counter);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(
      &p[i],
      NULL,
      add_to_counter,
      "A" + i
    );
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(p[i], NULL);
  }
  printf("main: done with both (counter = %d)\n", counter);
  return 0;
}


