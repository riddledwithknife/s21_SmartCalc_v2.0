#ifndef FINANCE_CALC_H
#define FINANCE_CALC_H

namespace s21 {
class Credit {
 public:
  enum class CreditType { Annuity, Differentiated };

  struct Info {
    double monthly_payment;
    double overpayment;
    double total_payment;
  };

  Credit(double amount_, int term_, double rate_)
      : amount_(amount_), term_(term_), rate_(rate_) {}

  Info Calculate(CreditType credit_type);

 private:
  double amount_;
  int term_;
  double rate_;

  Info CalculateAnnuity() const;

  Info CalculateDifferentiated() const;

  static double RoundTwoDigits(double value);
};

class Deposit {
 public:
  enum class Frequency {
    Day = 365,
    Week = 52,
    Month = 12,
    Quarter = 4,
    HalfYear = 2,
    Year = 1
  };

  struct Info {
    double accrued_interest;
    double tax_amount;
    double amount_by_the_end;
  };

  Deposit(double amount_, int term_, double rate_, Frequency frequency_,
          double tax_rate_)
      : amount_(amount_),
        term_(term_),
        rate_(rate_),
        frequency_(frequency_),
        tax_rate_(tax_rate_) {}

  Info Calculate(bool is_capitalization);

  static Frequency MapIndexToDateOption(int index);

 private:
  double amount_;
  int term_;
  double rate_;
  Frequency frequency_;
  double tax_rate_;

  Info CalculateWithCapitalization();

  Info CalculateSimple() const;

  static double RoundTwoDigits(double value);
};
}  // namespace s21

#endif  // FINANCE_CALC_H