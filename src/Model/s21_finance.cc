#include "s21_finance.h"

#include <cmath>
#include <stdexcept>

s21::Credit::Info s21::Credit::Calculate(CreditType credit_type) {
  term_ *= 12;
  if (credit_type == CreditType::Annuity) {
    return CalculateAnnuity();
  } else if (credit_type == CreditType::Differentiated) {
    return CalculateDifferentiated();
  }
  throw std::invalid_argument("Invalid credit type.");
}

s21::Credit::Info s21::Credit::CalculateAnnuity() const {
  double month_payment, coefficient, i;
  i = rate_ / 12.0 / 100.0;
  coefficient = i * pow(1 + i, term_) / (pow(1 + i, term_) - 1);
  month_payment = coefficient * amount_;
  return {RoundTwoDigits(month_payment),
          RoundTwoDigits(month_payment * term_ - amount_),
          RoundTwoDigits(month_payment * term_)};
}

s21::Credit::Info s21::Credit::CalculateDifferentiated() const {
  double term_remains = amount_;
  double average_payment = 0;

  for (int i = 0; i < term_; i++) {
    double all_payments = amount_ / term_ + term_remains * rate_ / 100.0 / 12.0;
    average_payment += all_payments;
    term_remains = term_remains - amount_ / term_;
  }

  return {RoundTwoDigits(average_payment / term_),
          RoundTwoDigits(average_payment - amount_),
          RoundTwoDigits(average_payment)};
}

double s21::Credit::RoundTwoDigits(double value) {
  return std::round(value * 100.0) / 100.0;
}

s21::Deposit::Info s21::Deposit::Calculate(bool is_capitalization) {
  term_ *= 12;

  if (is_capitalization) {
    return CalculateWithCapitalization();
  } else {
    return CalculateSimple();
  }
}

s21::Deposit::Frequency s21::Deposit::MapIndexToDateOption(int index) {
  switch (index) {
    case 1:
      return s21::Deposit::Frequency::Day;
    case 2:
      return s21::Deposit::Frequency::Week;
    case 3:
      return s21::Deposit::Frequency::Month;
    case 4:
      return s21::Deposit::Frequency::Quarter;
    case 5:
      return s21::Deposit::Frequency::HalfYear;
    case 6:
      return s21::Deposit::Frequency::Year;
    default:
      return s21::Deposit::Frequency::Month;
  }
}

s21::Deposit::Info s21::Deposit::CalculateWithCapitalization() {
  double rate_per_year = rate_ / 100.0;
  double result_amount =
      amount_ * pow(1 + (rate_per_year / static_cast<int>(frequency_)),
                    static_cast<int>(frequency_) * term_ / 12.0);
  double accrued_interest = result_amount - amount_;
  double tax = 75000;

  if (accrued_interest > tax) {
    tax = (accrued_interest - tax) * (tax_rate_ / 100.0);
  } else {
    tax = 0;
  }

  return {RoundTwoDigits(accrued_interest - tax), RoundTwoDigits(tax),
          RoundTwoDigits(result_amount)};
}

s21::Deposit::Info s21::Deposit::CalculateSimple() const {
  double rate_per_month = rate_ / 12.0 / 100.0;
  double accrued_interest = amount_ * rate_per_month * term_;
  double tax = 75000;

  if (accrued_interest > tax) {
    tax = (accrued_interest - tax) * (tax_rate_ / 100.0);
  } else {
    tax = 0;
  }

  return {RoundTwoDigits(accrued_interest - tax), RoundTwoDigits(tax),
          RoundTwoDigits(amount_)};
}

double s21::Deposit::RoundTwoDigits(double value) {
  return std::round(value * 100.0) / 100.0;
}