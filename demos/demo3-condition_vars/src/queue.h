//
// Created by Sam Ogden on 11/6/23.
//

#ifndef LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H
#define LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H

#include <stdbool.h>
#include <pthread.h>

#define QUEUE_SIZE 10

typedef struct Queue {
  unsigned int entries[QUEUE_SIZE];
  int head;
  int tail;
  pthread_mutex_t* mutex;
} Queue;

Queue init_queue();

int get_size(Queue* q);
bool is_full(Queue* q);
bool is_empty(Queue* q);

int add_item(Queue* q, int item);
int get_item(Queue* q);

void print_queue(Queue* q);

#endif //LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H
