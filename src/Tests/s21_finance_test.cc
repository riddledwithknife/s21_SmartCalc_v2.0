#include "../Model/s21_finance.h"

#include <gtest/gtest.h>

TEST(CreditTest, Annuity) {
  s21::Credit credit(200000, 2, 24);

  s21::Credit::Info info = credit.Calculate(s21::Credit::CreditType::Annuity);
  EXPECT_EQ(info.monthly_payment, 10574.22);
  EXPECT_EQ(info.overpayment, 53781.27);
  EXPECT_EQ(info.total_payment, 253781.27);
}

TEST(CreditTest, Diff) {
  s21::Credit credit(200000, 2, 24);

  s21::Credit::Info info =
      credit.Calculate(s21::Credit::CreditType::Differentiated);
  EXPECT_EQ(info.monthly_payment, 10416.67);
  EXPECT_EQ(info.overpayment, 50000);
  EXPECT_EQ(info.total_payment, 250000);
}

TEST(Deposit, Capitalisation) {
  s21::Deposit deposit(500000, 2, 24, s21::Deposit::Frequency::Month, 13);

  s21::Deposit::Info info = deposit.Calculate(true);
  EXPECT_EQ(info.accrued_interest, 274420.2);
  EXPECT_EQ(info.tax_amount, 29798.42);
  EXPECT_EQ(info.amount_by_the_end, 804218.62);
}

TEST(Deposit, NoCapitalisation) {
  s21::Deposit deposit(500000, 2, 24, s21::Deposit::Frequency::Month, 13);

  s21::Deposit::Info info = deposit.Calculate(false);
  EXPECT_EQ(info.accrued_interest, 218550);
  EXPECT_EQ(info.tax_amount, 21450);
  EXPECT_EQ(info.amount_by_the_end, 500000);
}