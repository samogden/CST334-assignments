#include "src/student_code.h"
#include "src/common.h"

#define FLOAT_EPSILON 0.1

int main() {
    SCHEDULER_STATS* stats = get_empty_stats_block();
    SCHEDULER_PARAMS params = (SCHEDULER_PARAMS) {
            .preemptable = true,
            .time_quantum = 0.0001f,
            .process_selection_func = rr_process_selector
    };

    test_5proc(params, stats);

    // todo: these can't be right because I shouldn't have partial times I don't think.
    printf("%d\b", stats->num_processes_started==    5);
    printf("%d\b", stats->num_processes_completed==  5);
    printf("%d\b", stats->completion_time,          30, FLOAT_EPSILON);
    printf("%d\b", stats->sum_of_turnaround_times,  101.3, FLOAT_EPSILON);
    printf("%d\b", stats->sum_of_response_time,     0,  FLOAT_EPSILON);
    printf("%d\b", stats->average_turnaround_time,  20.25, FLOAT_EPSILON);
    printf("%d\b", stats->average_response_time,    0,  FLOAT_EPSILON);
    printf("-----------------------------------\n");
}
