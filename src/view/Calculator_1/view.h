#ifndef S21_CALC_VIEW_H
#define S21_CALC_VIEW_H

#include <QMainWindow>
#include <QVector>

#include "./../../controller/controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

class view : public QMainWindow {
  Q_OBJECT

 public:
  view(QWidget *parent = nullptr);
  ~view();
  bool is_result_clicked_last;

 private:
  Ui::view *ui;

 private slots:
  void initial_graph();
  void click_to_number();
  void click_to_operator();
  void click_to_bracket();
  void click_to_math_foo();
  void click_to_result();
  void on_pushButton_clear_all_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_create_graph_clicked();
  double convert_x_to_y(double x, QString text);
};

#endif  // S21_CALC_VIEW_H
