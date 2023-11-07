#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stack>
#include <string>

namespace s21 {
class Calculator {
 public:
  Calculator() noexcept : infix_(), postfix_(), flag_(true) {}
  double Calculate(const std::string &expression, double x) noexcept;
  int GetStatus() const noexcept;

 private:
  enum functions_ {
    s21_cos = 'c',
    s21_sin = 's',
    s21_sqrt = 'q',
    s21_tan = 't',
    s21_acos = 'C',
    s21_asin = 'S',
    s21_atan = 'T',
    s21_ln = 'l',
    s21_log = 'L'
  };

  std::string infix_;
  std::string postfix_;
  bool flag_;

  void ToPostfix() noexcept;
  void DelExcessOperators() noexcept;
  static int GetPriority(char ch) noexcept;
  static bool IsDigit(char ch) noexcept;
  static bool IsOperator(char ch) noexcept;
  static bool IsFunc(char ch) noexcept;

  double Computation(double x) noexcept;
  double ArithmeticFunc(char func, double num) noexcept;
  double ArithmeticOperator(char sign, double num1, double num2) noexcept;

  static char GetFuncName(char ch1, char ch2) noexcept;
  static int GetFuncLen(char ch) noexcept;

  void ProcessDigit(int &i);
  void ProcessX(int &i);
  void ProcessOperator(int &i, std::stack<char> &stack1);
  void ProcessRBrace(int &i, std::stack<char> &stack1);
  static void ProcessLBrace(int &i, std::stack<char> &stack1);
  void ProcessFunc(int &i, std::stack<char> &stack1);

  void DigitsToStack(int &i, std::stack<double> &stack1);
  double FuncToStack(int &i, std::stack<double> &stack1);
  std::vector<double> GetNumbersFromStack(int i, std::stack<double> &stack1);
};
}  // namespace s21

#endif  // CALCULATOR_H
