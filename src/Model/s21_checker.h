#ifndef CHECKER_H
#define CHECKER_H

#include <string>

namespace s21 {
class Checker {
 public:
  explicit Checker(const std::string &expr);
  bool IsCorrect() const;

 private:
  std::string expression_;
  int exp_len_;
  bool is_correct_;

  bool ValidateLen();
  bool ValidateAlphabet();
  bool ValidateSigns();
  bool ValidateParentheses();
  bool ValidateFunctions();
  bool ValidateNumbers();
  static bool IsDigit(char ch);
};

}  // namespace s21

#endif  // CHECKER_H
