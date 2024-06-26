#ifndef _CALC_MODEL_H_
#define _CALC_MODEL_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
// using std

namespace s21 {
// result of working foo
enum class result { success, failure };

// node for stack
class node_t {
  private:
  // clear
 public:
  int _math_foo;
  // (, ), -, +, *, /, ^, %
  char _operators;
  bool _is_unary;
  int _priority;
  long double _value;

  node_t();
  node_t(long double value);
  node_t(const node_t& other);
  ~node_t();

  int is_number(const node_t &node);

};

class counter {
  int _count;

 public:
  counter() : _count() {}
  int count() const { return _count; }
  void inc() { ++_count; }
};

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

 public:
  model();
  ~model();

  /**
   * @brief func to calculate polish notation
   * @param polish reverse polish notation to calculate
   * @param result result of calculations
   * @return `0` - success
   * @return `1` - error
   */
  int calculations(std::stack<s21::node_t>* polish, long double* result);

  /**
   * @brief foo checking string to correct input
   * @param str - string to check
   * @return `0` - if string correct
   * @return `1` - if string incorrect
   */
  int validate_string(char* str);

  /**
   * @brief foo converts to reverse polish notation
   * @param str - string to convert
   * @param polish - polish notation stack
   * @return `0` - if convert success
   * @return `1` - if convert failed
   */
  int converting_to_polish(char* str, std::stack<s21::node_t>* polish);
};  // class model
}  // namespace s21

#endif  //_CALC_MODEL_H_
