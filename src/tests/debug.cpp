#include "./../controller/controller.h"
#include "./../model/model.h"
using namespace s21;
using namespace std;

int main() {
  long double res;
  Model m;

  string str = "(-(-3))";
  m.calculate_str(str, &res);
  cout << "str = " << str << " res = " << res;

  return 0;
}