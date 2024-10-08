
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

/**
 * Takes in a tokenizer and produces an expression based on the production rule:
 * <Expression> -> <Numeral> | ( <Expression> <Operator> <Expression> )
 * @param t (tokenizer): tokenizer projects that we should parse using
 * @return (Expression*) : Expression struct with all fields properly filled out
 */
Expression* parse_expression(Tokenizer* t);

/**
 * Takes in a tokenizer and produces an Numeral based on the production rules:
 * <Numeral> -> <Literal> | <Variable>
 * <Literal> -> [1-9][0-9]*
 * <Variable> -> [a-zA-Z]+
 * @param t (tokenizer): tokenizer projects that we should parse using
 * @return (Numeral*) : Numeral struct with all fields properly filled out
 */
Numeral* parse_numeral(Tokenizer* t);

/**
 * Takes in a tokenizer and produces an Operator based on the production rule:
 * <Operator> -> + | - | * | /
 * Note that while these are literals, they should not be stored as such
 * @param t (tokenizer): tokenizer projects that we should parse using
 * @return (Operator*) : Operator struct with all fields properly filled out
 */
Operator* parse_operator(Tokenizer* t);

/**
 * Evaluates the expression by accessing the appropriate value, or recursing and passing into the operator evaluation
 * @param e (Expression): Expression struct to evaluate
 * @return (EvaluationResult): struct with all fields appropriately set
 */
EvaluationResult evaluate_expression(Expression e);

/**
 * Evaluates the expression by considering what operation and what the values of the passed expressions are
 * @param o (Operator): Operator struct defining operationg to perform
 * @param left (Expression): Left-hand-side expression to evaluate
 * @param right (Expression): Right-hand-side expression to evaluate
 * @return (EvaluationResult): struct with all fields appropriately set
 */
EvaluationResult evaluate_operator(Operator o, Expression left, Expression right);

/**
 * Evaluate a Numeral
 * @param n (Numeral): Numeral struct to evaluate value of
 * @return (EvaluationResult): struct with all fields appropriately set
 */
EvaluationResult evaluate_numeral(Numeral n);



#endif //PARSER_H
