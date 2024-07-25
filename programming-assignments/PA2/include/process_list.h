

#ifndef PROCESS_LIST_H
#define PROCESS_LIST_H

#include <stdlib.h>
#include <stdbool.h>

#include "process.h"


#define MAX_NUMBER_PROCESSES 256

typedef struct PROCESS_LIST {
    PROCESS** processes; // List of pointers to processes in the current process list
    int num_processes; // Counter for how many processes we have the in process list currently
} PROCESS_LIST;

/**
 * Create a new empty process list struct
 * @return (PROCESS_LIST*) : a pointer to a new, empty but initialized process list structure
 */
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



#endif //PROCESS_LIST_H
