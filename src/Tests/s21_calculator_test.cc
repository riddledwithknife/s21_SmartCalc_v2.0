#include "../Model/s21_calculator.h"

#include <gtest/gtest.h>

TEST(CalculatorTest, CorrectCalculation_1) {
  s21::Calculator calc;

  double value = calc.Calculate("5 + 2", 0);
  EXPECT_EQ(value, 7);
}

TEST(CalculatorTest, CorrectCalculation_2) {
  s21::Calculator calc;

  double value = calc.Calculate("5 - 2", 0);
  EXPECT_EQ(value, 3);
}

TEST(CalculatorTest, CorrectCalculation_3) {
  s21::Calculator calc;

  double value = calc.Calculate("5 * 2", 0);
  EXPECT_EQ(value, 10);
}

TEST(CalculatorTest, CorrectCalculation_4) {
  s21::Calculator calc;

  double value = calc.Calculate("5 / 2", 0);
  EXPECT_EQ(value, 2.5);
}

TEST(CalculatorTest, CorrectCalculation_5) {
  s21::Calculator calc;

  double value = calc.Calculate("5 % 2", 0);
  EXPECT_EQ(value, 1);
}

TEST(CalculatorTest, CorrectCalculation_6) {
  s21::Calculator calc;

  double value = calc.Calculate("5 ^ 2", 0);
  EXPECT_EQ(value, 25);
}

TEST(CalculatorTest, CorrectFunctionSin) {
  s21::Calculator calc;

  double value = calc.Calculate("sin(1)", 0);
  EXPECT_EQ(value, 0.8414709848078965);
}

TEST(CalculatorTest, CorrectFunctionSinX) {
  s21::Calculator calc;

  double value = calc.Calculate("sin(x)", 3);
  EXPECT_EQ(value, 0.14112000805986721);
}

TEST(CalculatorTest, CorrectFunctionCos) {
  s21::Calculator calc;

  double value = calc.Calculate("cos(1)", 0);
  EXPECT_EQ(value, 0.54030230586813977);
}

TEST(CalculatorTest, CorrectFunctionCosX) {
  s21::Calculator calc;

  double value = calc.Calculate("cos(x)", 3);
  EXPECT_EQ(value, -0.98999249660044542);
}

TEST(CalculatorTest, CorrectFunctionTan) {
  s21::Calculator calc;

  double value = calc.Calculate("tan(1)", 0);
  EXPECT_EQ(value, 1.5574077246549021);
}

TEST(CalculatorTest, CorrectFunctionTanX) {
  s21::Calculator calc;

  double value = calc.Calculate("tan(x)", -1);
  EXPECT_EQ(value, -1.5574077246549021);
}

TEST(CalculatorTest, CorrectFunctionSqrt) {
  s21::Calculator calc;

  double value = calc.Calculate("sqrt(4)", 0);
  EXPECT_EQ(value, 2);
}

TEST(CalculatorTest, CorrectFunctionSqrtX) {
  s21::Calculator calc;

  double value = calc.Calculate("sqrt(x)", 4);
  EXPECT_EQ(value, 2);
}

TEST(CalculatorTest, CorrectFunctionLn) {
  s21::Calculator calc;

  double value = calc.Calculate("ln(10)", 0);
  EXPECT_EQ(value, 2.3025850929940459);
}

TEST(CalculatorTest, CorrectFunctionLog) {
  s21::Calculator calc;

  double value = calc.Calculate("log(10)", 0);
  EXPECT_EQ(value, 1);
}