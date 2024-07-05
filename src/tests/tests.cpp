#include "tests.h"

int main() {
  s21::Model m;
  // s21::Controller c;
  long double result = 0;
  m.calculate_str("2+2", &result);

  std::cout << result << "end кста";
  return 0;
}