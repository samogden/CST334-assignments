
#include "stdlib.h"
#include "stdio.h"
#include "float.h"

#include "process_scheduling.h"
#include "process_list.h"
#include "process.h"
#include "student_code.h"

#include <common.h>


SCHEDULER_STATS* main_simulation_loop(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats, PROCESS_LIST* processes_to_schedule) {

  fprintf(stderr, "\nStarting processing loop\n");
  float curr_time = 0.0f; // Record the current time of the simulation

  PROCESS_LIST* incomplete_processes = get_incomplete_processes(processes_to_schedule);

  while ( (! is_empty(incomplete_processes)) && (curr_time <= MAX_TIME) ) {

    // Get jobs that have actually started, based on their entry time
    PROCESS_LIST* entered_processes = get_entered_processes(incomplete_processes, curr_time);
    // Select a process using our function.
    // Note: this will be NULL if our entered_processes is empty
    PROCESS* selected_process = params.process_selection_func(entered_processes);

    // Start with a time slice that'll end the simulation
    float next_time_slice = FLT_MAX;

    if (params.time_quantum > 0) {
      // Then we have a defined time slice, and we respect that each time
      next_time_slice = params.time_quantum;
    } else {

      // Get the time until the next arrival
      float time_until_next_arrival = get_next_entry_time(processes_to_schedule, curr_time) - curr_time;

      if (selected_process == NULL) {
        // Then we want to jump ahead to the next job arrival time since there are no jobs (see note above)
        next_time_slice = time_until_next_arrival;
      } else {
        // Otherwise, if we are preemptable we only run until it arrives
        if (params.preemptable && time_until_next_arrival < selected_process->time_remaining) {
          next_time_slice = time_until_next_arrival;
        } else {
          // Otherwise, we simply run until the end of the job
          next_time_slice = selected_process->time_remaining;
        }
      }
    }

    if (next_time_slice < MINIMUM_TIME_QUANTUM) {
      next_time_slice = MINIMUM_TIME_QUANTUM;
    }

    if (selected_process != NULL) {
      run(selected_process, stats, curr_time);
      selected_process->last_run = curr_time;
    }

    curr_time += next_time_slice;

    if (selected_process != NULL) {
      stop(selected_process, stats, curr_time);
    }

    delete_process_list(incomplete_processes);
    incomplete_processes = get_incomplete_processes(processes_to_schedule);
  }


  stats->completion_time = curr_time;
  finalize_stats(stats);
  print_stats(*stats);

  return stats;
}

SCHEDULER_STATS* get_empty_stats_block() {
  SCHEDULER_STATS* stats = malloc(sizeof(SCHEDULER_STATS));
  stats->num_processes_started = 0;
  stats->num_processes_completed = 0;
  stats->completion_time = 0.0f;
  stats->sum_of_turnaround_times = 0.0f;
  stats->sum_of_response_time = 0.0f;
  stats->average_turnaround_time = 0.0f;
  stats->average_response_time = 0.0f;
  return stats;
}

void print_stats(SCHEDULER_STATS stats) {
  fprintf(stderr, "stats->num_processes_started = %d\n", stats.num_processes_started);
  fprintf(stderr, "stats->num_processes_completed = %d\n", stats.num_processes_completed);
  fprintf(stderr, "stats->completion_time = %.2f\n", stats.completion_time);
  fprintf(stderr, "stats->sum_of_turnaround_times = %.2f\n", stats.sum_of_turnaround_times);
  fprintf(stderr, "stats->sum_of_response_time = %.2f\n", stats.sum_of_response_time);
  fprintf(stderr, "stats->average_turnaround_time = %.2f\n", stats.average_turnaround_time);
  fprintf(stderr, "stats->average_response_time = %.2f\n", stats.average_response_time);
}
