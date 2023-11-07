#include "../Model/s21_checker.h"

#include <gtest/gtest.h>

#include <string>

TEST(CheckerTest, CorrectSigns) {
  s21::Checker expression("1+2-3*4/5^6%7");

  EXPECT_TRUE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectSings_1) {
  s21::Checker expression("1 | 2");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectSings_2) {
  s21::Checker expression("1 ++ 2");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectSings_3) {
  s21::Checker expression("1 */ 2");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, CorrectParen) {
  s21::Checker expression("(1 - 2) * 2");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectParen) {
  s21::Checker expression(")1 - 2( * 2");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, CorrectFuncs) {
  s21::Checker expression("5*sin(cos(log(ln(x))))");

  EXPECT_TRUE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectFuncs_1) {
  s21::Checker expression("son(x)");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectFuncs_2) {
  s21::Checker expression("osin(x)");

  EXPECT_FALSE(expression.IsCorrect());
}

TEST(CheckerTest, IncorrectFuncs_3) {
  s21::Checker expression("ycos(x)");

  EXPECT_FALSE(expression.IsCorrect());
}
