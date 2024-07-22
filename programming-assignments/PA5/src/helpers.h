
#ifndef HELPERS_H
#define HELPERS_H

#define fsleep(f_seconds) msleep((long int)(f_seconds * (double)1000L))

#define TIME_DELAY 0.1 // Any orders of magnitude lower tends to lead to errors, likely due to noise

#define NUM_PLAYS 50

int msleep(long msec);
double currentTime();

#endif //HELPERS_H
