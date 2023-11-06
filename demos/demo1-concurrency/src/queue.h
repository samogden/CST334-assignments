//
// Created by Sam Ogden on 11/6/23.
//

#ifndef LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H
#define LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H

#include <stdbool.h>

#define QUEUE_SIZE 16


typedef struct Queue {
  unsigned int entries[QUEUE_SIZE];
  int head;
  int tail;
} Queue;

Queue init_queue();

int get_size(Queue* q);
bool is_full(Queue* q);
bool is_empty(Queue* q);

int add_item(Queue* q, int item);
int get_item(Queue* q, int item);

void print_queue(Queue* q);

#endif //LAB6_CONCURRENT_LINKED_LISTS_QUEUE_H
