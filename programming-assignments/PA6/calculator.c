
#include "src/student_code.h"
#include "src/parser.h"
#include "src/common.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1024

int main() {

  size_t buffer_size = MAX_INPUT_LENGTH;
  char* buffer = (char *)malloc(buffer_size * sizeof(char));

  while (true) {
    // Read in line from stdin
    int chars_read = getline(&buffer, &buffer_size, stdin);
    buffer[chars_read - 1] = '\0'; // Strip off the newline

    // Parse results
    Expression* e = parse(buffer);
    if (e == NULL) {
      log_error("Parsing failed...\n");
      continue;
    }
    EvaluationResult result = evaluate_expression(*e);
    if (result.eval_type == eval_error) {
      log_error("Failed to evaluate.\n");
      switch (result.err_type) {
        case err_dividebyzero:
        log_error("Divide by zero detected.\n");
          break;
        case err_nonliteralfound:
        log_error("Non-literal found in expression.\n");
          break;
      }
      continue;
    } else {
      log_info("Result: %d\n", result.val);
    }
  }

  return 0;
}
