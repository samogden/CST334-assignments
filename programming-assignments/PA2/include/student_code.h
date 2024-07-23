
#include "process_scheduling.h"

#ifndef CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H
#define CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H

/**
 * Finalizes the calculation of the stats block, meaning it will calculate things like average turnaround time
 * @param stats - a stats object that has some fields that are not yet used (or to be overwritten)
 */
void finalize_stats(SCHEDULER_STATS* stats);

/**
 * Select a process from a PROCESS_LIST struct to be run next using the First-In-First-Out selection process
 * @param pl
 * @return
 */
PROCESS* fifo_process_selector(PROCESS_LIST* pl);
/**
 * Select a process from a PROCESS_LIST struct to be run next using the RoundRobin selection process
 * @param pl
 * @return
 */
PROCESS* rr_process_selector(PROCESS_LIST* pl);
/**
 * Select a process from a PROCESS_LIST struct to be run next using the Shortest Job First selection process
 * @param pl
 * @return
 */
PROCESS* sjf_process_selector(PROCESS_LIST* pl);
/**
 * Select a process from a PROCESS_LIST struct to be run next using the Priority selection process
 * @param pl
 * @return
 */
PROCESS* priority_process_selector(PROCESS_LIST* pl);
/**
 * Select a process from a PROCESS_LIST struct to be run next using the Last-In-First-Out selection process
 * @param pl
 * @return
 */
PROCESS* lifo_process_selector(PROCESS_LIST* pl);
/**
 * Select a process from a PROCESS_LIST struct to be run next using the Shortest-Time-to-Completion-First selection process
 * @param pl
 * @return
 */
PROCESS* stcf_process_selector(PROCESS_LIST* pl);

#endif //CST334_ASSIGNMENTS_SOLUTIONS_STUDENT_CODE_H
