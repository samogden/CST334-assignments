
#include <criterion/criterion.h>
#include "../src/common.h"
#include "../src/parser.h"
#include "time.h"


Test(Operator, parse_operator__addition, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  // Tokenize our operator
  Tokenizer t = init__tokenizer("+");

  // Parse our operator
  Operator* o = parse_operator(&t);

  /*
   * We should now have two things:
   * 1. An operator is a valid operator
   * 2. A tokenizer that is now empty
  */
  cr_assert_not_null(o);
  cr_assert_eq(o->opt_type, opt_addition);
  cr_assert(is_done(t));
}

Test(Operator, parse_operator__subtraction, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  // Tokenize our operator
  Tokenizer t = init__tokenizer("-");

  // Parse our operator
  Operator* o = parse_operator(&t);

  /*
   * We should now have two things:
   * 1. An operator is a valid operator
   * 2. A tokenizer that is now empty
  */
  cr_assert_not_null(o);
  cr_assert_eq(o->opt_type, opt_subtraction);
  cr_assert(is_done(t));
}


Test(Operator, parse_operator__multiplication, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  // Tokenize our operator
  Tokenizer t = init__tokenizer("*");

  // Parse our operator
  Operator* o = parse_operator(&t);

  /*
   * We should now have two things:
   * 1. An operator is a valid operator
   * 2. A tokenizer that is now empty
  */
  cr_assert_not_null(o);
  cr_assert_eq(o->opt_type, opt_multiplication);
  cr_assert(is_done(t));
}

Test(Operator, parse_operator__division, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  // Tokenize our operator
  Tokenizer t = init__tokenizer("/");

  // Parse our operator
  Operator* o = parse_operator(&t);

  /*
   * We should now have two things:
   * 1. An operator is a valid operator
   * 2. A tokenizer that is now empty
  */
  cr_assert_not_null(o);
  cr_assert_eq(o->opt_type, opt_division);
  cr_assert(is_done(t));
}

Test(Operator, parse_operator__invalid1, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {


  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    // Pick a random character that is not one of our known operators
    char c;
    do {
      c = (rand() % (1 << sizeof(char))) + 1;
    } while (c == '+' || c == '-' || c == '*' || c == '/');

    // Create a test string using our random character
    char* test_str = calloc(MAX_IDENTIFIER_LENGTH, sizeof(char));
    sprintf(test_str, "%c", c);

    // Tokenize our test string
    Tokenizer t = init__tokenizer(test_str);

    // Parse our operator
    Operator* o = parse_operator(&t);

    /*
     * We should now have two things:
     * 1. A NULL pointer instead of an operator
     * 2. A tokenizer that is not empty
    */
    cr_assert_null(o);
    cr_assert_not(is_done(t));

  }
}

Test(Operator, parse_operator__invalid2, .init=setup, .fini=teardown, .timeout=3, .disabled=false) {

  char valid_operators[] = {'+', '-', '*', '/'};

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    // Pick a random character that is not one of our known operators
    char c;
    do {
      c = (rand() % (1 << sizeof(char))) + 1;
    } while (c == '+' || c == '-' || c == '*' || c == '/');

    // Create a test string using our random character
    char* test_str = calloc(MAX_IDENTIFIER_LENGTH, sizeof(char));
    sprintf(
      test_str,
      "%c%c",
      valid_operators[rand() % 4],
      c
    );

    // Tokenize our test string
    Tokenizer t = init__tokenizer(test_str);

    // Parse our operator
    Operator* o = parse_operator(&t);

    /*
     * We should now have two things:
     * 1. A NULL pointer instead of an operator
     * 2. A tokenizer that is not empty
    */
    cr_assert_null(o);
    cr_assert_not(is_done(t));

  }
}
