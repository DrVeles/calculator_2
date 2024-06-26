#ifndef _CALC_MODEL_H_
#define _CALC_MODEL_H_

#include <cmath>
#include <iostream>
#include <string>

namespace s21 {

class model {
 private:
  /**
  operation priority:
  0 - x, n
  1 - sum, sub
  2 - div, mod, mult
  3 - brackets, pow, unary plus, unary minus
  4 - sin, cos, tan, asin, acos, atan, sqrt, ln, log
  */
  enum class priority { zero, first, second, third, fourt };

  // enum for math functions
  enum class multi_character {
    not_foo,
    sin_foo,
    cos_foo,
    tan_foo,
    asin_foo,
    acos_foo,
    atan_foo,
    sqrt_foo,
    ln_foo,
    log_foo
  };

  /* data */
 public:
  model(/* args */);
  ~model();
};  // class model

}  // namespace s21

#endif  //_CALC_MODEL_H_

// #define STACK_SIZE 255

// result of working foo
// typedef enum result { success, failure } result_e;

// // node of stack
// typedef struct {
//   int math_foo;
//   // (, ), -, +, *, /, ^, %
//   char operators;
//   bool is_unary;
//   int priority;
//   long double value;
// } s21_node_t;

// // stack array and top of array
// typedef struct {
//   int top;
//   s21_node_t array[STACK_SIZE];
// } s21_stack_t;

// // foo to validate node is number? return: true or false
// bool is_number(s21_node_t *node);

// // pushing node to top of stack
// int push(s21_stack_t *stack, s21_node_t *node);

// // take node from top of stack
// int pop(s21_stack_t *stack, s21_node_t *node);

// // only show last node
// int show(s21_stack_t *stack, s21_node_t *node);

// // clearing node
// void clear_node(s21_node_t *node);

// // clearing stack
// void clear_stack(s21_stack_t *stack);

// /**
//  * @brief func to calculate polish notation
//  * @param polish reverse polish notation to calculate
//  * @param result result of calculations
//  * @return `0` - success
//  * @return `1` - error
//  */
// int calculations(s21_stack_t* polish, long double* result);

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /**
//  * @brief foo checking string to correct input
//  * @param str - string to check
//  * @return `0` - if string correct
//  * @return `1` - if string incorrect
//  */
// int validate_string(char* str);

// /**
//  * @brief foo converts to reverse polish notation
//  * @param str - string to convert
//  * @param polish - polish notation stack
//  * @return `0` - if convert success
//  * @return `1` - if convert failed
//  */
// int converting_to_polish(char* str, s21_stack_t* polish);
