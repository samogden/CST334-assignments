//
// Created by Sam Ogden on 9/26/23.
//

#include <criterion/criterion.h>

#include "../src/student_code.h"
#include "../src/process.h"
#include "../src/process_list.h"
#include "../src/process_scheduling.h"

TestSuite(HelperFunctions, .disabled=false);

Test(HelperFunctions, mark_process_start, .disabled=false) {
    SCHEDULER_STATS* s = get_empty_stats_block();
    PROCESS *p = create_process(1.0f, 0, 0.0f);

    mark_process_start(s, p, 0.0f, 1.0f);

    cr_assert(p->length == 1.0f);
    cr_assert(p->priority == 0);
    cr_assert(p->entry_time == 0.0f);
    cr_assert(p->time_remaining == 1.0f);

    cr_assert(s->num_processes_started == 1);
    cr_assert(s->num_processes_completed == 0);
    cr_assert(s->sum_of_turnaround_times == 0.0f);
    cr_assert(s->sum_of_response_time == 0.0f);
    cr_assert(s->average_turnaround_time == 0.0f);
    cr_assert(s->average_response_time == 0.0f);
    cr_assert(s->completion_time == 0.0f);
}

Test(HelperFunctions, mark_process_run, .disabled=false) {
    SCHEDULER_STATS* s = get_empty_stats_block();
    PROCESS *p = create_process(1.0f, 0, 0.0f);

    mark_process_run(s, p, 0.0f, 1.0f);

    cr_assert(p->length == 1.0f);
    cr_assert(p->priority == 0);
    cr_assert(p->entry_time == 0.0f);
    cr_assert(p->time_remaining == 0.0f);

    cr_assert(s->num_processes_started == 0);
    cr_assert(s->num_processes_completed == 0);
    cr_assert(s->sum_of_turnaround_times == 0.0f);
    cr_assert(s->sum_of_response_time == 0.0f);
    cr_assert(s->average_turnaround_time == 0.0f);
    cr_assert(s->average_response_time == 0.0f);
    cr_assert(s->completion_time == 0.0f);
}


Test(HelperFunctions, mark_process_end, .disabled=false) {
    SCHEDULER_STATS* s = get_empty_stats_block();
    PROCESS *p = create_process(1.0f, 0, 0.0f);
    p->time_remaining = 0; // Pretend the job ran
    mark_process_end(s, p, 1.0f, 0.0f);

    cr_assert(p->length == 1.0f);
    cr_assert(p->priority == 0);
    cr_assert(p->entry_time == 0.0f);
    cr_assert(p->time_remaining == 0.0f);

    cr_assert(s->num_processes_started == 0);
    cr_assert(s->num_processes_completed == 1);
    cr_assert(s->sum_of_turnaround_times == 1.0f);
    cr_assert(s->sum_of_response_time == 0.0f);
    cr_assert(s->average_turnaround_time == 0.0f);
    cr_assert(s->average_response_time == 0.0f);
    cr_assert(s->completion_time == 0.0f);
}


Test(HelperFunctions, finalize_stats, .disabled=false) {
    SCHEDULER_STATS* s = get_empty_stats_block();
    PROCESS *p0 = create_process(1.0f, 0, 0.0f);
    PROCESS *p1 = create_process(1.0f, 0, 0.0f);

    mark_process_start(s, p0,0.0f, 1.0f);
    mark_process_run(s, p0, 0.0f, 1.0f);
    mark_process_end(s, p0, 1.0f, 0.0f);

    mark_process_start(s, p1,1.0f, 1.0f);
    mark_process_run(s, p1, 1.0f, 1.0f);
    mark_process_end(s, p1, 2.0f, 0.0f);

    finalize_stats(s);

    cr_assert(s->num_processes_started == 2);
    cr_assert(s->num_processes_completed == 2);
    cr_assert(s->sum_of_turnaround_times == 3.0f);
    cr_assert(s->sum_of_response_time == 1.0f);
    cr_assert(s->average_turnaround_time == 1.5f);
    cr_assert(s->average_response_time == 0.5f);
    cr_assert(s->completion_time == 0.0f);
}
