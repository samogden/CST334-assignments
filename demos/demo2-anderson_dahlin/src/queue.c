//
// Created by Sam Ogden on 11/14/23.
//

#include "queue.h"
#include <stdio.h>
#include "server.h"


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

int push(Queue* q, char* item) {
  if (is_full(q)) {
    return -1;
  }
  q->entries[q->head] = item;
  q->head = (q->head + 1) % QUEUE_SIZE;
  return q->head - q->tail % QUEUE_SIZE;
}

char* pop(Queue* q) {
  if (is_empty(q)) {
    return NULL;
  }
  char* return_val = q->entries[q->tail];
  q->tail = (q->tail + 1) % QUEUE_SIZE;
  return return_val;
}

void print_queue(Queue* q) {
  for (int i = q->tail; i < get_size(q); i++) {
    printf("%d -> %d\n", i - q->tail, q->entries[i % QUEUE_SIZE]);
  }
}