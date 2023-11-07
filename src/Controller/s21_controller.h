#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "View/FinanceWindow/s21_financewindow.h"
#include "View/MainWindow/s21_mainwindow.h"

namespace s21 {
class Controller {
 public:
  static void ProcessMathWithGraphExpression(Ui::s21_MainWindow *ui);

  static void ProcessCreditExpression(Ui::s21_FinanceWindow *ui);

  static void ProcessDepositExpression(Ui::s21_FinanceWindow *ui);
};
}  // namespace s21

#endif  // CONTROLLER_H
