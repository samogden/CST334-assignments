
#include <criterion/criterion.h>
#include "../src/common.h"
#include "../src/parser.h"
#include "time.h"


Test(
  Evaluation,
  evaluate__numeral_simple,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "1";
  Tokenizer t = init__tokenizer(test_str);
  Numeral* n = parse_numeral(&t);

  EvaluationResult result = evaluate_numeral(*n);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 1);
}


Test(
  Numeral,
  evaluate__numeral_multiple,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  for (int i = 0; i < NUM_TEST_REPEATS; i++) {
    int val = rand();

    // Make a test string that contains just a single random number
    char* test_str = calloc(MAX_STR_LENGTH, sizeof(char));
    sprintf(test_str, "%d", val);

    // Make a tokenizer of the test string
    Tokenizer t = init__tokenizer(test_str);

    // Pass the tokenizer into the numeral parser
    Numeral* n = parse_numeral(&t);

    EvaluationResult result = evaluate_numeral(*n);
    cr_assert_eq(result.eval_type, eval_value);
    cr_assert_eq(result.val, val);
  }
}


Test(
  Evaluation,
  evaluate__expression_numeral,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "1";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 1);
}

Test(
  Evaluation,
  evaluate__expression__addition,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 + 2 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 3);
}
Test(
  Evaluation,
  evaluate__expression__subtraction,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 - 2 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, -1);
}
Test(
  Evaluation,
  evaluate__expression__multiplication,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 * 2 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 2);
}

Test(
  Evaluation,
  evaluate__expression__division,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 / 2 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 0);
}

Test(
  Evaluation,
  evaluate__expression__division__rounding,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 2 / 2 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 1);
}

Test(
  Evaluation,
  evaluate__expression__err_dividebyzero,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 / 0 )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_error);
  cr_assert_eq(result.err_type, err_dividebyzero);
}


Test(
  Evaluation,
  evaluate__expression_complex,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 + ( ( 2 * 3 ) - ( 3 / 1 ) ) )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_value);
  cr_assert_eq(result.val, 4);
}

Test(
  Evaluation,
  evaluate__expression_complex_error,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  // Note: these tests won't work without already having completed parsing
  char* test_str = "( 1 + ( ( 2 * 3 ) - ( 3 / ( 1 - 1 ) ) ) )";
  Tokenizer t = init__tokenizer(test_str);
  Expression* e = parse_expression(&t);

  EvaluationResult result = evaluate_expression(*e);
  cr_assert_eq(result.eval_type, eval_error);
  cr_assert_eq(result.err_type, err_dividebyzero);
}
