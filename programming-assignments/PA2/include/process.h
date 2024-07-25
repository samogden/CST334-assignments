
#ifndef PROCESS_H
#define PROCESS_H

#include "statistics.h"

typedef struct PROCESS {
    unsigned int id; // Each process should have a unique ID
    float entry_time; // Time of job entry
    float duration; // Length of job
    float time_remaining; // Amount of runtime left for job
    float restart_time; // Used for calculating runtimes
    unsigned int priority; // Priority value -- lower is more important
    float last_run; // When was the job last run
} PROCESS;

/**
 * Create a new process with appropriate fields filled
 * @param duration (float): how long is the process
 * @param priority (int): what is the priority of the process -- 0 is the highest priority
 * @param entry_time (float): when did the job enter and thus become eligable to run
 * @return
 */
PROCESS* create_process(float duration, unsigned int priority, float entry_time);

/**
 * Deletes a process, freeing up memory
 * @param process
 */
void delete_process(PROCESS* process);

/**
 * Prints out helpful information about process
 * @param p
 */
void describe_process(PROCESS* p);

/**
 * Move the given process to a running state
 * @param p (PROCESS*) : the process to change to the running state
 * @param stats (SCHEDULER_STATS*): stats block for the current simulation run
 * @param curr_time (float): float of the current time that a job was started to be run
 */
void run(PROCESS* p, SCHEDULER_STATS* stats, float curr_time);
/**
 * Move the given process to a stopped state
 * @param p (PROCESS*) : the process to change to the stopped state
 * @param stats (SCHEDULER_STATS*): stats block for the current simulation run
 * @param curr_time (float): float of the current time that a job was started to be run
 */
void stop(PROCESS* p, SCHEDULER_STATS* stats, float curr_time);

/**
 * Update appropriate metadata and stat date for starting a process
 * @param p
 * @param stats
 * @param time_started
 */
void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started);

/**
 * Update appropriate metadata and stat date for stopping a process
 * @param p
 * @param stats
 * @param time_started
 */
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed);

#endif //PROCESS_H
