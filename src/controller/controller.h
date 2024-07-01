#ifndef _CALC_CONTROLLER_H_
#define _CALC_CONTROLLER_H_

#include <string>

#include "./../model/model.h"

namespace s21 {
class controller {
 public:
  /**
   * @brief func to send string from front to backend and calculate result
   * @param input_str - string from frontend
   * @param result - result of backend works
   * @return `0` - success
   * @return `1` - failure
   */
  int api_to_calculate(const std::string input_str, long double* result) {
    model m;
    return m.calculate_str(input_str, result);
  }

  /**
   * @brief func to validate frontend string to correct math notation
   * @param input_str - string from frontend
   * @return `0` - success
   * @return `1` - failure
   */
  int api_to_validate(const std::string input_str) {
    model m;
    return m.validate_string(input_str);
  }
};

};  // namespace s21

#endif  //_CALC_CONTROLLER_H_