//
// Created by Sam Ogden on 8/7/23.
//

#include "process_list.h"

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_SCHEDULING_H
#define CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_SCHEDULING_H

typedef struct SCHEDULER_STATS {
    unsigned int num_processes_started;
    unsigned int num_processes_completed;
    float sum_of_turnaround_times;
    float sum_of_response_time;
    float average_turnaround_time;
    float average_response_time;
    float completion_time;
} SCHEDULER_STATS;


typedef struct SCHEDULER_PARAMS {
    float time_slice;
    PROCESS* (*process_selection_func)(PROCESS_LIST*);
} SCHEDULER_PARAMS;

SCHEDULER_STATS* process_scheduling_loop(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats, PROCESS_LIST* processes_to_schedule); // Main processing loop that will increment until there are no processes left.  Returns stats block
PROCESS* select_process_to_run(PROCESS_LIST* pl); // Select next process to schedule
float run_simulation_step(PROCESS_LIST *pl, PROCESS* p, float curr_time, SCHEDULER_STATS* stats, float time_slice);
SCHEDULER_STATS* get_empty_stats_block();
void print_stats(SCHEDULER_STATS stats);


#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_SCHEDULING_H
