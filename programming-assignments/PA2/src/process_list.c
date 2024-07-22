
#include "process_list.h"

#include "stdlib.h"
#include "stdio.h"
#include "float.h"

PROCESS_LIST* create_process_list() {
  PROCESS_LIST * pl = malloc(sizeof(PROCESS_LIST));
  pl->processes = malloc(MAX_NUMBER_PROCESSES * sizeof(PROCESS*));
  pl->num_processes = 0;
  return pl;
}

void delete_process_list(PROCESS_LIST* pl) {
  free(pl->processes);
  free(pl);
}

bool is_empty(PROCESS_LIST* pl) {
  return (pl->num_processes == 0);
}

void add_process_to_tail(PROCESS_LIST* pl, PROCESS* p) {
  if (pl->num_processes >= MAX_NUMBER_PROCESSES) {
    return; // truthfully we should fail here
  }
  pl->processes[pl->num_processes] = p;
  pl->num_processes++;
}

void add_process_to_head(PROCESS_LIST* pl, PROCESS* p) {

  if (pl->num_processes >= MAX_NUMBER_PROCESSES) {
    return; // truthfully we should fail here
  }

  for (int i = pl->num_processes; i > 0; i--) {
    pl->processes[i] = pl->processes[i-1];
  }
  pl->processes[0] = p;
  pl->num_processes++;

}

void remove_process(PROCESS_LIST* pl, PROCESS* p) {
  if (is_empty(pl)) { return; } // If the list is empty, then we simply can return

  // First find the index of the given process
  int index = -1;
  for (index = 0; index < pl->num_processes; index++) {
    if (pl->processes[index] == p) { break; }
  }
  if (index == -1) { return; } // It wasn't in the list of processes anyway

  // We want to move everything _after_ the index forward one step
  for (int i = index; i < pl->num_processes; i++) {
    pl->processes[i] = pl->processes[i+1];
  }
  pl->num_processes--;
}

void print_contents(PROCESS_LIST* pl) {
  fprintf(stderr, "(print_contents)");
  if (is_empty(pl)) {
    fprintf(stderr, "[empty]\n");
    return;
  }
  for (int i = 0; i < pl->num_processes; i++) {
    fprintf(stderr, "id=%d", pl->processes[i]->id);
    fprintf(stderr, "(%.1f/%.1f)", pl->processes[i]->time_remaining, pl->processes[i]->duration);
    if (i != (pl->num_processes - 1)) {
      fprintf(stderr, " -> ");
    }
  }
  fprintf(stderr, "\n");
}

PROCESS_LIST* get_incomplete_processes(PROCESS_LIST* processes_in) {
  PROCESS_LIST* incomplete_processes = create_process_list();

  for (int i = 0; i < processes_in->num_processes; i++) {
    if (processes_in->processes[i]->time_remaining > 0.0) {
      add_process_to_tail(incomplete_processes, processes_in->processes[i]);
    }
  }
  return incomplete_processes;
}


PROCESS_LIST* get_entered_processes(PROCESS_LIST* all_process, float curr_time) {
  PROCESS_LIST* entered_processes = create_process_list();

  for (int i_all = 0; i_all < all_process->num_processes; i_all++) {
    if (all_process->processes[i_all]->entry_time <= curr_time) {
      entered_processes->processes[entered_processes->num_processes++] = all_process->processes[i_all];
    }
  }
  return entered_processes;
}

float get_next_entry_time(PROCESS_LIST* all_processes, float curr_time) {
  float next_entry_time = FLT_MAX;
  for (int i = 0; i < all_processes->num_processes; i++) {
    float process_entry_time = all_processes->processes[i]->entry_time;
    if (process_entry_time > curr_time &&
      process_entry_time < next_entry_time) {
      next_entry_time = process_entry_time;
  }
}
return next_entry_time;
}

PROCESS* get_minimum(PROCESS_LIST* pl, int (*compare_function)(PROCESS, PROCESS)) {
  if (is_empty(pl)) { return NULL; }

  PROCESS* minimum = pl->processes[0];
  for (int i = 1; i < pl->num_processes; i++) {
    if (compare_function(*minimum, *pl->processes[i]) > 0) {
      // Then the other function is better than the current best
      minimum = pl->processes[i];
    }
  }
  return minimum;
}