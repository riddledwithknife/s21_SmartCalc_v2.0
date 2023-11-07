#include "s21_financewindow.h"

#include "Controller/s21_controller.h"

s21_FinanceWindow::s21_FinanceWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::s21_FinanceWindow) {
  ui->setupUi(this);
}

s21_FinanceWindow::~s21_FinanceWindow() { delete ui; }

void s21_FinanceWindow::on_CREDITCALCMENU_clicked() {
  if (ui->ModeTab->currentIndex() == 1) {
    QString style = ui->CREDITCALCMENU->styleSheet();
    ui->CREDITCALCMENU->setStyleSheet(ui->DEPOSITCALCMENU->styleSheet());
    ui->DEPOSITCALCMENU->setStyleSheet(style);
    ui->ModeTab->setCurrentIndex(0);
  }
}

void s21_FinanceWindow::on_DEPOSITCALCMENU_clicked() {
  if (ui->ModeTab->currentIndex() == 0) {
    QString style = ui->DEPOSITCALCMENU->styleSheet();
    ui->DEPOSITCALCMENU->setStyleSheet(ui->CREDITCALCMENU->styleSheet());
    ui->CREDITCALCMENU->setStyleSheet(style);
    ui->ModeTab->setCurrentIndex(1);
  }
}

void s21_FinanceWindow::on_Calculate_clicked() {
  s21::Controller::ProcessCreditExpression(ui);
}

void s21_FinanceWindow::on_Clear_clicked() {
  ui->DepositAmount->setText("");
  ui->Term->setText("");
  ui->InterestRate->setText("");

  ui->MonthlyPayment->setText("");
  ui->Overpayment->setText("");
  ui->TotalPayout->setText("");
}

void s21_FinanceWindow::on_Annuity_clicked() {
  ui->Differentiated->setChecked(false);
}

void s21_FinanceWindow::on_Differentiated_clicked() {
  ui->Annuity->setChecked(false);
}

void s21_FinanceWindow::on_Calculate_2_clicked() {
  s21::Controller::ProcessDepositExpression(ui);
}

void s21_FinanceWindow::on_Clear_2_clicked() {
  ui->DepositAmount_2->setText("");
  ui->Term_2->setText("");
  ui->InterestRate_2->setText("");
  ui->TaxRate->setText("");

  ui->AccuredInterest->setText("");
  ui->TaxAmount->setText("");
  ui->AmountByTheEnd->setText("");
}

void s21_FinanceWindow::on_YesCap_clicked() { ui->NoCap->setChecked(false); }

void s21_FinanceWindow::on_NoCap_clicked() { ui->YesCap->setChecked(false); }
