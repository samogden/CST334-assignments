
#ifndef COMMON_H
#define COMMON_H

#include "stdio.h"

#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_warn(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);

#define fsleep(f_seconds) msleep((long int)(f_seconds * (double)1000L))

#define TIME_DELAY 0.1 // Any orders of magnitude lower tends to lead to errors, likely due to noise

#define NUM_PLAYS 50

int msleep(long msec);
double currentTime();

#endif //COMMON_H
