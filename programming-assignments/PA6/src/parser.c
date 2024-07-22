
#include "parser.h"
#include <common.h>
#include "string.h"

Expression* parse(char* str_to_parse){
  Tokenizer t = init__tokenizer(str_to_parse);
  Expression* e = parse_expression(&t);
  if (e == NULL) {
    log_error("Parsing error!  Rule failed to parse.\n");
    return NULL;
  }
  if ( ! is_done(t)) {
    // Question: What is this checking?  Why is it important?
    log_error("Parsing error!  Tokens remaining.\n")
    return NULL;
  }
  return e;
}
