

#include <criterion/criterion.h>

#include <stdio.h>

#include "../src/process_scheduling.h"
#include "../src/student_code.h"
#include "../src/tests.h"

#define FLOAT_EPSILON 0.1


Test(FIFO, test_2proc_0entry_0entry_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = fifo_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  15, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     5,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7.5, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2.5,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(FIFO, test_2proc_0entry_1entry_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = fifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  14, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     4,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(RR, test_2proc_0entry_0entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0001f,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_assert(stats->num_processes_started==2);
    cr_assert(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  20, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     0,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    0,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(RR, test_2proc_0entry_1entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0001f,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_assert(stats->num_processes_started==2);
    cr_assert(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  18, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     0,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  9, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    0,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(SJF, test_2proc_0entry_0entry_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = sjf_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  15, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     5,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7.5, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2.5,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(SJF, test_2proc_0entry_1entry_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = sjf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  14, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     4,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}


Test(LIFO, test_2proc_0entry_0entry_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = lifo_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  15, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     5,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7.5, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2.5,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(LIFO, test_2proc_0entry_1entry_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = lifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  15, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     0,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7.5, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    0.0,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(STCF, test_2proc_0entry_0entry_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = stcf_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  15, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     5,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7.5, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2.5,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(STCF, test_2proc_0entry_1entry_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = stcf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect_float_eq(stats->completion_time,          10, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  14, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     4,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  7, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    2,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}


/*
 * Bigger end2end tests
 */
Test(FIFO, 5proc_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = fifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  76, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     47,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  15.2, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    9.4,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(LIFO, 5proc_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = lifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  72, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     22,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  14.4, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    4.4,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(PRIORITY, 5proc_priority, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = priority_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  87, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     58,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  17.4, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    11.6,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(SJF, 5proc_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = false,
            .time_quantum = 0.0f,
            .process_selection_func = sjf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  65, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     36,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  13, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    7.2,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}


Test(STCF, 5proc_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0f,
            .process_selection_func = stcf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  63, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     32,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  12.6, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    6.4,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}

Test(RR, 5proc_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0001f,
            .process_selection_func = rr_process_selector
    };

    test_5proc(params, stats);

    // todo: these can't be right because I shouldn't have partial times I don't think.
    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect_float_eq(stats->completion_time,          30, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_turnaround_times,  101.3, FLOAT_EPSILON);
    cr_expect_float_eq(stats->sum_of_response_time,     0,  FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_turnaround_time,  20.25, FLOAT_EPSILON);
    cr_expect_float_eq(stats->average_response_time,    0,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}