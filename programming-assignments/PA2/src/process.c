//
// Created by Sam Ogden on 8/7/23.
//

#include "process.h"

#include "stdlib.h"
#include "stdio.h"

unsigned int next_id = 0;

PROCESS* create_process(float length, unsigned int priority, float entry_time) {

    // First, create_process a new object using malloc
    PROCESS* p = malloc(sizeof(PROCESS));

    // Next, set the fields of the object
    p->id = next_id++;
    p->length = length;
    p->process_state = PROC_READY;
    p->priority = priority;
    p->entry_time = entry_time;
    p->time_remaining = length;

    return p;
}

void delete_process(PROCESS* process) {
    free(process);
}

void describe_process(PROCESS* p) {
    printf("p->id: %d\n", p->id);
    printf("p->length: %f\n", p->length);
    printf("p->priority: %d\n", p->priority);
    printf("p->entry_time: %f\n", p->entry_time);
    printf("p->time_remaining: %f\n", p->time_remaining);
}