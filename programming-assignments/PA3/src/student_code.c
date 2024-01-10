
#include "student_code.h"

void finalize_stats(SCHEDULER_STATS* stats) {
    // todo
}


void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo
}

void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice) {
    // todo
}

void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float end_time, float time_slice_remaining) {
    // todo
}

int compare_priority(PROCESS p1, PROCESS p2) {
    return (int)p2.priority - (int)p1.priority;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    p = get_minimum(pl, compare_priority);
    return p;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    // todo
    return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    // todo
    return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    // todo
    return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
    PROCESS* p;
    // todo
    return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
    PROCESS *p;
    // todo
    return p;
}

