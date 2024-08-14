
#include "process_list.h"

#ifndef SCHEDULING_H
#define SCHEDULING_H

#define MAX_TIME 1000.0f
#define MINIMUM_TIME_QUANTUM 0.000001f

typedef struct SCHEDULER_PARAMS {
  bool preemptable;
  float time_quantum; // 0 if it's not RR, something else if it is.
  PROCESS* (* process_selection_func)(PROCESS_LIST*);
} SCHEDULER_PARAMS;

/**
 * Gives an entry stats block that we can use to track the simulation
 * @return
 */
SCHEDULER_STATS* get_empty_stats_block();

/**
 * (Helper function) prints out the stats block (generally for debugging)
 * @param stats
 */
void print_stats(SCHEDULER_STATS stats);

/**
 * Run the given scheduling approach until all jobs have been processed
 * @param params : SCHEDULE_PARAMS struct defining simulation parameters, such as scheduling policy
 * @param stats
 * @param processes_to_schedule
 * @return
 */
SCHEDULER_STATS* main_simulation_loop(
  SCHEDULER_PARAMS params,
  SCHEDULER_STATS* stats,
  PROCESS_LIST* processes_to_schedule
);

#endif //SCHEDULING_H
