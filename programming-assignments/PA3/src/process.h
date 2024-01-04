//
// Created by Sam Ogden on 8/7/23.
//

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H
#define CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H

enum process_state {
    PROC_RUNNING,
    PROC_READY,
    PROC_BLOCKED
};
typedef struct PROCESS {
    unsigned int id; // Each process should have a unique ID
    float length; // Each process has an amount of time it will execute for
    enum process_state process_state; // Keeping track of process state
    unsigned int priority; // Priority value -- lower means higher priority, with 0 being highest priority
    float entry_time; // Entry time of the job
    float time_remaining; // Amount of time remaining in the execution
} PROCESS;

PROCESS* create_process(float length, unsigned int priority, float entry_time);
void delete_process(PROCESS* process);

void describe_process(PROCESS* p);

#endif //CST334_ASSIGNMENTS_SOLUTIONS_PROCESS_H
