#include "tests.h"

// ================= MODEL ==================

TEST(test_polish_node, test_constructors_1) {
  s21::PolishNode p = s21::PolishNode(1);
  s21::PolishNode r(p);
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_2) {
  s21::PolishNode p = s21::PolishNode(1);
  s21::PolishNode r = p;
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_3) {
  s21::PolishNode p = s21::PolishNode(1);
  s21::PolishNode r = s21::PolishNode(p);
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_4) {
  s21::PolishNode p = 1;
  s21::PolishNode r = s21::PolishNode(p);
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_5) {
  s21::PolishNode p(1);
  s21::PolishNode r = s21::PolishNode(p);
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_6) {
  s21::PolishNode p{1};
  s21::PolishNode r = s21::PolishNode(p);
  ASSERT_EQ(p._value, r._value);
}
TEST(test_polish_node, test_constructors_7) {
  s21::PolishNode p{1};
  s21::PolishNode r, t, c;
  r = t = c = p;
  ASSERT_EQ(p._value, r._value);
  ASSERT_EQ(p._value, t._value);
  ASSERT_EQ(p._value, c._value);
  ASSERT_EQ(p._value, p._value);
}

TEST(test_model, validate_string_1) {
  string strings[] = {"1 + 1", "3 - 1", "0.5 * 6", "15/5", "(-(-3))"};
  Model m;
  for (auto str : strings) {
    ASSERT_EQ(m.validate_string(str), 0);
  }
}

TEST(test_model, validate_string_2) {
  string strings[] = {"1 + 1 +", "3 - 1)", "(0.5 * 6", "15/5..5"};
  Model m;
  for (auto str : strings) {
    ASSERT_EQ(m.validate_string(str), 1);
  }
}

TEST(test_model, calculate_str_1) {
  string strings[] = {"1 + 2", "3 - 1", "0.5 * 6", "15/5"};
  Model m;
  long double res;
  for (auto str : strings) {
    m.calculate_str(str, &res);
    ASSERT_EQ(res, 3.0);
  }
}

TEST(test_model, calculate_addition) {
  string strings[] = {"1 + 2", "3 + 7", "0.5 + 6.5", "-2 + 5"};
  long double expected[] = {3, 10, 7, 3};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_subtraction) {
  string strings[] = {"5 - 2", "7 - 3", "6.5 - 0.5", "5 - 10"};
  long double expected[] = {3, 4, 6, -5};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_multiplication) {
  string strings[] = {"2 * 3", "4 * 0.5", "7 * 3", "-2 * 5"};
  long double expected[] = {6, 2, 21, -10};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_division) {
  string strings[] = {"6 / 2", "9 / 3", "7.5 / 0.5", "10 / -2"};
  long double expected[] = {3, 3, 15, -5};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_power) {
  string strings[] = {"2 ^ 3", "4 ^ 0.5", "5 ^ 2", "2 ^ -1"};
  long double expected[] = {8, 2, 25, 0.5};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_modulus) {
  string strings[] = {"10 % 3", "7 % 4", "5 % 2", "8 % 5"};
  long double expected[] = {1, 3, 1, 3};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_unary_plus_minus) {
  string strings[] = {"+2", "-3", "+0.5", "-2.5"};
  long double expected[] = {2, -3, 0.5, -2.5};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_EQ(res, expected[i]);
  }
}

TEST(test_model, calculate_str_2) {
  string strings[] = {"1 + 1 +", "3 - 1)", "(0.5 * 6", "15/5..5"};
  Model m;
  long double res;
  for (auto str : strings) {
    ASSERT_EQ(m.calculate_str(str, &res), 1);
  }
}

