#include "s21_mainwindow.h"

#include "Controller/s21_controller.h"

s21_MainWindow::s21_MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_MainWindow) {
  ui->setupUi(this);
}

s21_MainWindow::~s21_MainWindow() { delete ui; }

void s21_MainWindow::on_Zero_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "0");
}

void s21_MainWindow::on_One_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "1");
}

void s21_MainWindow::on_Two_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "2");
}

void s21_MainWindow::on_Three_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "3");
}

void s21_MainWindow::on_Four_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "4");
}

void s21_MainWindow::on_Five_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "5");
}

void s21_MainWindow::on_Six_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "6");
}

void s21_MainWindow::on_Seven_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "7");
}

void s21_MainWindow::on_Eight_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "8");
}

void s21_MainWindow::on_Nine_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "9");
}

void s21_MainWindow::on_Add_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "+");
}

void s21_MainWindow::on_Minus_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "-");
}

void s21_MainWindow::on_Mul_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "*");
}

void s21_MainWindow::on_Div_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "/");
}

void s21_MainWindow::on_Comma_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + ".");
}

void s21_MainWindow::on_Mod_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "%");
}

void s21_MainWindow::on_X_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "x");
}

void s21_MainWindow::on_NegVar_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "-a");
}

void s21_MainWindow::on_PlusVar_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "+a");
}

void s21_MainWindow::on_Pow_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "^");
}

void s21_MainWindow::on_Sqrt_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "sqrt()");
}

void s21_MainWindow::on_StaplesClose_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + ")");
}

void s21_MainWindow::on_StaplesOpen_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "(");
}

void s21_MainWindow::on_Equal_clicked() {
  s21::Controller::ProcessMathWithGraphExpression(ui);
}

void s21_MainWindow::on_Del_clicked() {
  QString currentString = ui->TextLine->text();
  currentString.chop(1);
  ui->TextLine->setText(currentString);
}

void s21_MainWindow::on_Clear_clicked() {
  ui->TextLine->setText("");
  ui->XValue->setText("");

  ui->xMin->setText("");
  ui->xMax->setText("");

  ui->yMin->setText("");
  ui->yMax->setText("");
}

void s21_MainWindow::on_SINCOSMENU_clicked() {
  if (ui->OperatorsTab->currentIndex() == 0) {
    QString style = ui->SINCOSMENU->styleSheet();
    ui->SINCOSMENU->setStyleSheet(ui->MAINMENU->styleSheet());
    ui->MAINMENU->setStyleSheet(style);
    ui->OperatorsTab->setCurrentIndex(1);
  }
}

void s21_MainWindow::on_MAINMENU_clicked() {
  if (ui->OperatorsTab->currentIndex() == 1) {
    QString style = ui->MAINMENU->styleSheet();
    ui->MAINMENU->setStyleSheet(ui->SINCOSMENU->styleSheet());
    ui->SINCOSMENU->setStyleSheet(style);
    ui->OperatorsTab->setCurrentIndex(0);
  }
}

void s21_MainWindow::on_Sin_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "sin()");
}

void s21_MainWindow::on_Cos_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "cos()");
}

void s21_MainWindow::on_Tan_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "tan()");
}

void s21_MainWindow::on_Asin_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "asin()");
}

void s21_MainWindow::on_Acos_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "acos()");
}

void s21_MainWindow::on_Atan_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "atan()");
}

void s21_MainWindow::on_Log_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "log()");
}

void s21_MainWindow::on_Ln_clicked() {
  ui->TextLine->setText(ui->TextLine->text() + "ln()");
}

void s21_MainWindow::on_actionFinancial_Mode_triggered() {
  FWindow->show();
  this->close();
}

void s21_MainWindow::on_actionMain_Mode_triggered() {
  FWindow->close();
  this->show();
}
