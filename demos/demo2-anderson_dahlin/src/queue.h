//
// Created by Sam Ogden on 11/14/23.
//

#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include <stdbool.h>
#include "pthread.h"

#define QUEUE_SIZE 16

typedef struct Queue {
  // Data variable
  char* entries[QUEUE_SIZE];
  int head;
  int tail;

  // State variables
  int num_readers;
  int num_writers;

  pthread_mutex_t mutex;
  pthread_cond_t can_write;
  pthread_cond_t can_read;
} Queue;

Queue init_queue();

int get_size(Queue* q);
bool is_full(Queue* q);
bool is_empty(Queue* q);

int push(Queue* q, char* item);
char* pop(Queue* q);

void print_queue(Queue* q);


#endif //WORK_QUEUE_H
