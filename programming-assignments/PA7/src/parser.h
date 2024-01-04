//
// Created by Sam Ogden on 11/24/23.
//

#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"

// Inspiration take from: https://people.cs.ksu.edu/~schmidt/300s05/Lectures/GrammarNotes/bnf.html
// and from

/*
 * <Expression> -> <Numeral> | ( <Expression> <Operator> <Expression> )
 * <Numeral> -> <Literal> | <Variable>
 * <Operator> -> + | - | * | /
 * <Literal> -> [1-9][0-9]*
 * <Variable> -> [a-zA-Z]+
 */

typedef struct Expression Expression;
typedef struct Operator Operator;
typedef struct Numeral Numeral;

struct Expression {
  enum {
    expr_numeral,
    expr_expression
  } expr_type;
  union{
    Numeral* numeral;
    struct {
      Expression* left;
      Operator* operator;
      Expression* right;
    };
  };
};

struct Numeral {
  enum {
    num_literal,
    num_variable
  } num_type;
  union {
    int val;
    char* identifier;
  };
};

typedef struct Operator {
  enum {
    opt_addition,
    opt_subtraction,
    opt_multiplication,
    opt_division
  } opt_type;
} Operator;

typedef struct EvaluationResult {
  enum {
    eval_value,
    eval_expression,
    eval_error
  } eval_type;
  union {
    int val;
    Expression* expression;
    enum {
      err_dividebyzero,
      err_nonliteralfound
    } err_type;
  };
} EvaluationResult;

Expression* parse(char* str_to_parse);
Expression* parse_expression(Tokenizer* t);
Numeral* parse_numeral(Tokenizer* t);
Operator* parse_operator(Tokenizer* t);

EvaluationResult evaluate_expression(Expression e);
EvaluationResult evaluate_operator(Operator o, Expression left, Expression right);
EvaluationResult evaluate_numeral(Numeral n);



#endif //PARSER_H
