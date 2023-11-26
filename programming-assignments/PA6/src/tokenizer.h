//
// Created by Sam Ogden on 11/24/23.
//

#ifndef PA6_TOKENIZER_H
#define PA6_TOKENIZER_H

#include "stdlib.h"
#include "stdbool.h"

typedef struct Tokenizer Tokenizer; // Tokenizer internals

typedef struct Tokenizer {
  char* str_left_to_tokenize;
  char* token;
  char* delimiter;
} Tokenizer;

Tokenizer init__tokenizer(char* str_in);

void next_token(Tokenizer* t);
bool is_done(Tokenizer t);

#endif //PA6_TOKENIZER_H
