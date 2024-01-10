
#include "stdlib.h"
#include "stdio.h"

#include "process_scheduling.h"
#include "process_list.h"
#include "student_code.h"

#define MAX_TIME 1000000.0f


float run_simulation_step(PROCESS_LIST *pl, PROCESS* p, float curr_time, SCHEDULER_STATS* stats, float time_slice) {
    // "Run" the process
    mark_last_used(pl, p);

    // Check whether this is the first time we've run the process
    if (p->time_remaining == p->length) {
        // Then this is the first time we've run the process
        mark_process_start(stats, p, curr_time, time_slice);
    }

    float slice_left = time_slice;

    // Check if the job is ending
    if (p->time_remaining <= slice_left) {
        // Then the job will end this time slice
        slice_left = slice_left - p->time_remaining;
        fprintf(stderr, "Process (id=%d) completed\n", p->id);
        mark_process_end(stats, p, curr_time+p->time_remaining, slice_left);
        remove_process(pl, p);
        free(p);
    } else {
        // If it has more time remaining than the time slice then reduce the time remaining
        mark_process_run(stats, p, curr_time, slice_left);
        //fprintf(stderr, "(%.1f): Ran process (id=%d) for %.2fs, %.2fs left\n", curr_time, p->id, time_slice, p->time_remaining);
        slice_left = 0.0f;
    }
    return slice_left;
}

SCHEDULER_STATS* process_scheduling_loop(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats, PROCESS_LIST* processes_to_schedule) {

    fprintf(stderr, "\nStarting processing loop\n");
    float curr_time = 0.0f; // Record the current time of the simulation
    PROCESS* process_to_run; // Set up a variable to hold the process we're going to run

    while (!is_empty(processes_to_schedule) && curr_time <= MAX_TIME) {
        //fprintf(stderr, "TIME: %.2fs\n", curr_time);
        // While we still have processes to schedule, pick one and run it

        // First, get jobs that have actually started, based on their entry time
        PROCESS_LIST* entered_processes = copy_only_entered_processes(processes_to_schedule, curr_time);

        // to debug better, uncommenting the next line might help
        //print_contents(entered_processes);

        if (is_empty(entered_processes)) {
            fprintf(stderr, "(%.1f) No jobs ready, skipping time slice\n", curr_time);
        } else {
            // Call our function to select our next process to run, passing in a process variable
            // By passing in a process point we can ensure we're modifying the existing process
            process_to_run = params.process_selection_func(entered_processes);

            fprintf(stderr, "(%.1f) Running p%d (%.1f left)\n", curr_time, process_to_run->id, process_to_run->time_remaining);
            // Run a step of the simulation
            run_simulation_step(processes_to_schedule, process_to_run, curr_time, stats, params.time_slice);
        }

        // Jump forward the length of a time slice
        curr_time += params.time_slice;
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