//
// Created by Sam Ogden on 11/24/23.
//

#define DELIMITER " "

#include "tokenizer.h"
#include "string.h"

Tokenizer init__tokenizer(char* str_in) {
  Tokenizer t = {
    .str_left_to_tokenize = malloc(strlen(str_in)+1),
    .token = NULL,
    .delimiter = DELIMITER
  };
  strcpy(t.str_left_to_tokenize, str_in);
  t.token = strtok(t.str_left_to_tokenize, t.delimiter);
  return t;
}

void next_token(Tokenizer* t) {
  t->token = strtok(NULL, t->delimiter);
}

bool is_done(Tokenizer t) {
  return t.token == NULL;
}
