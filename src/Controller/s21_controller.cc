#include "s21_controller.h"

#include <string>

#include "../Model/s21_calculator.h"
#include "../Model/s21_finance.h"

void s21::Controller::ProcessMathWithGraphExpression(Ui::s21_MainWindow *ui) {
  std::string current_string = ui->TextLine->text().toStdString();
  std::string x_value_string = ui->XValue->text().toStdString();

  if (x_value_string.empty()) {
    x_value_string = "0";
  }

  s21::Calculator calculator;
  double result = calculator.Calculate(current_string, stod(x_value_string));

  if (calculator.GetStatus() == true) {
    int xMin = ui->xMin->text().toInt();
    int xMax = ui->xMax->text().toInt();

    int yMin = ui->yMin->text().toInt();
    int yMax = ui->yMax->text().toInt();

    QVector<double> x, y;
    double y_value;
    for (double x_value = xMin; x_value < xMax; x_value += 0.01) {
      y_value = calculator.Calculate(current_string, x_value);
      if (calculator.GetStatus() == true) {
        x.push_back(x_value);
        y.push_back(y_value);
      }
    }

    ui->graph->xAxis->setRange(xMin, xMax);
    ui->graph->yAxis->setRange(yMin, yMax);

    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);

    ui->graph->replot();
  }

  if (calculator.GetStatus() == true) {
    ui->TextLine->setText(QString::fromStdString(std::to_string(result)));
  } else if (calculator.GetStatus() == false) {
    ui->TextLine->setText("Error");
  }
}

void s21::Controller::ProcessCreditExpression(Ui::s21_FinanceWindow *ui) {
  s21::Credit credit(ui->DepositAmount->text().toDouble(),
                     ui->Term->text().toInt(),
                     ui->InterestRate->text().toDouble());
  s21::Credit::Info info = {};

  if (ui->Annuity->isChecked()) {
    info = credit.Calculate(s21::Credit::CreditType::Annuity);
  } else if (ui->Differentiated->isChecked()) {
    info = credit.Calculate(s21::Credit::CreditType::Differentiated);
  }

  ui->MonthlyPayment->setText(
      QString::fromStdString(std::to_string(info.monthly_payment)));
  ui->Overpayment->setText(
      QString::fromStdString(std::to_string(info.overpayment)));
  ui->TotalPayout->setText(
      QString::fromStdString(std::to_string(info.total_payment)));
}

void s21::Controller::ProcessDepositExpression(Ui::s21_FinanceWindow *ui) {
  s21::Deposit deposit(
      ui->DepositAmount_2->text().toDouble(), ui->Term_2->text().toInt(),
      ui->InterestRate_2->text().toDouble(),
      s21::Deposit::MapIndexToDateOption(ui->Date->currentIndex()),
      ui->TaxRate->text().toDouble());

  s21::Deposit::Info info = {};

  if (ui->YesCap->isChecked()) {
    info = deposit.Calculate(true);
  } else if (ui->NoCap->isChecked()) {
    info = deposit.Calculate(false);
  }

  ui->AccuredInterest->setText(
      QString::fromStdString(std::to_string(info.accrued_interest)));
  ui->TaxAmount->setText(
      QString::fromStdString(std::to_string(info.tax_amount)));
  ui->AmountByTheEnd->setText(
      QString::fromStdString(std::to_string(info.amount_by_the_end)));
}