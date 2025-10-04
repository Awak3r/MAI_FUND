#include <gtest/gtest.h>
#include <stdlib.h>


extern "C" {
    int test_in(char *string, int n);
    int in_to_10number(char *string, int n);
    void convert_to_n(int number, int base, char *result);
}

class NumberConversionTest : public ::testing::Test {
protected:
    void SetUp() override {
        
    }
};


TEST_F(NumberConversionTest, ValidDecimalNumber) {
    char input[] = "123\n";
    EXPECT_EQ(test_in(input, 10), 1);
}

TEST_F(NumberConversionTest, ValidHexadecimalNumber) {
    char input[] = "1AF\n";
    EXPECT_EQ(test_in(input, 16), 1);
}


TEST_F(NumberConversionTest, InvalidCharacterForBase) {
    char input[] = "12G\n";
    EXPECT_EQ(test_in(input, 16), 0);
}


TEST_F(NumberConversionTest, ValidNegativeNumber) {
    char input[] = "-123\n";
    EXPECT_EQ(test_in(input, 10), 1);
}


TEST_F(NumberConversionTest, BinaryToDecimalConversion) {
    char input[] = "1010";
    EXPECT_EQ(in_to_10number(input, 2), 10);
}


TEST_F(NumberConversionTest, HexToDecimalConversion) {
    char input[] = "1A";
    EXPECT_EQ(in_to_10number(input, 16), 26);
}


TEST_F(NumberConversionTest, NegativeNumberConversion) {
    char input[] = "-123";
    EXPECT_EQ(in_to_10number(input, 10), -123);
}


TEST_F(NumberConversionTest, ConvertToBinary) {
    char result[100];
    convert_to_n(10, 2, result);
    EXPECT_STREQ(result, "1010");
}


TEST_F(NumberConversionTest, ConvertToHexadecimal) {
    char result[100];
    convert_to_n(255, 16, result);
    EXPECT_STREQ(result, "FF");
}


TEST_F(NumberConversionTest, ConvertZero) {
    char result[100];
    convert_to_n(0, 10, result);
    EXPECT_STREQ(result, "0");
}


TEST_F(NumberConversionTest, ConvertNegativeNumber) {
    char result[100];
    convert_to_n(-123, 10, result);
    EXPECT_STREQ(result, "-123");
}


TEST_F(NumberConversionTest, ConvertToBase9) {
    char result[100];
    convert_to_n(81, 9, result);
    EXPECT_STREQ(result, "100");
}


TEST_F(NumberConversionTest, ConvertToBase18) {
    char result[100];
    convert_to_n(35, 18, result);
    EXPECT_STREQ(result, "1H");
}


TEST_F(NumberConversionTest, ConvertToBase27) {
    char result[100];
    convert_to_n(53, 27, result);
    EXPECT_STREQ(result, "1Q");
}


TEST_F(NumberConversionTest, ConvertToBase36) {
    char result[100];
    convert_to_n(35, 36, result);
    EXPECT_STREQ(result, "Z");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}