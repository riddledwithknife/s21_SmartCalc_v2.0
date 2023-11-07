cmake_minimum_required(VERSION 3.5)
project(SmartCalcTest LANGUAGES CXX)

enable_testing()
find_package(GTest)

set(APP_TESTS
        s21_calculator_test.cc
        s21_checker_test.cc
        s21_finance_test.cc
        tests.cc

        ../Model/s21_calculator.cc
        ../Model/s21_calculator.h
        ../Model/s21_checker.cc
        ../Model/s21_checker.h
        ../Model/s21_finance.cc
        ../Model/s21_finance.h
)

add_executable(SmartCalcTest ${APP_TESTS})

target_link_libraries(SmartCalcTest PRIVATE GTest::GTest GTest::Main)

add_test(NAME SmartCalcTest COMMAND SmartCalcTest)