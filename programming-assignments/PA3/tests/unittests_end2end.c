

#include <criterion/criterion.h>

#include <stdio.h>

#include "../src/process_scheduling.h"
#include "../src/student_code.h"
#include "../src/tests.h"


TestSuite(End2End, .disabled=false);

Test(FIFO, test_2proc_0entry_1entry_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = fifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==14);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 7.0);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}

Test(RR, test_2proc_0entry_0entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_0entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==19);
    cr_expect(stats->sum_of_response_time==1);
    cr_expect(stats->average_turnaround_time == 9.5);
    cr_expect(stats->average_response_time==0.5);
    printf("-----------------------------------\n");
}

Test(RR, test_2proc_0entry_1entry_rr, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = rr_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==18);
    cr_expect(stats->sum_of_response_time==0);
    cr_expect(stats->average_turnaround_time == 9.0);
    cr_expect(stats->average_response_time==0);
    printf("-----------------------------------\n");
}

Test(SJF, test_2proc_0entry_1entry_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = sjf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==14);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 7);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}


Test(LIFO, test_2proc_0entry_1entry_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = lifo_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==15);
    cr_expect(stats->sum_of_response_time==0);
    cr_expect(stats->average_turnaround_time == 7.5);
    cr_expect(stats->average_response_time==0.0);
    printf("-----------------------------------\n");
}

Test(STCF, test_2proc_0entry_1entry_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = stcf_process_selector
    };

    test_2proc_0entry_1entry(params, stats);

    cr_expect(stats->num_processes_started==2);
    cr_expect(stats->num_processes_completed==2);
    cr_expect(stats->completion_time==10);
    cr_expect(stats->sum_of_turnaround_times==14);
    cr_expect(stats->sum_of_response_time==4);
    cr_expect(stats->average_turnaround_time == 7.0);
    cr_expect(stats->average_response_time==2);
    printf("-----------------------------------\n");
}




Test(FIFO, 5proc_fifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = fifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  76.0f);
    cr_expect(stats->sum_of_response_time==     47.0f);
    cr_expect(stats->average_turnaround_time == 15.20f);
    cr_expect(stats->average_response_time==    9.40f);
    printf("-----------------------------------\n");
}

Test(LIFO, 5proc_lifo, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = lifo_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  72.0f);
    cr_expect(stats->sum_of_response_time==     22.0f);
    cr_expect(stats->average_turnaround_time == 14.40f);
    cr_expect(stats->average_response_time==    4.40f);
    printf("-----------------------------------\n");
}

Test(PRIORITY, 5proc_priority, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = priority_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  93.0f);
    cr_expect(stats->sum_of_response_time==     55.0f);
    cr_expect(stats->average_turnaround_time == 18.60f);
    cr_expect(stats->average_response_time==    11.0f);
    printf("-----------------------------------\n");
}

Test(SJF, 5proc_sjf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = sjf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  65.0f);
    cr_expect(stats->sum_of_response_time==     29.0f);
    cr_expect(stats->average_turnaround_time == 13.0f);
    cr_expect(stats->average_response_time==    5.80f);
    printf("-----------------------------------\n");
}


Test(STCF, 5proc_stcf, .disabled=false) {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .time_slice = 1,
            .process_selection_func = stcf_process_selector
    };

    test_5proc(params, stats);

    cr_expect(stats->num_processes_started==    5);
    cr_expect(stats->num_processes_completed==  5);
    cr_expect(stats->completion_time==          30.0f);
    cr_expect(stats->sum_of_turnaround_times==  63.0f);
    cr_expect(stats->sum_of_response_time==     32.0f);
    cr_expect(stats->average_turnaround_time == 12.60f);
    cr_expect(stats->average_response_time==    6.40f);
    printf("-----------------------------------\n");
}