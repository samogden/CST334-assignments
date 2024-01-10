
#ifndef COMMON_H
#define COMMON_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"


#define NUM_TEST_REPEATS 10
#define MAX_IDENTIFIER_LENGTH 64
#define MAX_STR_LENGTH (64 + 1) * NUM_TEST_REPEATS

#define log_debug(...) fprintf(stderr, "DEBUG:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_info(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_warn(...)  fprintf(stderr, "INFO:");  fprintf(stderr, __VA_ARGS__); fflush(stderr);
#define log_error(...) fprintf(stderr, "ERROR:"); fprintf(stderr, __VA_ARGS__); fflush(stderr);


void setup();
void teardown();

bool is_str_type(int (*func_ptr)(int), char* str);
bool is_str_alpha(char* str);
bool is_str_num(char* str);
bool is_str_alphanum(char* str);

#endif //COMMON_H
