
#include "student_code.h"
#include "tokenizer.h"
#include <common.h>

int main() {
  Tokenizer t = init__tokenizer("Hello out there");
  while ( ! is_done(t)) {
    log_debug("token: %s\n", t.token);
    next_token(&t);
  }
  return 0;
}
