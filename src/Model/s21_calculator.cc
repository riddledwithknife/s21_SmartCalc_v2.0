#include "s21_calculator.h"

#include <cmath>
#include <stack>
#include <string>
#include <vector>

#include "s21_checker.h"

namespace s21 {
double Calculator::Calculate(const std::string &expression, double x) noexcept {
  for (char c : expression) {
    if (c != ' ') {
      infix_ += c;
    }
  }
  DelExcessOperators();

  double result = 0;
  s21::Checker checker(infix_);
  flag_ = checker.IsCorrect();
  if (flag_) {
    ToPostfix();
    result = Computation(x);
  }
  infix_ = {}, postfix_ = {};
  return result;
}

int Calculator::GetStatus() const noexcept { return flag_; }

void Calculator::ToPostfix() noexcept {
  std::stack<char> stack1;

  for (int i = 0; infix_[i] != '\0' && flag_;) {
    if (IsDigit(infix_[i])) {
      ProcessDigit(i);
    } else if (infix_[i] == 'x') {
      ProcessX(i);
    } else if (IsFunc(infix_[i])) {
      ProcessFunc(i, stack1);
    } else if (infix_[i] == '(') {
      ProcessLBrace(i, stack1);
    } else if (IsOperator(infix_[i])) {
      ProcessOperator(i, stack1);
    } else if (infix_[i] == ')') {
      ProcessRBrace(i, stack1);
    } else {
      flag_ = false;
    }
  }
  while (!stack1.empty()) {
    if (stack1.top() == '(' || stack1.top() == ')') flag_ = false;
    postfix_ += stack1.top();
    postfix_ += ' ';
    stack1.pop();
  }
}

void Calculator::DelExcessOperators() noexcept {
  std::string temp;

  if (infix_[0] == '-')
    temp += '~';
  else if (infix_[0] != '+')
    temp += infix_[0];

  for (unsigned long i = 1; i < infix_.size(); i++) {
    if (infix_[i - 1] == '(' && infix_[i] == '-') {
      temp += '~';
    } else if (!((i == 0 || infix_[i - 1] == '(') && infix_[i] == '+')) {
      temp += infix_[i];
    }
  }
  infix_.swap(temp);
}

int Calculator::GetPriority(char ch) noexcept {
  int priority = -1;

  std::string funcs_alias("sctCSTqlL");

  if (ch == '(' || ch == ')')
    priority = 0;
  else if (ch == '+' || ch == '-')
    priority = 1;
  else if (ch == '*' || ch == '/' || ch == '%')
    priority = 2;
  else if (ch == '^' || funcs_alias.find(ch) != std::string::npos)
    priority = 3;
  else if (ch == '~')
    priority = 4;
  return priority;
}

bool Calculator::IsDigit(char ch) noexcept { return ch >= '0' and ch <= '9'; }

bool Calculator::IsOperator(char ch) noexcept {
  bool result = false;
  std::string functions("+-~*/%^");
  if (functions.find(ch) != std::string::npos) result = true;
  return result;
}

bool Calculator::IsFunc(char ch) noexcept {
  bool result = false;
  std::string functions("cstal");
  if (functions.find(ch) != std::string::npos) result = true;
  return result;
}

double Calculator::Computation(double x) noexcept {
  std::string temp;
  std::string funcs_alias("sctCSTqlL"), operators("+-*/%^~");
  std::stack<double> stack1;

  double result = 0;
  std::vector<double> numbers;

  for (int i = 0; postfix_[i] != '\0'; i++) {
    if (IsDigit(postfix_[i])) {
      DigitsToStack(i, stack1);
    } else if (postfix_[i] == 'x') {
      stack1.push(x);
    } else if (funcs_alias.find(postfix_[i]) != std::string::npos) {
      result = FuncToStack(i, stack1);
    } else if (operators.find(postfix_[i]) != std::string::npos) {
      numbers = GetNumbersFromStack(i, stack1);
      if (flag_) {
        result = ArithmeticOperator(postfix_[i], numbers[1], numbers[0]);
        stack1.push(result);
      }
    }
  }
  return result;
}

double Calculator::ArithmeticFunc(char func, double num) noexcept {
  double result = 0;

  if (func == s21_cos) {
    result = cos(num);
  } else if (func == s21_sin) {
    result = sin(num);
  } else if (func == s21_tan) {
    result = tan(num);
  } else if (func == s21_acos) {
    if (num < -1 || num > 1)
      flag_ = false;
    else
      result = acos(num);
  } else if (func == s21_asin) {
    if (num < -1 || num > 1)
      flag_ = false;
    else
      result = asin(num);
  } else if (func == s21_atan) {
    result = atan(num);
  } else if (func == s21_sqrt) {
    if (num < 0)
      flag_ = false;
    else
      result = sqrt(num);
  } else if (func == s21_ln) {
    if (num <= 0)
      flag_ = false;
    else
      result = log(num);
  } else if (func == s21_log) {
    if (num <= 0)
      flag_ = false;
    else
      result = log10(num);
  } else {
    flag_ = false;
  }

  return result;
}

double Calculator::ArithmeticOperator(char sign, double num1,
                                      double num2) noexcept {
  double result = 0;
  if (sign == '+') {
    result = num1 + num2;
  } else if (sign == '-' || sign == '~') {
    result = num1 - num2;
  } else if (sign == '*') {
    result = num1 * num2;
  } else if (sign == '/') {
    if (num2 == 0)
      flag_ = false;
    else
      result = num1 / num2;
  } else if (sign == '^') {
    result = pow(num1, num2);
  } else if (sign == '%') {
    if (num2 == 0)
      flag_ = false;
    else
      result = fmod(num1, num2);
  } else {
    flag_ = false;
  }
  return result;
}

char Calculator::GetFuncName(char ch1, char ch2) noexcept {
  char result = 0;
  if (ch1 == 'c' && ch2 == 'o')
    result = s21_cos;
  else if (ch1 == 's' && ch2 == 'i')
    result = s21_sin;
  else if (ch1 == 't' && ch2 == 'a')
    result = s21_tan;
  else if (ch1 == 'a' && ch2 == 'c')
    result = s21_acos;
  else if (ch1 == 'a' && ch2 == 's')
    result = s21_asin;
  else if (ch1 == 'a' && ch2 == 't')
    result = s21_atan;
  else if (ch1 == 's' && ch2 == 'q')
    result = s21_sqrt;
  else if (ch1 == 'l' && ch2 == 'n')
    result = s21_ln;
  else if (ch1 == 'l' && ch2 == 'o')
    result = s21_log;
  return result;
}

int Calculator::GetFuncLen(char ch) noexcept {
  int result = 0;
  if (ch == s21_cos || ch == s21_sin || ch == s21_tan || ch == s21_log)
    result = 3;
  else if (ch == s21_acos || ch == s21_asin || ch == s21_atan || ch == s21_sqrt)
    result = 4;
  else if (ch == s21_ln)
    result = 2;
  return result;
}

void Calculator::ProcessDigit(int &i) {
  while (IsDigit(infix_[i]) || infix_[i] == '.') {
    postfix_ += infix_[i];
    i++;
  }
  postfix_ += ' ';
}

void Calculator::ProcessX(int &i) {
  postfix_ += infix_[i];
  i++;
  postfix_ += ' ';
}

void Calculator::ProcessOperator(int &i, std::stack<char> &stack1) {
  std::string funcs_alias("csqtCSTlL");
  int priority1 = -1, priority2 = -1;
  char op_stack = 0;
  while (!stack1.empty()) {
    op_stack = stack1.top();
    stack1.pop();
    priority1 = GetPriority(infix_[i]);
    priority2 = GetPriority(op_stack);
    if (funcs_alias.find(op_stack) != std::string::npos ||
        priority2 >= priority1) {
      postfix_ += op_stack;
      postfix_ += ' ';
    } else {
      stack1.push(op_stack);
      break;
    }
  }
  stack1.push(infix_[i]);
  i++;
}

void Calculator::ProcessRBrace(int &i, std::stack<char> &stack1) {
  while (!stack1.empty()) {
    if (stack1.top() != '(') {
      postfix_ += stack1.top();
      postfix_ += ' ';
      stack1.pop();
    } else {
      stack1.pop();
      break;
    }
  }
  i++;
}

void Calculator::ProcessLBrace(int &i, std::stack<char> &stack1) {
  stack1.push('(');
  i++;
}

void Calculator::ProcessFunc(int &i, std::stack<char> &stack1) {
  char func_alias = GetFuncName(infix_[i], infix_[i + 1]);
  stack1.push(func_alias);
  i += GetFuncLen(func_alias);
}

void Calculator::DigitsToStack(int &i, std::stack<double> &stack1) {
  std::string buffer;
  for (; IsDigit(postfix_[i]) || postfix_[i] == '.'; i++) {
    buffer += postfix_[i];
  }
  double number = std::stod(buffer);
  stack1.push(number);
}

double Calculator::FuncToStack(int &i, std::stack<double> &stack1) {
  double num1 = stack1.top();
  stack1.pop();
  double result = ArithmeticFunc(postfix_[i], num1);
  stack1.push(result);
  return result;
}

std::vector<double> Calculator::GetNumbersFromStack(
    int i, std::stack<double> &stack1) {
  std::vector<double> numbers;

  if (stack1.size() >= 2 && postfix_[i] != '~') {
    numbers.push_back(stack1.top());
    stack1.pop();
    numbers.push_back(stack1.top());
    stack1.pop();
  } else if (!stack1.empty() && postfix_[i] == '~') {
    numbers.push_back(stack1.top());
    stack1.pop();
    numbers.push_back(0);
  } else {
    flag_ = false;
  }

  return numbers;
}
}  // namespace s21