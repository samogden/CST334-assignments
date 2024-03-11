
#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdio.h"

#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_warn(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);

#endif //COMMON_H
