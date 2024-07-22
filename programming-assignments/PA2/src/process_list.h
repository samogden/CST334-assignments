
#include "process.h"

#include "stdlib.h"
#include "stdbool.h"

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H
#define CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H

#define MAX_NUMBER_PROCESSES 256

typedef struct PROCESS_LIST {
    PROCESS** processes;
    int num_processes;
} PROCESS_LIST;

PROCESS_LIST* create_process_list();
void delete_process_list(PROCESS_LIST* pl);

bool is_empty(PROCESS_LIST* pl);

void add_process_to_tail(PROCESS_LIST* pl, PROCESS* p); // Adds a new process to the end of the list
void add_process_to_head(PROCESS_LIST* pl, PROCESS* p); // Adds a new process to the end of the list
void remove_process(PROCESS_LIST* pl, PROCESS* p); // Removes a process from the list

void print_contents(PROCESS_LIST* pl);

// Question: What's the 2nd parameter passed into this function being used for?
PROCESS* get_minimum(PROCESS_LIST* pl, int (*compare_function)(PROCESS, PROCESS));

void mark_last_used(PROCESS_LIST*pl, PROCESS* p);

PROCESS_LIST* get_incomplete_processes(PROCESS_LIST* processes_in);

PROCESS_LIST* get_entered_processes(PROCESS_LIST* all_processes, float curr_time);
float get_next_entry_time(PROCESS_LIST* all_processes, float curr_time);



#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_LIST_H
