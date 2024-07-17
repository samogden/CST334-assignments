
#ifndef CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H
#define CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H

#include "statistics.h"

typedef struct PROCESS {
    unsigned int id; // Each process should have a unique ID
    float entry_time; // Time of job entry
    float duration; // Length of job

    float time_remaining; // Amount of runtime left for job

    float restart_time; // Used for calculating runtimes

    unsigned int priority; // Priority value -- lower is more important

} PROCESS;

PROCESS* create_process(float duration, unsigned int priority, float entry_time);
void delete_process(PROCESS* process);

void describe_process(PROCESS* p);

void run(PROCESS* p, SCHEDULER_STATS* stats, float curr_time);
void stop(PROCESS* p, SCHEDULER_STATS* stats, float curr_time);

void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started);
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed);

#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H
