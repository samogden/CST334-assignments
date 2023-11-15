//
// Created by Sam Ogden on 11/14/23.
//

#ifndef WORK_QUEUE_H
#define WORK_QUEUE_H

#include <stdbool.h>

#define QUEUE_SIZE 16

typedef struct Queue {
  char* entries[QUEUE_SIZE];
  int head;
  int tail;
} Queue;

Queue init_queue();

int get_size(Queue* q);
bool is_full(Queue* q);
bool is_empty(Queue* q);

int push(Queue* q, char* item);
char* pop(Queue* q);

void print_queue(Queue* q);


#endif //WORK_QUEUE_H
