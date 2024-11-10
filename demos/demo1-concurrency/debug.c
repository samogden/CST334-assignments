#include "src/queue.h"

#include <stddef.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_TO_ADD 10000

typedef struct add_args_t {
  Queue* q;
  unsigned int val;
} add_args_t;

void* add_item_wrapper(void* add_args) {
  Queue* q = ((add_args_t*)add_args)->q;
  unsigned int val = ((add_args_t*)add_args)->val;

  add_item(q, val);
  printf("size: %d\n", get_size(q));

  return NULL;
}

int main() {

  Queue q = init_queue();
  pthread_t threads[NUM_TO_ADD];
  add_args_t args[NUM_TO_ADD];

  for (unsigned int i = 0; i < NUM_TO_ADD; i++) {
    args[i].q = &q;
    args[i].val = i;

    // add_item_wrapper(&args);
    pthread_create(
      &threads[i],
      NULL,
      add_item_wrapper,
      &args[i]
    );
  }
  for (int i = 0; i < NUM_TO_ADD; i++) {
    // catch all our threads
    pthread_join(threads[i], NULL);
  }
  print_queue(&q);

  return 0;
}
