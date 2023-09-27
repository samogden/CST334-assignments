//
// Created by Sam Ogden on 8/7/23.
//

#include "process_list.h"

#include "stdlib.h"
#include "stdio.h"

PROCESS_LIST* create_process_list() {
    PROCESS_LIST * pl = malloc(sizeof(PROCESS_LIST));
    pl->processes = malloc(MAX_NUMBER_PROCESSES * sizeof(PROCESS*));
    pl->last_used = -1;
    pl->num_processes = 0;
    return pl;
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
    if (pl->last_used == -1) { pl->last_used = 0; }
}

void add_process_to_head(PROCESS_LIST* pl, PROCESS* p) {

    if (pl->num_processes >= MAX_NUMBER_PROCESSES) {
        return; // truthfully we should fail here
    }

    for (int i = pl->num_processes; i > 0; i--) {
        pl->processes[i] = pl->processes[i-1];
    }
    pl->last_used++;
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
    if (pl->last_used >= index) {
        pl->last_used--;
    }
    pl->num_processes--;
}

void print_contents(PROCESS_LIST* pl) {
    fprintf(stderr, "(print_contents) (last_used: %d) ", pl->last_used);
    if (is_empty(pl)) {
        fprintf(stderr, "[empty]\n");
        return;
    }
    for (int i = 0; i < pl->num_processes; i++) {
        if (i == pl->last_used) {
            fprintf(stderr, "**id=%d**", pl->processes[i]->id);
        } else {
            fprintf(stderr, "id=%d", pl->processes[i]->id);
        }
        fprintf(stderr, "(%.1f/%.1f)", pl->processes[i]->time_remaining, pl->processes[i]->length);
        if (i != (pl->num_processes - 1)) {
            fprintf(stderr, " -> ");
        }
    }
    fprintf(stderr, "\n");
}

void mark_last_used(PROCESS_LIST* pl, PROCESS* p) {
    for (int i = 0; i < pl->num_processes; i++) {
        if (pl->processes[i] == p) {
            pl->last_used = i;
            return;
        }
    }
    pl->last_used = -1;
}

PROCESS* get_last_used(PROCESS_LIST* pl) {
    return pl->processes[pl->last_used % pl->num_processes];
}

PROCESS* get_next(PROCESS_LIST* pl) {
    return pl->processes[(pl->last_used + 1) % pl->num_processes];
}

PROCESS* get_prev(PROCESS_LIST* pl) {
    return pl->processes[(pl->last_used - 1) % pl->num_processes];
}

PROCESS_LIST* copy_only_entered_processes(PROCESS_LIST* all_process, float curr_time) {
    PROCESS_LIST* entered_processes = create_process_list();

    for (int i_all = 0; i_all < all_process->num_processes; i_all++) {
        if (all_process->processes[i_all]->entry_time <= curr_time) {
            entered_processes->processes[entered_processes->num_processes++] = all_process->processes[i_all];
        }
    }
    mark_last_used(entered_processes, all_process->processes[all_process->last_used]);
    return entered_processes;
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