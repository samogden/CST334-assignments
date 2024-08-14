

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

/**
 * Deletes a process list
 * @param pl (PROCESS_LIST*) : a pointer to a process list to delete
 */
void delete_process_list(PROCESS_LIST* pl);

/**
 * Adds a new process, p, to the tail of the process list
 * @param pl
 * @param p
 */
void add_process_to_tail(PROCESS_LIST* pl, PROCESS* p);


/**
 * Given a process list and a compare function for ordering, finds the "minimum" process
 * @param pl
 * @param compare_function
 * @return
 */
PROCESS* get_minimum(PROCESS_LIST* pl, int (*compare_function)(PROCESS, PROCESS));

/**
 * Finds all processes in the given process list that are incomplete and returns them as a new process list
 * @param processes_in
 * @return
 */
PROCESS_LIST* get_incomplete_processes(PROCESS_LIST* processes_in);

/**
 * Finds all processes in the given list that have entered and returns them as a new process list
 * @param all_processes
 * @param curr_time
 * @return
 */
PROCESS_LIST* get_entered_processes(PROCESS_LIST* all_processes, float curr_time);


/**
 * (Helper function) Determine whether a process list is empty
 * @param pl (PROCESS_LIST*) : process list to check
 * @return
 */
bool is_empty(PROCESS_LIST* pl);
/**
 * (Helper function) prints out the contents of the process list and some metadata
 * @param pl
 */
void print_contents(PROCESS_LIST* pl);

/**
 * (Helper function) Given a list of all processes and the current time, returns the next time a job enters
 * @param all_processes
 * @param curr_time
 * @return
 */
float get_next_entry_time(PROCESS_LIST* all_processes, float curr_time);

#endif //PROCESS_LIST_H
