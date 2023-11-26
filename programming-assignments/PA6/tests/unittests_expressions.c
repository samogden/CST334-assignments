
#include <criterion/criterion.h>
#include "../src/common.h"
#include "../src/parser.h"
#include "time.h"


Test(
  Expressions,
  parse_expression__simple,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  char* test_str = "1";

  // Tokenize our operator
  Tokenizer t = init__tokenizer(test_str);

  Expression* e = parse_expression(&t);

  /*
   * We should now have a bunch of things:
   * 1. A non-NULL expression
   * 2. A tokenizer that is now empty
   * 3. A type of 'numeral'
   * 4. A `numeral` field that is:
   *  - A Numeral
   *  - literal
   *  - equal to 1
  */
  // Check #1
  cr_assert_not_null(e);

  // Check #2
  cr_assert(is_done(t));

  // Check #3
  cr_assert_eq(e->expr_type, expr_numeral);

  // Check #4
  cr_assert_not_null(e->numeral);
  cr_assert_eq(e->numeral->num_type, num_literal);
  cr_assert_eq(e->numeral->val, 1);

}


Test(
  Expressions,
  parse_expression__addition_literal,
  .init=setup,
  .fini=teardown,
  .timeout=3,
  .disabled=false
    ) {

  char* test_str = "( 1 + 2 )";

  // Tokenize our operator
  Tokenizer t = init__tokenizer(test_str);

  Expression* e = parse_expression(&t);

  /*
   * We should now have a bunch of things:
   * 1. A non-NULL expression
   * 2. A tokenizer that is now empty
   * 3. A type of 'expression'
   * 4. Two expressions as left and right
   *  - left should have value 1
   *  - right should have value 2
   * 5. An Operator as operator
   *  - Value '+'
  */

  // Checking #1
  cr_assert_not_null(e);

  // Checking #2
  cr_assert(is_done(t));

  // Checking #3
  cr_assert_eq(e->expr_type, expr_expression);

  // Checking #4
  cr_assert_not_null(e->left);
  cr_assert_eq(e->left->expr_type, num_literal);
  cr_assert_not_null(e->left->numeral);
  cr_assert_eq(e->left->numeral->val, 1);

  cr_assert_not_null(e->right);
  cr_assert_eq(e->right->expr_type, num_literal);
  cr_assert_not_null(e->right->numeral);
  cr_assert_eq(e->right->numeral->val, 2);

  // Checking #5
  cr_assert_not_null(e->operator);
  cr_assert_eq(e->operator->opt_type, opt_addition);

}
