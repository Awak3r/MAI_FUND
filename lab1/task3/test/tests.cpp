#include <gtest/gtest.h>
extern "C" {
#include "../include/func.h"
#include "../include/utils.h"
}

TEST(UtilsTest, IsNumberValid) {
    EXPECT_EQ(is_number("123"), 1);
    EXPECT_EQ(is_number("123.456"), 1);
    EXPECT_EQ(is_number("-123.456"), 1);
    EXPECT_EQ(is_number("0"), 1);
    EXPECT_EQ(is_number("0.0001"), 1);
}

TEST(UtilsTest, IsNumberInvalid) {
    EXPECT_EQ(is_number("abc"), 0);
    EXPECT_EQ(is_number("12.34.56"), 0);
    EXPECT_EQ(is_number(""), 0);
    EXPECT_EQ(is_number(NULL), 0);
    EXPECT_EQ(is_number("12abc"), 0);
}


TEST(UtilsTest, TupoiEpsilonEqual) {
    EXPECT_EQ(tupoi_epsilon(1.0f, 1.0f, 0.0001f), 1);
    EXPECT_EQ(tupoi_epsilon(1.0001f, 1.0f, 0.001f), 1);
    EXPECT_EQ(tupoi_epsilon(5.5f, 5.5f, 0.00001f), 1);
}

TEST(UtilsTest, TupoiEpsilonNotEqual) {
    EXPECT_EQ(tupoi_epsilon(1.0f, 2.0f, 0.0001f), 0);
    EXPECT_EQ(tupoi_epsilon(1.0f, 1.1f, 0.01f), 0);
    EXPECT_EQ(tupoi_epsilon(0.0f, 1.0f, 0.5f), 0);
}


TEST(FuncBTest, IsMultiple) {
    EXPECT_EQ(func_b(10, 5), 1);
    EXPECT_EQ(func_b(100, 10), 1);
    EXPECT_EQ(func_b(15, 3), 1);
    EXPECT_EQ(func_b(7, 7), 1);
}

TEST(FuncBTest, IsNotMultiple) {
    EXPECT_EQ(func_b(10, 3), 0);
    EXPECT_EQ(func_b(7, 5), 0);
    EXPECT_EQ(func_b(100, 7), 0);
}

TEST(FuncBTest, ZeroArguments) {
    EXPECT_EQ(func_b(0, 5), -1);
    EXPECT_EQ(func_b(5, 0), -1);
    EXPECT_EQ(func_b(0, 0), -1);
}

TEST(FuncBTest, NegativeNumbers) {
    EXPECT_EQ(func_b(-10, 5), 1);
    EXPECT_EQ(func_b(10, -5), 1);
    EXPECT_EQ(func_b(-15, -3), 1);
}

TEST(UravnTest, TwoRoots) {
    int length = 0;
    float* res = uravn(1.0f, -5.0f, 6.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, 2);
    EXPECT_NEAR(res[0], 3.0f, 0.001f);
    EXPECT_NEAR(res[1], 2.0f, 0.001f);
    
    free(res);
}

TEST(UravnTest, OneRoot) {
    int length = 0;
    float* res = uravn(1.0f, -2.0f, 1.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, 1);
    EXPECT_NEAR(res[0], 1.0f, 0.001f);
    
    free(res);
}

TEST(UravnTest, NoRoots) {
    int length = 0;
    float* res = uravn(1.0f, 0.0f, 1.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, 0);
    
    free(res);
}

TEST(UravnTest, LinearEquation) {
    int length = 0;
    float* res = uravn(0.0f, 2.0f, -6.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, 1);
    EXPECT_NEAR(res[0], 3.0f, 0.001f);
    
    free(res);
}

TEST(UravnTest, AllCoefficientsZero) {
    int length = 0;
    float* res = uravn(0.0f, 0.0f, 0.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, -1);
    
    free(res);
}

TEST(UravnTest, NoSolutionLinear) {
    int length = 0;
    float* res = uravn(0.0f, 0.0f, 5.0f, 0.0001f, &length);
    
    EXPECT_EQ(length, 0);
    
    free(res);
}

TEST(FuncCTest, RightTriangle345) {
    float coef[3] = {3.0f, 4.0f, 5.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 1);
}

TEST(FuncCTest, RightTriangle51213) {
    float coef[3] = {5.0f, 12.0f, 13.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 1);
}

TEST(FuncCTest, RightTriangle81517) {
    float coef[3] = {8.0f, 15.0f, 17.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 1);
}

TEST(FuncCTest, RightTriangleDifferentOrder) {
    float coef1[3] = {5.0f, 3.0f, 4.0f};
    float coef2[3] = {4.0f, 5.0f, 3.0f};
    
    EXPECT_EQ(func_c(0.0001f, coef1), 1);
    EXPECT_EQ(func_c(0.0001f, coef2), 1);
}

TEST(FuncCTest, NotRightTriangle) {
    float coef[3] = {2.0f, 3.0f, 4.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 0);
}

TEST(FuncCTest, NotTriangleAtAll) {
    float coef[3] = {1.0f, 2.0f, 10.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 0);
}

TEST(FuncCTest, ImpossibleTriangle) {
    float coef[3] = {1.0f, 1.0f, 5.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 0);
}

TEST(FuncCTest, EquilateralTriangle) {
    float coef[3] = {5.0f, 5.0f, 5.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 0);
}

TEST(FuncCTest, IsoscelesNotRight) {
    float coef[3] = {5.0f, 5.0f, 6.0f};
    EXPECT_EQ(func_c(0.0001f, coef), 0);
}

TEST(FuncCTest, ZeroSides) {
    float coef1[3] = {0.0f, 4.0f, 5.0f};
    float coef2[3] = {3.0f, 0.0f, 5.0f};
    float coef3[3] = {3.0f, 4.0f, 0.0f};
    
    EXPECT_EQ(func_c(0.0001f, coef1), 0);
    EXPECT_EQ(func_c(0.0001f, coef2), 0);
    EXPECT_EQ(func_c(0.0001f, coef3), 0);
}

TEST(PermutationTest, UniquePermutation) {
    float perms[3][3] = {
        {1.0f, 2.0f, 3.0f},
        {2.0f, 3.0f, 1.0f},
        {3.0f, 1.0f, 2.0f}
    };
    
    EXPECT_EQ(is_permutation_unique(perms, 3, 4.0f, 5.0f, 6.0f, 0.0001f), 1);
}

TEST(PermutationTest, DuplicatePermutation) {
    float perms[3][3] = {
        {1.0f, 2.0f, 3.0f},
        {2.0f, 3.0f, 1.0f},
        {3.0f, 1.0f, 2.0f}
    };
    
    EXPECT_EQ(is_permutation_unique(perms, 3, 1.0f, 2.0f, 3.0f, 0.0001f), 0);
}

TEST(PermutationTest, EmptyList) {
    float perms[1][3];
    
    EXPECT_EQ(is_permutation_unique(perms, 0, 1.0f, 2.0f, 3.0f, 0.0001f), 1);
}

TEST(PermutationTest, WithEpsilon) {
    float perms[1][3] = {
        {1.0f, 2.0f, 3.0f}
    };
    
    EXPECT_EQ(is_permutation_unique(perms, 1, 1.0001f, 2.0001f, 3.0001f, 0.001f), 0);
    EXPECT_EQ(is_permutation_unique(perms, 1, 1.0001f, 2.0001f, 3.0001f, 0.00001f), 1);
}

