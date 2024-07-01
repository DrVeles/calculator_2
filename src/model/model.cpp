#include "model.h"

namespace s21 {
// NODE_T class functions

node_t::node_t() {
  this->_math_foo = 0;
  this->_operators = '\0';
  this->_is_unary = 0;
  this->_priority = 0;
  this->_value = 0.0;
};
node_t::node_t(long double value) { _value = value; };

node_t::node_t(const node_t& other) {
  this->_math_foo = other._math_foo;
  this->_operators = other._operators;
  this->_is_unary = other._is_unary;
  this->_priority = other._priority;
  this->_priority = other._priority;
};

node_t::~node_t(){};

// MODEL class functions

model::model(){};

model::~model(){};

int model::calculations(std::stack<s21::node_t>* polish, long double* result){};

int model::validate_string(std::string str){};

int model::converting_to_polish(char* str, std::stack<s21::node_t>* polish){};

int model::calculate_str(std::string input_str, long double* result) {
  s21_stack_t polish;
  char* copy_str = malloc(strlen(input_str) + 1);
  strcpy(copy_str, input_str);
  long double temp_res = 0;

  if (!(validate_string(copy_str)) &&
      !(converting_to_polish(copy_str, &polish)) &&
      !(calculations(&polish, &temp_res))) {
    *result = temp_res;
  } else {
    flag = 1;
  }
  free(copy_str);

  return flag;
}
}  // namespace s21
