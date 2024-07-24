//
// Created by Sam Ogden on 8/8/23.
//

#include "student_code.h"
#include "stdio.h"

void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started) {
  // todo
}
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed) {
  // todo
}

void finalize_stats(SCHEDULER_STATS* stats) {
  // todo
}

int compare_noop(PROCESS p1, PROCESS p2) {
  return 0;
}

int compare_priority(PROCESS p1, PROCESS p2) {
  // todo
}

int compare_arrival_time(PROCESS p1, PROCESS p2) {
  // todo
}

int compare_arrival_time_invert(PROCESS p1, PROCESS p2) {
  // todo
}

int compare_job_duration(PROCESS p1, PROCESS p2) {
  // todo
}

int compare_time_remaining(PROCESS p1, PROCESS p2) {
  // todo
}

int compare_last_run(PROCESS p1, PROCESS p2) {
  // todo
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p;
  // todo: what should be this next line?
  p = get_minimum(pl, compare_noop);
  return p;
}
