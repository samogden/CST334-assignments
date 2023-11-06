//
// Created by Sam Ogden on 11/6/23.
//

#include "queue.h"
#include "stdio.h"


Queue init_queue() {
  Queue q = {
    .head = 0,
    .tail = 0,
  };
  return q;
}

int get_size(Queue* q) {
  return (q->head - q->tail) % QUEUE_SIZE;
}

bool is_full(Queue* q) {
  return ((q->head + 1) % QUEUE_SIZE) == q->tail;
}
bool is_empty(Queue* q) {
  return (q->head == q->tail);
}

int add_item(Queue* q, int item) {
  if (is_full(q)) {
    return -1;
  }
  q->entries[q->head] = item;
  q->head = q->head + 1 % QUEUE_SIZE;
  return q->head - q->tail % QUEUE_SIZE;
}

int get_item(Queue* q, int item) {
  if (is_empty(q)) {
    return -1;
  }
  int return_val = q->entries[q->tail];
  q->tail = q->tail + 1 % QUEUE_SIZE;
  return return_val;
}

void print_queue(Queue* q) {
  for (int i = q->tail; i < get_size(q); i++) {
    printf("%d -> %d\n", i - q->tail, q->entries[i % QUEUE_SIZE]);
  }
}

