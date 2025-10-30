#include <gtest/gtest.h>
#include <cstdio>
#include <climits>
extern "C" {
#include "../include/func.h"
}

class ScanfTest : public ::testing::Test {
protected:
    FILE* testFile;
    
    void SetUp() override {
        testFile = tmpfile();
    }
    
    void TearDown() override {
        if (testFile) {
            fclose(testFile);
        }
    }
    
    // Вспомогательная функция для записи в файл и сброса позиции
    void writeToFile(const char* data) {
        fprintf(testFile, "%s", data);
        rewind(testFile);
    }
};

// ==================== Тесты для oversscanf ====================

TEST_F(ScanfTest, Oversscanf_RomanNumeral_Simple) {
    int result = 0;
    int count = oversscanf("V", "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 5);
}

TEST_F(ScanfTest, Oversscanf_RomanNumeral_Complex) {
    int result = 0;
    int count = oversscanf("MCMXCIV", "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 1994);
}

TEST_F(ScanfTest, Oversscanf_RomanNumeral_Large) {
    int result = 0;
    int count = oversscanf("MMMCMXCIX", "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 3999);
}

TEST_F(ScanfTest, Oversscanf_Zeckendorf_Simple) {
    unsigned int result = 0;
    // Для числа 10: F5+F3 = 5+3+2 = 10, представление: 10101 + завершающая 1
    int count = oversscanf("101011", "%Zr", &result);
    EXPECT_EQ(count, 1);
    EXPECT_NE(result, 0);
}

TEST_F(ScanfTest, Oversscanf_Zeckendorf_One) {
    unsigned int result = 0;
    // Число 1 = F1, представление: 1 + завершающая 1 = "11"
    int count = oversscanf("11", "%Zr", &result);
    EXPECT_EQ(count, 1);
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Binary) {
    int result = 0;
    int count = oversscanf("1111", "%Cv", &result, 2);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 15);
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Hex) {
    int result = 0;
    int count = oversscanf("ff", "%Cv", &result, 16);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255);
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Octal) {
    int result = 0;
    int count = oversscanf("377", "%Cv", &result, 8);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255);
}

TEST_F(ScanfTest, Oversscanf_CustomBaseUpper_Hex) {
    int result = 0;
    int count = oversscanf("FF", "%CV", &result, 16);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255);
}

TEST_F(ScanfTest, Oversscanf_CustomBaseUpper_Base36) {
    int result = 0;
    int count = oversscanf("Z", "%CV", &result, 36);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 35);
}

TEST_F(ScanfTest, Oversscanf_StandardInt) {
    int result = 0;
    int count = oversscanf("42", "%d", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 42);
}

TEST_F(ScanfTest, Oversscanf_StandardUnsigned) {
    unsigned int result = 0;
    int count = oversscanf("255", "%u", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255u);
}



TEST_F(ScanfTest, Oversscanf_StandardHex) {
    int result = 0;
    int count = oversscanf("ff", "%x", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 0xff);
}

TEST_F(ScanfTest, Oversscanf_StandardOctal) {
    int result = 0;
    int count = oversscanf("377", "%o", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 0377);
}

TEST_F(ScanfTest, Oversscanf_StandardString) {
    char result[50] = {0};
    int count = oversscanf("hello", "%s", result);
    EXPECT_EQ(count, 1);
    EXPECT_STREQ(result, "hello");
}

TEST_F(ScanfTest, Oversscanf_StandardChar) {
    char result = 0;
    int count = oversscanf("A", "%c", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 'A');
}

TEST_F(ScanfTest, Oversscanf_PositionN) {
    int pos = 0;
    int num = 0;
    int count = oversscanf("42", "%d%n", &num, &pos);
    EXPECT_EQ(num, 42);
    EXPECT_EQ(pos, 2);  // Позиция после "42"
}

TEST_F(ScanfTest, Oversscanf_Multiple) {
    int a = 0, b = 0;
    int count = oversscanf("10 20", "%d %d", &a, &b);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 20);
}

TEST_F(ScanfTest, Oversscanf_MixedFormats) {
    int roman = 0;
    int decimal = 0;
    int count = oversscanf("X 42", "%Ro %d", &roman, &decimal);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(roman, 10);
    EXPECT_EQ(decimal, 42);
}

TEST_F(ScanfTest, Oversscanf_EmptyString) {
    int result = 0;
    int count = oversscanf("", "%d", &result);
    EXPECT_EQ(count, 0);
}

TEST_F(ScanfTest, Oversscanf_InvalidFormat) {
    int result = 0;
    int count = oversscanf("abc", "%d", &result);
    EXPECT_EQ(count, 0);
}

// ==================== Тесты для overfscanf ====================

TEST_F(ScanfTest, Overfscanf_RomanNumeral_Simple) {
    writeToFile("IX");
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 9);
}

