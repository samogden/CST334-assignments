
#ifndef HELPER_H
#define HELPER_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"


#define NUM_TEST_REPEATS 10
#define MAX_IDENTIFIER_LENGTH 64
#define MAX_STR_LENGTH (64 + 1) * NUM_TEST_REPEATS


void setup();
void teardown();

/**
 * Generalized function to check whether a string is a particular type
 * @param func_ptr : function that checks for a more specific type
 * @param str
 * @return
 */
bool is_str_type(int (*func_ptr)(int), char* str);

/**
 * Is the string made up of *just* letters
 * @param str
 * @return
 */
bool is_str_alpha(char* str);

/**
 * Is the string made up of *just* numbers
 * @param str
 * @return
 */
bool is_str_num(char* str);

/**
 * Is the string made up of letters _and_ numbers
 * @param str
 * @return
 */
bool is_str_alphanum(char* str);

#endif //HELPER_H
