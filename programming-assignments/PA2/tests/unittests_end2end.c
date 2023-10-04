//
// Created by Sam Ogden on 9/26/23.
//


#include <criterion/criterion.h>

#include <stdio.h>

#include "../src/process_scheduling.h"
#include "../src/student_code.h"
#include "../src/tests.h"


TestSuite(End2End, .disabled=false);

Test(End2End, test_2proc_0entry_1entry_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = fifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==10);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 5.0);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}

Test(End2End, test_2proc_0entry_0entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==15);
    cr_expect(stats->sum_of_response_time==1);
    cr_expect(stats->average_turnaround_time == 7.5);
    cr_expect(stats->average_response_time==0.5);
    printf("-----------------------------------\n");
}

Test(End2End, test_2proc_0entry_1entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==14);
    cr_expect(stats->sum_of_response_time==0);
    cr_expect(stats->average_turnaround_time == 7.0);
    cr_expect(stats->average_response_time==0);
    printf("-----------------------------------\n");
}

Test(End2End, test_2proc_0entry_1entry_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = sjf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==10);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 5.0);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}


Test(End2End, test_2proc_0entry_1entry_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = lifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==11);
    cr_expect(stats->sum_of_response_time==0);
    cr_expect(stats->average_turnaround_time == 5.5);
    cr_expect(stats->average_response_time==0.0);
    printf("-----------------------------------\n");
}

Test(End2End, test_2proc_0entry_1entry_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = stcf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==10);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 5.0);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}




Test(End2End, 5proc_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = fifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  66.0f);
    cr_expect(stats->sum_of_response_time==     47.0f);
    cr_expect(stats->average_turnaround_time == 13.20f);
    cr_expect(stats->average_response_time==    9.40f);
    printf("-----------------------------------\n");
}

Test(End2End, 5proc_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = lifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  62.0f);
    cr_expect(stats->sum_of_response_time==     22.0f);
    cr_expect(stats->average_turnaround_time == 12.40f);
    cr_expect(stats->average_response_time==    4.40f);
    printf("-----------------------------------\n");
}

Test(End2End, 5proc_priority, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = priority_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  83.0f);
    cr_expect(stats->sum_of_response_time==     55.0f);
    cr_expect(stats->average_turnaround_time == 16.60f);
    cr_expect(stats->average_response_time==    11.0f);
    printf("-----------------------------------\n");
}

Test(End2End, 5proc_sjc, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = sjf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  55.0f);
    cr_expect(stats->sum_of_response_time==     29.0f);
    cr_expect(stats->average_turnaround_time == 11.0f);
    cr_expect(stats->average_response_time==    5.80f);
    printf("-----------------------------------\n");
}


Test(End2End, 5proc_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = stcf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  53.0f);
    cr_expect(stats->sum_of_response_time==     32.0f);
    cr_expect(stats->average_turnaround_time == 10.60f);
    cr_expect(stats->average_response_time==    6.40f);
    printf("-----------------------------------\n");
}