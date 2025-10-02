#include <gtest/gtest.h>
extern "C" {
#include "../include/func.h"
#include "../include/utils.h"
}

TEST(FuncATest, PositiveNumber) {
    int len = 0;
    int* result = func_a(10, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(len, 0);
    EXPECT_EQ(result[0], 20); 
    EXPECT_EQ(result[1], 30);  
    EXPECT_EQ(result[len-1], 100); 
    free(result);
}

TEST(FuncATest, NegativeNumber) {
    int len = 0;
    int* result = func_a(-10, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(len, 0);
    EXPECT_EQ(result[0], 20);  
    free(result);
}

TEST(FuncATest, OutOfRange) {
    int len = 0;
    int* result = func_a(51, &len);
    EXPECT_EQ(result, nullptr);
    
    result = func_a(-51, &len);
    EXPECT_EQ(result, nullptr);
}

TEST(FuncATest, EdgeCase50) {
    int len = 0;
    int* result = func_a(50, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(result[0], 100);  
    free(result);
}

TEST(FuncATest, SmallNumber) {
    int len = 0;
    int* result = func_a(1, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(len, 50);  
    free(result);
}

TEST(FuncBTest, PrimeNumbers) {
    EXPECT_EQ(func_b(2), 1);
    EXPECT_EQ(func_b(3), 1);
    EXPECT_EQ(func_b(5), 1);
    EXPECT_EQ(func_b(7), 1);
    EXPECT_EQ(func_b(11), 1);
    EXPECT_EQ(func_b(97), 1);
}

TEST(FuncBTest, CompositeNumbers) {
    EXPECT_EQ(func_b(4), 0);
    EXPECT_EQ(func_b(6), 0);
    EXPECT_EQ(func_b(8), 0);
    EXPECT_EQ(func_b(9), 0);
    EXPECT_EQ(func_b(100), 0);
}

TEST(FuncBTest, EdgeCases) {
    EXPECT_EQ(func_b(0), 0);
    EXPECT_EQ(func_b(1), 0);
    EXPECT_EQ(func_b(-5), 0);
}

TEST(FuncCTest, Zero) {
    int len = 0;
    int* result = func_c(0, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(result[0], 0);
    free(result);
}

TEST(FuncCTest, SmallNumbers) {
    int len = 0;
    int* result = func_c(15, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 1);
    EXPECT_EQ(result[0], 15);  
    
    result = func_c(16, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(result[0], 0); 
    EXPECT_EQ(result[1], 1);  
    free(result);
}

TEST(FuncCTest, LargeNumber) {
    int len = 0;
    int* result = func_c(255, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 2);
    EXPECT_EQ(result[0], 15);  
    EXPECT_EQ(result[1], 15); 
    free(result);
}

TEST(FuncCTest, PowerOfTwo) {
    int len = 0;
    int* result = func_c(256, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 1);  
    free(result);
}

TEST(FuncETest, PositiveNumbers) {
    EXPECT_EQ(func_e(0), 0);
    EXPECT_EQ(func_e(1), 1); 
    EXPECT_EQ(func_e(5), 15);  
    EXPECT_EQ(func_e(10), 55); 
}

TEST(FuncETest, NegativeInput) {
    EXPECT_EQ(func_e(-1), -1);
    EXPECT_EQ(func_e(-10), -1);
}

TEST(FuncETest, LargeNumber) {
    EXPECT_EQ(func_e(100), 5050);
}

TEST(FuncFTest, SmallNumbers) {
    EXPECT_EQ(func_f(0), 1);
    EXPECT_EQ(func_f(1), 1);
    EXPECT_EQ(func_f(2), 2);
    EXPECT_EQ(func_f(3), 6);
    EXPECT_EQ(func_f(4), 24);
    EXPECT_EQ(func_f(5), 120);
}

TEST(FuncFTest, MediumNumbers) {
    EXPECT_EQ(func_f(10), 3628800);
}

TEST(FuncFTest, InvalidInput) {
    EXPECT_EQ(func_f(-1), -1);
    EXPECT_EQ(func_f(21), -1);  
    EXPECT_EQ(func_f(100), -1);
}

TEST(FuncFTest, EdgeCase20) {
    EXPECT_EQ(func_f(20), 2432902008176640000LL);
}

TEST(UtilsTest, Factorial) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(-1), -1);
    EXPECT_EQ(factorial(21), -1);
}

TEST(UtilsTest, Sum) {
    EXPECT_EQ(sum(0), 0);
    EXPECT_EQ(sum(10), 55);
    EXPECT_EQ(sum(-1), -1);
}

TEST(UtilsTest, IsPrime) {
    EXPECT_EQ(is_simple(2), 1);
    EXPECT_EQ(is_simple(17), 1);
    EXPECT_EQ(is_simple(4), 0);
    EXPECT_EQ(is_simple(1), 0);
}

TEST(UtilsTest, IntToHex) {
    int len = 0;
    int* result = int_to_hex(0, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 1);
    free(result);
    
    result = int_to_hex(255, &len);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(len, 2);
    free(result);
}

TEST(IntegrationTest, MultipleCallsFuncA) {
    int len1 = 0, len2 = 0, len3 = 0;
    int* r1 = func_a(5, &len1);
    int* r2 = func_a(10, &len2);
    int* r3 = func_a(20, &len3);
    
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    ASSERT_NE(r3, nullptr);
    
    EXPECT_GT(len1, len2);  
    EXPECT_GT(len2, len3);  
    
    free(r1);
    free(r2);
    free(r3);
}

TEST(IntegrationTest, AllFunctions) {
    int len = 0;
    
 
    int* arr = func_a(7, &len);
    ASSERT_NE(arr, nullptr);
    free(arr);

    EXPECT_EQ(func_b(7), 1);
    

    int* hex = func_c(7, &len);
    ASSERT_NE(hex, nullptr);
    free(hex);
 
    EXPECT_EQ(func_e(7), 28);
    

    EXPECT_EQ(func_f(7), 5040);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}