TEST(test_model, calculate_cosine) {
  string strings[] = {"cos(0)", "cos(3.14159265/2)", "cos(3.14159265)",
                      "cos(3*3.14159265/2)"};
  long double expected[] = {1, 0, -1, 0};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_sine) {
  string strings[] = {"sin(0)", "sin(3.14159265/2)", "sin(3.14159265)",
                      "sin(3*3.14159265/2)"};
  long double expected[] = {0, 1, 0, -1};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_tangent) {
  string strings[] = {"tan(0)", "tan(3.14159265/4)", "tan(3.14159265)",
                      "tan(3*3.14159265/4)"};
  long double expected[] = {0, 1, 0, -1};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_arccosine) {
  string strings[] = {"acos(1)", "acos(0)", "acos(-1)", "acos(0.5)"};
  long double expected[] = {0, 3.14159265 / 2, 3.14159265, 1.04719755};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_arcsine) {
  string strings[] = {"asin(0)", "asin(1)", "asin(-1)", "asin(0.5)"};
  long double expected[] = {0, 3.14159265 / 2, -3.14159265 / 2, 0.523598775};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_arctangent) {
  string strings[] = {"atan(0)", "atan(1)", "atan(-1)", "atan(1.7320508)"};
  long double expected[] = {0, 3.14159265 / 4, -3.14159265 / 4, 1.04719755};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_sqrt) {
  string strings[] = {"sqrt(4)", "sqrt(9)", "sqrt(0.25)", "sqrt(2)"};
  long double expected[] = {2, 3, 0.5, 1.41421356};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_ln) {
  string strings[] = {"ln(1)", "ln(2.718281828459045)", "ln(7.38905609893065)",
                      "ln(0.36787944117144233)"};
  long double expected[] = {0, 1, 2, -1};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

TEST(test_model, calculate_log) {
  string strings[] = {"log(1)", "log(10)", "log(100)", "log(0.1)"};
  long double expected[] = {0, 1, 2, -1};
  Model m;
  long double res;
  for (int i = 0; i < 4; ++i) {
    m.calculate_str(strings[i], &res);
    ASSERT_NEAR(res, expected[i], EPSILON);
  }
}

// =============== CONTROLLER =================

TEST(test_controller, test_api_to_validate_true) {
  s21::Controller c;
  string strings[] = {"1 + 1", "3 - 1", "0.5 * 6", "15/5"};
  for (auto str : strings) {
    ASSERT_EQ(c.api_to_validate(str), 0);
  }
}

TEST(test_controller, test_api_to_validate_false) {
  string strings[] = {"1 + 1 +", "3 - 1)", "(0.5 * 6", "15/5..5"};
  s21::Controller c;
  for (auto str : strings) {
    ASSERT_EQ(c.api_to_validate(str), 1);
  }
}

TEST(test_controller, test_api_to_calculate_true) {
  Controller c;
  long double res;

  struct TestCase {
    std::string expression;
    long double expected;
  };

  std::vector<TestCase> testCases = {
      {"1 + 2 - 3 * 13", 1 + 2 - 3 * 13},
      {"(1 + 2) - 3 * 13", (1 + 2) - 3 * 13},
      {"1 + (2 - 3) * 13", 1 + (2 - 3) * 13},
      {"(1 + 2 - 3) * 13", (1 + 2 - 3) * 13},
      {"(1 + 2) * (3 - 13)", (1 + 2) * (3 - 13)},
      {"(1 + 2) * 3 - 13", (1 + 2) * 3 - 13},
      {"1 + 2 - 3 * 13 + 4 / 2", 1 + 2 - 3 * 13 + 4 / 2},
      {"(1 + 2) * (3 - 13) / 2", (1 + 2) * (3 - 13) / 2},
      {"sqrt(16) + log(1) * log10(10) / sin(3.14159265 / 2)",
       sqrt(16) + log(1) * log10(10) / sin(3.14159265 / 2)},
      {"cos(0) + sin(3.14159265 / 2) - tan(0)",
       cos(0) + sin(3.14159265 / 2) - tan(0)},
      {"asin(1) + acos(0) - atan(1)", asin(1) + acos(0) - atan(1)},
  };

  for (const auto& testCase : testCases) {
    c.api_to_calculate(testCase.expression, &res);
    ASSERT_NEAR(res, testCase.expected, EPSILON);
  }
}

TEST(test_controller, test_api_to_calculate_false) {
  s21::Controller c;
  string strings[] = {"1 + 1 +", "3 - 1)", "(0.5 * 6", "15/5..5"};
  long double res;
  for (auto str : strings) {
    ASSERT_EQ(c.api_to_calculate(str, &res), 1);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
