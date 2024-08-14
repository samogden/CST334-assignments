
#ifndef TESTS_H
#define TESTS_H


#include "process_scheduling.h"
#include "student_code.h"

/**
 * Run test with 2 jobs that both enter at t=0
 * @param params
 * @param stats
 */
void test_2proc_0entry_0entry(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats);

/**
 * Run a simulation with 2 jobs that enter at t=0 and t=1
 * @param params
 * @param stats
 */
void test_2proc_0entry_1entry(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats);

/**
 * Run a simulation with 5 jobs that enter at random times
 * @param params
 * @param stats
 */
void test_5proc(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats);

#endif //TESTS_H
