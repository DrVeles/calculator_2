#include "view.h"

#include "./ui_view.h"

view::view(QWidget *parent) : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);
  setWindowTitle("Calculator by Vasilii");
  setFixedSize(width(), height());
  view::initial_graph();

  ui->input_field_x->setPlaceholderText("enter x, default: 0");
  QDoubleValidator *validator = new QDoubleValidator(this);
  validator->setNotation(QDoubleValidator::StandardNotation);
  ui->input_field_x->setValidator(validator);

  on_pushButton_clear_all_clicked();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(click_to_number()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(click_to_number()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(click_to_operator()));

  connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this,
          SLOT(click_to_bracket()));
  connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this,
          SLOT(click_to_bracket()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(click_to_math_foo()));

  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(click_to_result()));
}

view::~view() {
  delete ui;
  ui->customPlot->clearPlottables();
  ui->customPlot->clearItems();
}

void view::on_pushButton_clear_all_clicked() {
  ui->label_show_field->setText("");
  ui->input_field_x->setText("");
  ui->customPlot->clearPlottables();
  ui->customPlot->clearItems();
  ui->spinBox_x->setValue(4);
  ui->customPlot->xAxis->setRange(-4, 4);
  ui->customPlot->yAxis->setRange(-4, 4);
  ui->customPlot->xAxis->setTickLabels(true);
  ui->customPlot->replot();
}

void view::click_to_number() {
  QPushButton *button = (QPushButton *)sender();
  bool is_print = false;
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
  }

  if (button->text().contains(".")) {
    if (text.endsWith('1') || text.endsWith('2') || text.endsWith('3') ||
        text.endsWith('4') || text.endsWith('5') || text.endsWith('6') ||
        text.endsWith('7') || text.endsWith('8') || text.endsWith('9') ||
        text.endsWith('0')) {
      is_print = true;
      bool for_flag = true;
      for (auto it = text.rbegin(); it != text.rend() && for_flag; ++it) {
        if (it->isDigit()) {
          continue;
        } else if (*it == QChar('.')) {
          is_print = false;
          for_flag = false;
        } else {
          is_print = true;
          for_flag = false;
        }
      }
    }
  } else if (button->text().contains("0") && (text.isEmpty())) {
    is_print = true;
  } else if ((text.endsWith('0'))) {
    is_print = false;
    bool for_flag = true;
    for (auto it = text.rbegin(); it != text.rend() && for_flag; ++it) {
      if (it->isDigit() && !(it + 1)->isDigit()) {
        if (*(it + 1) == QChar('.')) {
          is_print = true;
          for_flag = false;
        } else if (!(*it == QChar('0'))) {
          is_print = true;
          for_flag = false;
        } else {
          for_flag = false;
        }
      }
    }
  } else if (text.endsWith(')') || text.endsWith('x')) {
    is_print = false;
  } else {
    is_print = true;
  }

  if (is_print) {
    ui->label_show_field->setText(text + button->text());
  }
}

void view::click_to_operator() {
  QPushButton *button = (QPushButton *)sender();
  bool is_print = false;
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
    ui->label_show_field->setText(text);
  }

  if (text.endsWith('1') || text.endsWith('2') || text.endsWith('3') ||
      text.endsWith('4') || text.endsWith('5') || text.endsWith('x') ||
      text.endsWith('6') || text.endsWith('7') || text.endsWith('8') ||
      text.endsWith('9') || text.endsWith('0') || text.endsWith(')')) {
    is_print = true;
  } else if ((button->text().contains('-') || button->text().contains('+')) &&
             text.endsWith('(')) {
    is_print = true;
  }
  if (is_print) {
    ui->label_show_field->setText(text + button->text());
  }
}

void view::click_to_bracket() {
  QPushButton *button = (QPushButton *)sender();
  bool is_print = false;
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
  }

  if (button->text().contains(')') &&
      !(text.endsWith('+') || text.endsWith('-') || text.endsWith('*') ||
        text.endsWith('/') || text.endsWith('^') || text.endsWith('%') ||
        text.endsWith('('))) {
    is_print = true;
  } else if (button->text().contains('(') &&
             (text.endsWith('+') || text.endsWith('-') || text.endsWith('*') ||
              text.endsWith('/') || text.endsWith('^') || text.endsWith('%') ||
              text.isEmpty() || text.endsWith('('))) {
    is_print = true;
  }

  if (is_print) {
    ui->label_show_field->setText(text + button->text());
  }
}

void view::click_to_math_foo() {
  QPushButton *button = (QPushButton *)sender();
  bool is_print = true;
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
  }

  if (text.endsWith('1') || text.endsWith('2') || text.endsWith('3') ||
      text.endsWith('4') || text.endsWith('5') || text.endsWith('.') ||
      text.endsWith('6') || text.endsWith('7') || text.endsWith('8') ||
      text.endsWith('9') || text.endsWith('0') || text.endsWith(')') ||
      text.endsWith('x')) {
    is_print = false;
  }

  if (is_print) {
    ui->label_show_field->setText(text + button->text() + '(');
  }
}

