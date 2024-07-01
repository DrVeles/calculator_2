#include "Model.h"

namespace s21 {
// PolishNode class functions

PolishNode::PolishNode() { this->clear_node(); };
PolishNode::PolishNode(long double value) {
  this->clear_node();
  _value = value;
};
PolishNode::PolishNode(const PolishNode& other) {
  this->_math_foo = other._math_foo;
  this->_operators = other._operators;
  this->_is_unary = other._is_unary;
  this->_priority = other._priority;
  this->_priority = other._priority;
};

PolishNode& PolishNode::operator=(const PolishNode& other) {
  if (this == &other) {
    return *this;
  }
  this->_math_foo = other._math_foo;
  this->_operators = other._operators;
  this->_is_unary = other._is_unary;
  this->_priority = other._priority;

  return *this;
}

void PolishNode::clear_node() {
  this->_math_foo = PolishNode::MathFuncs::not_foo;
  this->_operators = '\0';
  this->_is_unary = 0;
  this->_priority = PolishNode::Priority::zero;
  this->_value = 0.0;
}

// Model class functions

Model::Model() {}

Model::~Model() {}

int Model::validate_string(std::string str) {
  int flag = 0;
  int brackets = 0;
  size_t lenght_str = str.length();
  for (size_t i = 0; i < lenght_str && !flag; i++) {
    if (str[i] == '(') {
      brackets++;
    } else if (str[i] == ')') {
      brackets--;
    } else if (str[i] == '.') {
      if (i == 0) {
        flag = 1;
      } else if (str[i - 1] < '0' || str[i - 1] > '9' || str[i + 1] < '0' ||
                 str[i + 1] > '9') {
        flag = 1;
      }
    } else if (i == lenght_str - 1 && str[i] != ')' &&
               !(str[i] <= '9' && str[i] >= '0')) {
      flag = 1;
    }
  }
  if (brackets != 0) {
    flag = 1;
  }
  return flag;
}

int Model::calculate_str(std::string input_str, long double* result) {
  std::stack<s21::PolishNode> polish;
  long double temp_res = 0;
  int flag = 0;
  if (!(validate_string(input_str)) &&
      !(converting_to_polish(input_str, &polish)) &&
      !(calculations(&polish, &temp_res))) {
    *result = temp_res;
  } else {
    flag = 1;
  }

  return flag;
}

int Model::calculations(std::stack<s21::PolishNode>* polish,
                        long double* result){};

int Model::converting_to_polish(std::string str,
                                std::stack<s21::PolishNode>* polish) {
  if (validate_string(str)) {
    return 1;
  }
  int flag = 0;
  std::stack<s21::PolishNode> temp_stack, temp_polish;
  size_t lenth_of_str = str.length();

  for (size_t i = 0; i < lenth_of_str && !flag;) {
    size_t temp_i = i;
    PolishNode temp_node;

    if (str[i] == ' ') {
      temp_i++;
    } else if (str[i] >= '0' && str[i] <= '9') {
      temp_i = parse_numbers(str, temp_i, lenth_of_str, &temp_node);
      // push(&temp_polish, &temp_node);
      temp_polish.push(temp_node);
    } else if (str[i] == '(' || str[i] == 's' || str[i] == 'c' ||
               str[i] == 't' || str[i] == 'a' || str[i] == 'l') {
      temp_i = parse_brackets_funcs(str, temp_i, &temp_node);
      // push(&temp_stack, &temp_node);
      temp_stack.push(temp_node);
    } else if ((str[i] == '+' || str[i] == '-' || str[i] == '*' ||
                str[i] == '/' || str[i] == '^' || str[i] == '%')) {
      parse_operators(str, temp_i, &temp_node, &temp_polish, &temp_stack);
      temp_i++;
    } else if (str[i] == ')') {
      parse_close_brackets(&temp_polish, &temp_stack);
      temp_i++;
    }
    if (i == lenth_of_str - 1) {
      while (!temp_stack.empty()) {
        // pop(&temp_stack, &temp_node);
        // push(&temp_polish, &temp_node);
        temp_polish.push(temp_stack.top());
        temp_stack.pop();
      }
    }
    i = temp_i;
  }
  *polish = temp_polish;
  return flag;
};

size_t Model::parse_numbers(std::string str, size_t i, size_t lenth_of_str,
                            PolishNode* temp_node) {
  int lenth_num = 1;
  for (size_t j = i + 1;
       j < lenth_of_str && ((str[j] >= '0' && str[j] <= '9') || str[j] == '.');
       j++, lenth_num++) {
    ;
  }

  std::string str_number = str.substr(i, lenth_num);
  temp_node->_value = std::stod(str_number);
  // char str_number[lenth_num + 1];
  // str_number[lenth_num] = '\0';
  // strncpy(str_number, &str[i], lenth_num);
  // temp_node->_value = atof(str_number);

  return (i += lenth_num);
}

size_t Model::parse_brackets_funcs(std::string str, size_t i,
                                   PolishNode* temp_node) {
  size_t len_str_foo = 0;
  if (str[i] == '(') {
    temp_node->_operators = '(';
    temp_node->_priority = PolishNode::Priority::third;
    len_str_foo = 1;
  } else if (str[i] == 's') {
    if (str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::sin_foo;
    } else if (str[i + 1] == 'q' && str[i + 4] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::sqrt_foo;
      len_str_foo = 5;
    }
  } else if (str[i] == 'c' && str[i + 3] == '(') {
    temp_node->_math_foo = PolishNode::MathFuncs::cos_foo;
  } else if (str[i] == 't' && str[i + 3] == '(') {
    temp_node->_math_foo = PolishNode::MathFuncs::tan_foo;
  } else if (str[i] == 'a') {
    if (str[i + 1] == 's' && str[i + 4] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::asin_foo;
    } else if (str[i + 1] == 'c' && str[i + 4] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::acos_foo;
    } else if (str[i + 1] == 't' && str[i + 4] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::atan_foo;
    }
    len_str_foo = 5;
  } else if (str[i] == 'l') {
    if (str[i + 1] == 'n' && str[i + 2] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::ln_foo;
      len_str_foo = 3;
    } else if (str[i + 1] == 'o' && str[i + 3] == '(') {
      temp_node->_math_foo = PolishNode::MathFuncs::log_foo;
    }
  }
  if (temp_node->_priority == PolishNode::Priority::zero) {
    temp_node->_priority = PolishNode::Priority::fourt;
  }
  if (!len_str_foo) {
    len_str_foo = 4;
  }
  temp_node->_is_unary = true;
  return i + len_str_foo;
}

void Model::parse_operators(std::string str, size_t i, PolishNode* temp_node,
                            std::stack<s21::PolishNode>* temp_polish,
                            std::stack<s21::PolishNode>* temp_stack) {
  PolishNode last_node = temp_stack->top();
  // show(temp_stack, &last_node);
  if ((str[i] == '+' || str[i] == '-') &&
      (str[i - 1] == '(' || (str[i - 1] == ' ' && str[i - 2] == '('))) {
    temp_node->_is_unary = true;
    temp_node->_priority = PolishNode::Priority::third;
  } else if (str[i] == '+' || str[i] == '-') {
    temp_node->_priority = PolishNode::Priority::first;
  } else if (str[i] == '^') {
    temp_node->_priority = PolishNode::Priority::third;
  } else {
    temp_node->_priority = PolishNode::Priority::second;
  }
  temp_node->_operators = str[i];

  // while ((!show(temp_stack, &last_node)) && (last_node._operators != '(') &&
  while (!temp_stack->empty() && (last_node._operators != '(') &&
         (((last_node._priority >= temp_node->_priority) &&
           (!temp_node->_is_unary && temp_node->_operators != '^')))) {
    PolishNode copy_node = {0};
    // pop(temp_stack, &copy_node);
    // push(temp_polish, &copy_node);
    temp_polish->push(temp_stack->top());
    temp_stack->pop();
    if (temp_stack->empty()) {
      last_node = temp_stack->top();
    }
  }
  // push(temp_stack,temp_node);
  temp_stack->push(*temp_node);
}

void Model::parse_close_brackets(std::stack<s21::PolishNode>* temp_polish,
                                 std::stack<s21::PolishNode>* temp_stack) {
  PolishNode last_node = temp_stack->top();
  bool while_flag = true;
  // while ((!show(temp_stack, &last_node)) && (last_node._operators != '(') &&
  while (!temp_stack->empty() && (last_node._operators != '(') && while_flag) {
    // pop(temp_stack, &last_node);
    // push(temp_polish, &last_node);
    temp_polish->push(temp_stack->top());
    temp_stack->pop();
    // if (last_node._math_foo) {
    if (last_node._math_foo != PolishNode::MathFuncs::not_foo) {
      while_flag = false;
    }
  }
  if (last_node._operators == '(') {
    // pop(temp_stack, &last_node);
    temp_stack->pop();
  }

  if (temp_stack->empty()) {
    last_node = temp_stack->top();
  }
}

}  // namespace s21
