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

Expression* parse_expression(Tokenizer* t) {
  // todo
  //Question: What should we do if the tokenizer is out of tokens?  Be specific and write some code.
  return NULL;
}

Numeral* parse_numeral(Tokenizer* t) {
  // todo
  return NULL;
}

Operator* parse_operator(Tokenizer* t) {
  // todo
  return NULL;
}

EvaluationResult evaluate_expression(Expression e) {
  EvaluationResult result;
  // todo
  return result;
}

EvaluationResult evaluate_operator(Operator o, Expression left, Expression right) {
  EvaluationResult result;
  // todo
  // Question: What errors might we throw?  What does each mean?  Hint, look at unit_tests and .h files.
  return result;
}

EvaluationResult evaluate_numeral(Numeral n) {
  EvaluationResult result;
  // todo
  return result;
}


