#include "src/queue.h"

#include <stddef.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_TO_ADD 10

typedef struct args_t {
  Queue* q;
  unsigned int val;
} args_t;

void* add_item_wrapper(void* args) {
  Queue* q = ((args_t*)args)->q;
  unsigned int val = ((args_t*)args)->val;

  add_item(q, val);
  printf("size: %d\n", get_size(q));

  return NULL;
}

void* get_item_wrapper(void* args) {
  Queue* q = ((args_t*)args)->q;

  int item = get_item(q);
  printf("item: %d\n", item);

  return NULL;
}

int main() {

  Queue q = init_queue();
  pthread_t threads[NUM_TO_ADD];
  args_t args[NUM_TO_ADD];

  for (unsigned int i = 0; i < NUM_TO_ADD; i++) {
    args[i].q = &q;
    args[i].val = i;

    // add_item_wrapper(&args);
    if (i > ((NUM_TO_ADD/2))) {
      pthread_create(
        &threads[i],
        NULL,
        add_item_wrapper,
        &args[i]
      );
    } else {
      pthread_create(
        &threads[i],
        NULL,
        get_item_wrapper,
        &args[i]
      );

    }
  }
  for (int i = 0; i < NUM_TO_ADD; i++) {
    // catch all our threads
    pthread_join(threads[i], NULL);
  }
  print_queue(&q);

  return 0;
}
