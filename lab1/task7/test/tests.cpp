#include <gtest/gtest.h>

extern "C" {
#include "../include/func.h"
}

TEST(MaxSchislTest, BinaryNumber) {
    char number[] = "1010";
    int result = max_schisl(number, 4);
    EXPECT_NE(result, -1);
}


TEST(MaxSchislTest, DecimalNumber) {
    char number[] = "123";
    int result = max_schisl(number, 3);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, HexadecimalNumber) {
    char number[] = "1A3F";
    int result = max_schisl(number, 4);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, SingleDigit) {
    char number[] = "7";
    int result = max_schisl(number, 1);
    EXPECT_NE(result, -1);
}


TEST(MaxSchislTest, LeadingZeros) {
    char number[] = "00123";
    int result = max_schisl(number, 5);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, OnlyZero) {
    char number[] = "0";
    int result = max_schisl(number, 1);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, MaxBase36) {
    char number[] = "Z";
    int result = max_schisl(number, 1);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, LowercaseLetters) {
    char number[] = "abc";
    int result = max_schisl(number, 3);
    EXPECT_NE(result, -1);
}


TEST(MaxSchislTest, MixedCase) {
    char number[] = "AbC";
    int result = max_schisl(number, 3);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, InvalidCharacter) {
    char number[] = "12@34";
    int result = max_schisl(number, 5);
    EXPECT_EQ(result, -1);
}

TEST(MaxSchislTest, Base8Number) {
    char number[] = "755";
    int result = max_schisl(number, 3);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, LargeBase36Number) {
    char number[] = "ZZZZZ";
    int result = max_schisl(number, 5);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, NumberWith9) {
    char number[] = "999";
    int result = max_schisl(number, 3);
    EXPECT_NE(result, -1);
}

TEST(MaxSchislTest, CombinedTest) {
    char num1[] = "1010";
    char num2[] = "FF";
    char num3[] = "777";
    
    EXPECT_NE(max_schisl(num1, 4), -1); 
    EXPECT_NE(max_schisl(num2, 2), -1);
    EXPECT_NE(max_schisl(num3, 3), -1); 
}

TEST(MaxSchislTest, InvalidCharacterExclamation) {
    char number[] = "12!45";
    int result = max_schisl(number, 5);
    EXPECT_EQ(result, -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}