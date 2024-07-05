#ifndef _CALC_Model_H_
#define _CALC_Model_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {
// node for stack
class PolishNode {
 private:
  void clear_node();

 public:
  /**
  operation priority:
  0 - x, n
  1 - sum, sub
  2 - div, mod, mult
  3 - brackets, pow, unary plus, unary minus
  4 - sin, cos, tan, asin, acos, atan, sqrt, ln, log
  */
  enum class Priority { zero, first, second, third, fourt };

  // enum for math functions
  enum class MathFuncs {
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

  MathFuncs _math_foo;
  // (, ), -, +, *, /, ^, %
  char _operator;
  bool _is_unary;
  Priority _priority;
  long double _value;

  PolishNode();
  PolishNode(long double value);
  PolishNode(const PolishNode& other);
  PolishNode& operator=(const PolishNode& other);
};

// class for backend calculations
class Model {
 private:
  size_t parse_numbers(std::string str, size_t i, size_t lenth_of_str,
                       PolishNode* temp_node);

  size_t parse_brackets_funcs(std::string str, size_t i, PolishNode* temp_node);

  void parse_operators(std::string str, size_t i, PolishNode* temp_node,
                       std::stack<s21::PolishNode>* temp_polish,
                       std::stack<s21::PolishNode>* temp_stack);

  void parse_close_brackets(std::stack<s21::PolishNode>* temp_polish,
                            std::stack<s21::PolishNode>* temp_stack);

  void unary_calculations(std::stack<s21::PolishNode>* polish,
                          std::stack<s21::PolishNode>* temp_stack);

  void binary_calculations(std::stack<s21::PolishNode>* polish,
                           std::stack<s21::PolishNode>* temp_stack);

  inline long double get_number(PolishNode* node) { return node->_value; };

 public:
  /**
   * @brief foo checking string to correct input
   * @param str - string to check
   * @return `0` - if string correct
   * @return `1` - if string incorrect
   */
  int validate_string(std::string str);

  /**
   * @brief func to full calculation from str
   * @param input_str raw str from frontend
   * @param result result of calculations
   * @return `0` - success
   * @return `1` - error
   */
  int calculate_str(std::string input_str, long double* result);

  /**
   * @brief func to calculate polish notation
   * @param polish reverse polish notation to calculate
   * @param result result of calculations
   * @return `0` - success
   * @return `1` - error
   */
  int calculations(std::stack<s21::PolishNode>* polish, long double* result);

  /**
   * @brief foo converts to reverse polish notation
   * @param str - string to convert
   * @param polish - polish notation stack
   * @return `0` - if convert success
   * @return `1` - if convert failed
   */
  int converting_to_polish(std::string str,
                           std::stack<s21::PolishNode>* polish);

};  // class Model
}  // namespace s21

#endif  //_CALC_Model_H_
