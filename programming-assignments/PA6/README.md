# CST334 Project 6: Building a calculator

## Assignment Description

In this project we're going to build a calculator!
Your mission is to set it up so it can do two main things
1. Parse input from a user
2. Evaluate the equation given

To do this we'll be implementing the below grammar:

```
<Expression> -> <Numeral> | ( <Expression> <Operator> <Expression> )
<Numeral> ::= <Literal> | <Variable>
<Operator> ::= + | - | * | /
<Literal> ::= [1-9][0-9]*
<Variable> ::= [a-zA-Z]+
```

This grammar will accept equations that look like `( 1 + 1 )`.
There are a few things to notice about this.
First, there are spaces between every individual component that we expect.
This helps us with tokenization so that we can figure out what we are going to be parsing at each step.
Second, by surrounding everything with parentheses it makes unambiguous.


#### Examples of equations that are ***accepted***

```shell
1
( 1 + 1 )
( 1 + ( 1 / 1 ) )
( ( 1 / 1 ) + 1 )
```

#### Examples of equations that should be ***rejected***

```shell
(1+1)
( 1 + 1 / 1  )
( (1 / 1) + 1 )
```

### Your task

You have two main tasks in this assignment: parsing the expression, and evaluating the expression.

To parse the expression you have to write the parsing functions below.
There are three of these, one for each of the main structs that we have defined in `parser.h`.
Using these, you'll have to build the syntax tree based on these elements.
Examining the structs will likely help.

To evaluate the expressions you have to complete the evaluation functions.
These should return the value of the expression/numeral/operator.

As a hint, both of these will likely use a recursive approach.

### Functions you'll be writing

```c

// Note: You don't need to write this function, but it needs to work
Expression* parse(char* str_to_parse); // 5 points

Expression* parse_expression(Tokenizer* t); // 15 points
Numeral* parse_numeral(Tokenizer* t); // 15 points
Operator* parse_operator(Tokenizer* t); // 15 points

EvaluationResult evaluate_expression(Expression e); // 10 points
EvaluationResult evaluate_operator(Operator o, Expression left, Expression right); // 10 points
EvaluationResult evaluate_numeral(Numeral n); // 10 points

```

Note: some of these functions rely on earlier functions to be written before they can pass any tests.


### Getting started

Setting up this project is very similar to the [previous programming assignments](../), so please check those out if you have questions!

Note: Some of the tests are passing right now.  These are testing rejection states, so these may change over time.

## What to submit

You'll be submitting ***only*** `student_code.c` and `student_code.h`.
Any other files changed will be lost during the grading process.

## Conclusion

Good luck!

p.s. 
There's also a new make rule called `calculator`.
You can use it to build a calculator app!

## Hints

### `union`s in C

I've used a new C data structure called a `union`.
These are similar to `struct`s, but instead of grouping different data types together they allow you to use _one_ of the fields.
That is, if I write:
```c
union {
  char a;
  int b;
};
```
I can use _either_ `a` or `b`, but these two values are actually stored in the same memory location, so I can only use one _or_ the other.
This allows us to use a single struct that can represent different productions.

I'd also recommend looking into unions a bit further when you get a chance.


