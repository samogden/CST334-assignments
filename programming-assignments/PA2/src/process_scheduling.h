
#include "process_list.h"

#ifndef CST334_ASSIGNMENTS_PROCESS_SCHEDULING_H
#define CST334_ASSIGNMENTS_PROCESS_SCHEDULING_H

#define MAX_TIME 1000.0f
#define MINIMUM_TIME_QUANTUM 0.000001f

typedef struct SCHEDULER_PARAMS {
  bool preemptable;
  float time_quantum; // 0 if it's not RR, something else if it is.
  PROCESS* (* process_selection_func)(PROCESS_LIST*);
} SCHEDULER_PARAMS;

SCHEDULER_STATS* get_empty_stats_block();
void print_stats(SCHEDULER_STATS stats);

SCHEDULER_STATS* process_scheduling_loop(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats,
                                         PROCESS_LIST* processes_to_schedule); // Main processing loop that will increment until there are no processes left.  Returns stats block




#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_SCHEDULING_H
