//
// Created by Sam Ogden on 3/30/24.
//

#ifndef STATISTICS_H
#define STATISTICS_H

typedef struct SCHEDULER_STATS {
  unsigned int num_processes_started;
  unsigned int num_processes_completed;
  float sum_of_turnaround_times;
  float sum_of_response_time;
  float average_turnaround_time;
  float average_response_time;
  float completion_time;
} SCHEDULER_STATS;


#endif //STATISTICS_H
