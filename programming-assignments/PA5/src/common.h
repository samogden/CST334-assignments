//
// Created by Sam Ogden on 11/20/23.
//

#ifndef PA5_COMMON_H
#define PA5_COMMON_H

#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__);
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__);
#define log_warn(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__);
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__);

#define fsleep(f_seconds) msleep((long int)(f_seconds * (double)1000L))

#define TIME_DELAY 1

int msleep(long msec);

#endif //PA5_COMMON_H
