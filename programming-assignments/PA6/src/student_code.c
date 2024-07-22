#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "student_code.h"
#include "parser.h"
#include "string.h"
#include "helper.h"
#include <common.h>


/*
 * <Expression> -> <Numeral> | ( <Expression> <Operator> <Expression> )
 * <Numeral> -> <Literal> | <Variable>
 * <Operator> -> + | - | * | /
 * <Literal> -> [1-9][0-9]*
 * <Variable> -> [a-zA-Z]+
 */

/**
 * Takes in a tokenizer and produces an expression based on the production rule:
 * <Expression> -> <Numeral> | ( <Expression> <Operator> <Expression> )
 * @param t tokenizer that _should_ contain more tokens
 * @return
 */
Expression* parse_expression(Tokenizer* t) {
  // todo
  //Question: What should we do if the tokenizer is out of tokens?  Be specific and write some code.
  return NULL;
}

/**
 * Takes in a tokenizer and produces an Numeral based on the production rules:
 * <Numeral> -> <Literal> | <Variable>
 * <Literal> -> [1-9][0-9]*
 * <Variable> -> [a-zA-Z]+
 * @param t
 * @return
 */
Numeral* parse_numeral(Tokenizer* t) {
  // todo
  return NULL;
}

/**
 * Takes in a tokenizer and produces an Operator based on the production rule:
 * <Operator> -> + | - | * | /
 * Note that while these are literals, they should not be stored as such
 * @param t
 * @return
 */
Operator* parse_operator(Tokenizer* t) {
  // todo
  return NULL;
}

/**
 * Evaluates the expression by accessing the appropriate value, or recursing and passing into the operator evaluation
 * @param e
 * @return
 */
EvaluationResult evaluate_expression(Expression e) {
  EvaluationResult result;
  // todo
  return result;
}

/**
 * Evaluates the expression by considering what operation and what the values of the passed expressions are
 * @param o
 * @param left
 * @param right
 * @return
 */
EvaluationResult evaluate_operator(Operator o, Expression left, Expression right) {
  EvaluationResult result;
  // todo
  // Question: What errors might we throw?  What does each mean?  Hint, look at unit_tests and .h files.
  return result;
}

/**
 * Evaluate a Numeral
 * @param n
 * @return
 */
EvaluationResult evaluate_numeral(Numeral n) {
  EvaluationResult result;
  // todo
  return result;
}


