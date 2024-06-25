//
// Created by Sam Ogden on 8/8/23.
//

#include "student_code.h"
#include "stdio.h"


void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started) {
  //todo
}
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed) {
  //todo
}

void finalize_stats(SCHEDULER_STATS* stats) {
  //todo
}

int compare_priority(PROCESS p1, PROCESS p2) {
  //todo
  return (int)p1.priority - (int)p2.priority;
}

PROCESS* fifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo
  return p;
}

PROCESS* rr_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo
  return p;
}

PROCESS* sjf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo
  return p;
}

PROCESS* priority_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  p = get_minimum(pl, compare_priority);
  return p;
}

PROCESS* lifo_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo
  return p;
}

PROCESS* stcf_process_selector(PROCESS_LIST* pl) {
  PROCESS *p = NULL;
  //todo
  return p;
}
