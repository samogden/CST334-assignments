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
    .num_readers = 0,
    .num_writers = 0
  };
  pthread_mutex_init(&q.mutex, NULL);
  pthread_cond_init(&q.can_write, NULL);
  pthread_cond_init(&q.can_read, NULL);
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


int _push(Queue* q, char* item) {
  if (is_full(q)) {
    return -1;
  }
  q->entries[q->head] = item;
  q->head = (q->head + 1) % QUEUE_SIZE;
  return q->head - q->tail % QUEUE_SIZE;
}

int push(Queue* q, char* item) {
  pthread_mutex_lock(&q->mutex);
  while (
    is_full(q)
    || q->num_writers >= 1
    || q->num_readers >= 1
  ) {
    log_debug("Ouch...\n");
    pthread_mutex_unlock(&q->mutex);
    pthread_mutex_lock(&q->mutex);
    pthread_cond_wait(&q->can_write, &q->mutex);
  }
  q->num_writers++;
  pthread_mutex_unlock(&q->mutex);

  int return_val = _push(q, item);


  pthread_mutex_lock(&q->mutex);
  q->num_writers--;
  pthread_cond_signal(&q->can_read);
  pthread_cond_signal(&q->can_write);
  pthread_mutex_unlock(&q->mutex);
  return return_val;
}

char* _pop(Queue* q) {
  log_debug("Pop!\n");
  if (is_empty(q)) {
    return NULL;
  }
  char* return_val = q->entries[q->tail];
  q->tail = (q->tail + 1) % QUEUE_SIZE;
  return return_val;
}

char* pop(Queue* q) {
  pthread_mutex_lock(&q->mutex);
  while (
    is_empty(q)
    || q->num_writers >= 1
    || q->num_readers >= 1
  ) {
    pthread_mutex_unlock(&q->mutex);
    pthread_mutex_lock(&q->mutex);
    pthread_cond_wait(&q->can_read, &q->mutex);
  }
  q->num_readers++;
  pthread_mutex_unlock(&q->mutex);

  char* return_val = _pop(q);

  pthread_mutex_lock(&q->mutex);
  q->num_readers--;
  pthread_cond_signal(&q->can_write);
  pthread_cond_signal(&q->can_read);
  pthread_mutex_unlock(&q->mutex);
  return return_val;
}

void print_queue(Queue* q) {
  for (int i = q->tail; i < get_size(q); i++) {
    printf("%d -> %s\n", i - q->tail, q->entries[i % QUEUE_SIZE]);
  }
}