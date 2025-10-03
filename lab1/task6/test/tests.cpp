#include <gtest/gtest.h>
extern "C" {
#include "../include/func.h"
#include <math.h>
}

// Тесты для func_a: ln(1+x)/x
TEST(FuncATest, AtZero) {
    double result = func_a(0.0, 1e-6);
    EXPECT_NEAR(result, 1.0, 1e-5);  // Предел равен 1
}

TEST(FuncATest, AtHalf) {
    double result = func_a(0.5, 1e-6);
    EXPECT_NEAR(result, log(1.5)/0.5, 1e-5);
}

TEST(FuncATest, AtOne) {
    double result = func_a(1.0, 1e-6);
    EXPECT_NEAR(result, log(2.0), 1e-5);
}

TEST(FuncATest, NearZero) {
    double result = func_a(1e-8, 1e-6);
    EXPECT_NEAR(result, 1.0, 1e-3);  // Должен вернуть предел
}

// Тесты для func_b: e^(-x^2/2)
TEST(FuncBTest, AtZero) {
    double result = func_b(0.0, 1e-6);
    EXPECT_NEAR(result, 1.0, 1e-5);
}

TEST(FuncBTest, AtOne) {
    double result = func_b(1.0, 1e-6);
    EXPECT_NEAR(result, exp(-0.5), 1e-5);
}

TEST(FuncBTest, AtHalf) {
    double result = func_b(0.5, 1e-6);
    EXPECT_NEAR(result, exp(-0.125), 1e-5);
}

// Тесты для func_c: -ln(1-x)
TEST(FuncCTest, AtZero) {
    double result = func_c(0.0, 1e-6);
    EXPECT_NEAR(result, 0.0, 1e-5);
}

TEST(FuncCTest, AtHalf) {
    double result = func_c(0.5, 1e-6);
    EXPECT_NEAR(result, -log(0.5), 1e-5);
}

TEST(FuncCTest, NearOne) {
    double result = func_c(0.9999999, 1e-6);
    EXPECT_GT(result, 0.0);  // Должно быть положительным большим числом
}

// Тесты для func_d: x^x
TEST(FuncDTest, AtZero) {
    double result = func_d(0.0, 1e-6);
    EXPECT_NEAR(result, 1.0, 1e-5);  // Предел равен 1
}

TEST(FuncDTest, AtOne) {
    double result = func_d(1.0, 1e-6);
    EXPECT_NEAR(result, 1.0, 1e-5);
}

TEST(FuncDTest, AtHalf) {
    double result = func_d(0.5, 1e-6);
    EXPECT_NEAR(result, pow(0.5, 0.5), 1e-5);
}

// Тесты для integral
TEST(IntegralTest, FunctionA) {
    double result = integral(1e-4, 'a');
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 2.0);  // Интеграл должен быть в разумных пределах
}

TEST(IntegralTest, FunctionB) {
    double result = integral(1e-4, 'b');
    EXPECT_GT(result, 0.5);
    EXPECT_LT(result, 1.0);  // Интеграл гауссианы от 0 до 1
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}