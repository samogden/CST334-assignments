//
// Created by Sam Ogden on 11/24/23.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "stdlib.h"
#include "stdbool.h"

typedef struct Tokenizer Tokenizer; // Tokenizer internals

typedef struct Tokenizer {
  char* str_left_to_tokenize;
  char* token;
  char* delimiter;
} Tokenizer;

Tokenizer init__tokenizer(char* str_in);

// Advance one token (aka "burn a token")
void next_token(Tokenizer* t);

// Say whether we have tokens left or not
bool is_done(Tokenizer t);

#endif //TOKENIZER_H
