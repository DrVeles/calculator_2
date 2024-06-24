#ifndef _CALC_CONTROLLER_H_
#define _CALC_CONTROLLER_H_

#include <string>

namespace s21 {
class controller {
 public:
  controller();
  ~controller();

  /**
   * @brief func to send string from front to backend
   * @param input_str - string from frontend
   * @param result - result of backend works
   * @return `0` - success
   * @return `1` - failure
   */
  int api_to_calculate(const char* input_str, long double* result);

  /**
   * @brief func to validate frontend string
   * @param input_str - string from frontend
   * @return `0` - success
   * @return `1` - failure
   */
  int api_to_validate(const char* input_str);
};

};  // namespace s21

#endif  //_CALC_CONTROLLER_H_