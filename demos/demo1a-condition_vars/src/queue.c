//
// Created by Sam Ogden on 11/6/23.
//

#include "queue.h"
#include "stdio.h"
#include <stdlib.h>


Queue init_queue() {
  Queue q = {
    .head = 0,
    .tail = 0,
  };
  q.mutex = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(q.mutex, NULL);
  return q;
}

int _get_size(Queue* q) {
  return (q->head - q->tail) % QUEUE_SIZE;
}

int get_size(Queue* q) {
  pthread_mutex_lock(q->mutex);
  int return_val = _get_size(q);
  pthread_mutex_unlock(q->mutex);
  return return_val;
}


bool is_full(Queue* q) {
  return ((q->head + 1) % QUEUE_SIZE) == q->tail;
}
bool is_empty(Queue* q) {
  return (q->head == q->tail);
}

int _add_item(Queue* q, int item) {
  if (is_full(q)) {
    return -1;
  }
  q->entries[q->head] = item;
  q->head = q->head + 1 % QUEUE_SIZE;
  return _get_size(q);
}

int _get_item(Queue* q) {
  if (is_empty(q)) {
    return -1;
  }
  int return_val = q->entries[q->tail];
  q->tail = q->tail + 1 % QUEUE_SIZE;
  return return_val;
}


int add_item(Queue* q, int item) {
  pthread_mutex_lock(q->mutex);

  int return_val = _add_item(q, item);

  pthread_mutex_unlock(q->mutex);
  return return_val;
}


int get_item(Queue* q) {
  pthread_mutex_lock(q->mutex);

  int return_val = _get_item(q);

  pthread_mutex_unlock(q->mutex);
  return return_val;
}

void print_queue(Queue* q) {
  for (int i = q->tail; i < get_size(q); i++) {
    printf("%d -> %d\n", i - q->tail, q->entries[i % QUEUE_SIZE]);
  }}

