#include "./../controller/controller.h"
#include "./../model/model.h"
using namespace s21;
using namespace std;

int main() {
  long double res;
  Model m;
  string str = "1+1";
  m.calculate_str(str, &res);

  cout << res << " = res, but need to " << str << " " << (1 + 1);
  return 0;
}