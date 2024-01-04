//
// Created by Sam Ogden on 11/20/23.
//


#include <time.h>
#include <errno.h>
#include <stdint.h>
#include "sys/time.h"

#include "common.h"
#include "string.h"
#include "ctype.h"


void setup() {
  srand(time(NULL));
};
void teardown() {};


bool is_str_type(int (*func_ptr)(int), char* str) {
  for (int i = 0; i < strlen(str); i++) {
    if ( ! func_ptr(str[i])) { return false; }
  }
  return true;
}

bool is_str_alpha(char* str) { return is_str_type(isalpha, str); }
bool is_str_num(char* str) { return is_str_type(isdigit, str); }
bool is_str_alphanum(char* str) { return is_str_type(isalnum, str); }