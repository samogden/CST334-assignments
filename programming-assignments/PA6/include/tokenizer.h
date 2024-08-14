
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

/**
 * Initialize the tokenizer on a string.
 * @param str_in
 * @return
 */
Tokenizer init__tokenizer(char* str_in);

/**
 * Advance the tokenizer to the next token
 * @param t
 */
void next_token(Tokenizer* t);

/**
 * Return true if the tokenizer has no tokens left and false if it has remaining tokens
 * @param t
 * @return
 */
bool is_done(Tokenizer t);

#endif //TOKENIZER_H