TEST_F(ScanfTest, Overfscanf_RomanNumeral_Complex) {
    writeToFile("MCMXCIV");
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 1994);
}

TEST_F(ScanfTest, Overfscanf_Zeckendorf) {
    writeToFile("11");
    unsigned int result = 0;
    int count = overfscanf(testFile, "%Zr", &result);
    EXPECT_EQ(count, 1);
}

TEST_F(ScanfTest, Overfscanf_CustomBase_Hex) {
    writeToFile("ff");
    int result = 0;
    int count = overfscanf(testFile, "%Cv", &result, 16);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255);
}

TEST_F(ScanfTest, Overfscanf_CustomBaseUpper_Hex) {
    writeToFile("FF");
    int result = 0;
    int count = overfscanf(testFile, "%CV", &result, 16);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 255);
}

TEST_F(ScanfTest, Overfscanf_StandardInt) {
    writeToFile("42");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 42);
}

TEST_F(ScanfTest, Overfscanf_StandardUnsigned) {
    writeToFile("4294967295");
    unsigned int result = 0;
    int count = overfscanf(testFile, "%u", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, UINT_MAX);
}

TEST_F(ScanfTest, Overfscanf_StandardString) {
    writeToFile("world");
    char result[50] = {0};
    int count = overfscanf(testFile, "%s", result);
    EXPECT_EQ(count, 1);
    EXPECT_STREQ(result, "world");
}

TEST_F(ScanfTest, Overfscanf_StandardChar) {
    writeToFile("Z");
    char result = 0;
    int count = overfscanf(testFile, "%c", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 'Z');
}

TEST_F(ScanfTest, Overfscanf_Multiple) {
    writeToFile("100 200 300");
    int a = 0, b = 0, c = 0;
    int count = overfscanf(testFile, "%d %d %d", &a, &b, &c);
    EXPECT_EQ(count, 3);
    EXPECT_EQ(a, 100);
    EXPECT_EQ(b, 200);
    EXPECT_EQ(c, 300);
}

TEST_F(ScanfTest, Overfscanf_MixedFormats) {
    writeToFile("L 50");
    int roman = 0, decimal = 0;
    int count = overfscanf(testFile, "%Ro %d", &roman, &decimal);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(roman, 50);
    EXPECT_EQ(decimal, 50);
}

TEST_F(ScanfTest, Overfscanf_Whitespace) {
    writeToFile("  42  ");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 42);
}

TEST_F(ScanfTest, Overfscanf_Newlines) {
    writeToFile("10\n20\n30");
    int a = 0, b = 0, c = 0;
    int count = overfscanf(testFile, "%d %d %d", &a, &b, &c);
    EXPECT_EQ(count, 3);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 20);
    EXPECT_EQ(c, 30);
}

TEST_F(ScanfTest, Overfscanf_LargeString) {
    // Проверка работы с большими строками (динамическое выделение памяти)
    std::string largeRoman(1000, 'M');  // 1000 символов 'M' = 1000000
    writeToFile(largeRoman.c_str());
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(result, 1000000);
}

TEST_F(ScanfTest, Overfscanf_EmptyFile) {
    writeToFile("");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    EXPECT_EQ(count, 0);
}

TEST_F(ScanfTest, Overfscanf_PositionTracking) {
    writeToFile("42");
    int num = 0, pos = 0;
    int count = overfscanf(testFile, "%d%n", &num, &pos);
    EXPECT_EQ(num, 42);
    EXPECT_GT(pos, 0);  // Позиция должна быть больше 0
}

// ==================== Тесты вспомогательных функций ====================

TEST(FibonachTest, GeneratesSequence) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    ASSERT_NE(fib, nullptr);
    EXPECT_GT(len, 2);
    EXPECT_EQ(fib[0], 1);
    EXPECT_EQ(fib[1], 1);
    EXPECT_EQ(fib[2], 2);
    free(fib);
}

TEST(FibonachTest, NoOverflow) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    ASSERT_NE(fib, nullptr);
    for (int i = 2; i < len; i++) {
        EXPECT_EQ(fib[i], fib[i-1] + fib[i-2]);
    }
    free(fib);
}

TEST(FuncCTest, Binary) {
    int result = func_c((char*)"1111", 2);
    EXPECT_EQ(result, 15);
}

TEST(FuncCTest, Hexadecimal) {
    int result = func_c((char*)"ff", 16);
    EXPECT_EQ(result, 255);
}

TEST(FuncCTest, InvalidBase) {
    int result = func_c((char*)"123", 50);
    EXPECT_EQ(result, 123);  // Должно использовать base=10
}

TEST(FuncDTest, UppercaseHex) {
    int result = func_d((char*)"FF", 16);
    EXPECT_EQ(result, 255);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
    