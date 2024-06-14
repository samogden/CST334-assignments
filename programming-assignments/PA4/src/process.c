
#include "process.h"

#include "stdlib.h"
#include "stdio.h"

#include "common.h"

unsigned int next_id = 0;

PROCESS* create_process(float duration, unsigned int priority, float entry_time) {

    // First, create_process a new object using malloc
    PROCESS* p = malloc(sizeof(PROCESS));

    // Next, set the fields of the object
    p->id = next_id++;
    p->duration = duration;
    p->priority = priority;
    p->entry_time = entry_time;
    p->time_remaining = duration;

    return p;
}

void delete_process(PROCESS* process) {
    free(process);
}

void describe_process(PROCESS* p) {
    printf("p->id: %d\n", p->id);
    printf("p->duration: %f\n", p->duration);
    printf("p->priority: %d\n", p->priority);
    printf("p->entry_time: %f\n", p->entry_time);
    printf("p->time_remaining: %f\n", p->time_remaining);
}

void run(PROCESS* p, SCHEDULER_STATS* stats, float curr_time) {
  // log_debug("Running job p%d (%0.3f remaining)\n", p->id, p->time_remaining)
  p->restart_time = curr_time;
  if (p->time_remaining == p->duration) {
    // Then it's our first time running
    mark_start(p, stats, curr_time);
  }
}
void stop(PROCESS* p, SCHEDULER_STATS* stats, float curr_time) {

  if (curr_time - p->restart_time < p->time_remaining) {
    // Then the job isn't done yet
    p->time_remaining -= curr_time - p->restart_time;
  } else {
    float job_end_time = p->restart_time + p->time_remaining;
    p->time_remaining = 0;
    mark_end(p, stats, job_end_time);
  }
  //log_debug("Stopping job p%d (%0.3f remaining)\n", p->id, p->time_remaining)
}
