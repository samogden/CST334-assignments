#ifndef STUDENT_CODE_H
#define STUDENT_CODE_H

#include "process_scheduling.h"

/**
 * Finalizes the calculation of the stats block after completion of run.
 * Hint: what can't we calculate before the end of the run?
 * Note: Check out the definition of the stats struct in stats.h
 * @param stats - a stats struct to have remaining fields computed.
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

#endif //STUDENT_CODE_H
