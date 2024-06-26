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

int model::validate_string(char* str){};

int model::converting_to_polish(char* str, std::stack<s21::node_t>* polish){};

}  // namespace s21

int main() {
  s21::node_t test;
  std::cout << test._value << "end кста";
  return 0;
}