void view::click_to_result() {
  bool is_print_err = false;
  long double res;
  bool to_double_flag = true;
  double x = ui->input_field_x->text().toDouble(&to_double_flag);
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
  }

  if (text.contains('x')) {
    if (ui->input_field_x->text().isEmpty()) {
      text.replace("x", "(0.0)");
    } else if (to_double_flag) {
      text.replace("x", '(' + QString::number(x, 'g', 7) + ')');
    }
  }
  if (!(text.endsWith('1') || text.endsWith('2') || text.endsWith('3') ||
        text.endsWith('4') || text.endsWith('5') || text.endsWith('6') ||
        text.endsWith('7') || text.endsWith('8') || text.endsWith('9') ||
        text.endsWith('0') || text.endsWith(')'))) {
    is_print_err = true;
  } else {
    text = "(" + text + ")";
    std::string str = text.toStdString();
    is_print_err = (s21::Controller().api_to_calculate(str, &res));
  }

  if (is_print_err) {
    ui->label_show_field->setText("Error");
  } else {
    ui->label_show_field->setText(QString::number(res, 'g', 7));
  }
  is_result_clicked_last = true;
}

double view::convert_x_to_y(double x, QString text) {
  QString x_str = QString::number(x, 'g', 17);
  long double y = 0.0;

  text.replace("x", '(' + x_str + ')');
  text = "(" + text + ")";
  std::string str = text.toStdString();
  s21::Controller().api_to_calculate(str, &y);
  return (double)y;
}

void view::on_pushButton_create_graph_clicked() {
  bool is_print = true;
  int range = ui->spinBox_x->text().toInt();
  int steps = 10;
  double x_value = 0;
  double center_y = 0;

  QString text = ui->label_show_field->text();
  if (text.contains('x')) {
    QString x_text = ui->input_field_x->text();
    QString text_to_valid = text;
    text_to_valid.replace("x", '(' + x_text + ')');
    std::string str = text_to_valid.toStdString();
    if (!s21::Controller().api_to_validate(str)) {
      if (!x_text.isEmpty()) {
        x_value = x_text.toDouble(&is_print);
      }
      center_y = view::convert_x_to_y(x_value, text);
      QVector<double> x(2 * range * steps), y(2 * range * steps);
      ui->customPlot->clearPlottables();
      ui->customPlot->clearItems();
      ui->customPlot->replot();
      for (int i = 0; i < range * steps * 2; i++) {
        x[i] = x_value + (i - range * steps) * (1.0 / steps);
        y[i] = convert_x_to_y(x[i], text);
      }

      ui->customPlot->addGraph();
      ui->customPlot->graph(0)->setData(x, y);
      ui->customPlot->graph(0)->setPen(QColor("#FFFFFF"));
    } else {
      is_print = false;
    }
  }

  if (is_print) {
    ui->customPlot->xAxis->setRange(-range + x_value, range + x_value);
    if (x_value > 900) {
      ui->customPlot->xAxis->setTickLabels(false);
    } else {
      ui->customPlot->xAxis->setTickLabels(true);
    }
    ui->customPlot->yAxis->setRange(-range + center_y, range + center_y);
    ui->customPlot->replot();
  } else {
    ui->label_show_field->setText("Error graph");
    ui->customPlot->clearPlottables();
    ui->customPlot->clearItems();
    ui->customPlot->replot();
  }
}

void view::initial_graph() {
  int range = ui->spinBox_x->text().toInt();

  ui->customPlot->xAxis->setRange(-range, range);
  ui->customPlot->yAxis->setRange(-range, range);

  ui->customPlot->xAxis->setBasePen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->setBasePen(QPen(QColor("#5E6C87")));
  ui->customPlot->xAxis->setTickPen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->setTickPen(QPen(QColor("#5E6C87")));
  ui->customPlot->xAxis->setSubTickPen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->setSubTickPen(QPen(QColor("#5E6C87")));
  ui->customPlot->xAxis->setTickLabelColor(QColor("#5E6C87"));
  ui->customPlot->yAxis->setTickLabelColor(QColor("#5E6C87"));
  ui->customPlot->xAxis->grid()->setPen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->grid()->setPen(QPen(QColor("#5E6C87")));
  ui->customPlot->xAxis->grid()->setZeroLinePen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->grid()->setZeroLinePen(QPen(QColor("#5E6C87")));
  ui->customPlot->yAxis->setTickLabels(false);
  ui->customPlot->xAxis->setTickLabels(true);
  ui->customPlot->setBackground(Qt::transparent);
  ui->customPlot->xAxis->setTickLabelColor(QColor("#CBE1FF"));
  ui->customPlot->yAxis->setTickLabelColor(QColor("#CBE1FF"));
  ui->customPlot->replot();
}

void view::on_pushButton_x_clicked() {
  QString text = ui->label_show_field->text();
  if (text.contains("Error") || text.contains("nan") || text.contains("inf") ||
      text.contains('e')) {
    text.clear();
  }

  if (!(text.endsWith('1') || text.endsWith('2') || text.endsWith('3') ||
        text.endsWith('4') || text.endsWith('5') || text.endsWith('6') ||
        text.endsWith('7') || text.endsWith('8') || text.endsWith('9') ||
        text.endsWith('0') || text.endsWith(')') || text.endsWith('.') ||
        text.endsWith('x'))) {
    ui->label_show_field->setText(text + "x");
  }
}
