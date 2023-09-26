//
// Created by Sam Ogden on 8/7/23.
//

#include "process.h"

#include "stdlib.h"
#include "stdbool.h"

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H
#define CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H

#define MAX_NUMBER_PROCESSES 256

typedef struct PROCESS_LIST {
    PROCESS** processes;
    int num_processes;
    int last_used;
} PROCESS_LIST;

PROCESS_LIST* create_process_list();
bool is_empty(PROCESS_LIST* pl);

void add_process_to_tail(PROCESS_LIST* pl, PROCESS* p); // Adds a new process to the end of the list
void add_process_to_head(PROCESS_LIST* pl, PROCESS* p); // Adds a new process to the end of the list
void remove_process(PROCESS_LIST* pl, PROCESS* p); // Removes a process from the list

void print_contents(PROCESS_LIST* pl);

PROCESS* get_last_used(PROCESS_LIST* pl);
PROCESS* get_next(PROCESS_LIST* pl);
PROCESS* get_prev(PROCESS_LIST* pl);
PROCESS* get_minimum(PROCESS_LIST* pl, int (*compare_function)(PROCESS, PROCESS));

void mark_last_used(PROCESS_LIST*pl, PROCESS* p);
PROCESS_LIST* copy_only_entered_processes(PROCESS_LIST* all_processes, float curr_time);


#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H
