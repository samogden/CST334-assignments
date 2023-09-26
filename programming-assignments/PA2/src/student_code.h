//
// Created by Sam Ogden on 8/8/23.
//

#include "process_scheduling.h"

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H
#define CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H

void finalize_stats(SCHEDULER_STATS* stats);
void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice);
void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice);
void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice);

int compare_priority(PROCESS p1, PROCESS p2);
int compare_arrival_time(PROCESS p1, PROCESS p2);

PROCESS* fifo_process_selector(PROCESS_LIST* pl);
PROCESS* rr_process_selector(PROCESS_LIST* pl);
PROCESS* sjf_process_selector(PROCESS_LIST* pl);
PROCESS* priority_process_selector(PROCESS_LIST* pl);
PROCESS* lifo_process_selector(PROCESS_LIST* pl);
PROCESS* stcf_process_selector(PROCESS_LIST* pl);

#endif //CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H
