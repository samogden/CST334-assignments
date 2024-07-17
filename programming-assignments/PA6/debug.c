
#include "src/student_code.h"
#include "src/tokenizer.h"
#include "src/common.h"

int main() {
  Tokenizer t = init__tokenizer("Hello out there");
  while ( ! is_done(t)) {
    log_debug("token: %s\n", t.token);
    next_token(&t);
  }
  return 0;
}
