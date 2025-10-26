#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <climits>
extern "C" {
#include "../include/func.h"
}

class CustomPrintfTest : public ::testing::Test {
protected:
    char buffer[2048];
    FILE* testFile;
    
    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
        testFile = tmpfile();
    }
    
    void TearDown() override {
        if (testFile) {
            fclose(testFile);
        }
    }
};

TEST_F(CustomPrintfTest, FuncA_SmallNumbers) {
    char* result = func_a(5);
    EXPECT_STREQ(result, "V");
    free(result);
    
    result = func_a(9);
    EXPECT_STREQ(result, "IX");
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_MediumNumbers) {
    char* result = func_a(58);
    EXPECT_STREQ(result, "LVIII");
    free(result);
    
    result = func_a(1994);
    EXPECT_STREQ(result, "MCMXCIV");
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_LargeNumbers) {
    char* result = func_a(3999);
    EXPECT_STREQ(result, "MMMCMXCIX");
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_Zero) {
    char* result = func_a(0);
    EXPECT_STREQ(result, "");
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_One) {
    char* result = func_b(1);
    EXPECT_STREQ(result, "11");
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_SmallNumbers) {
    char* result = func_b(10);
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(result[strlen(result)-1] == '1'); 
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_Hundred) {
    char* result = func_b(100);
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(result[strlen(result)-1] == '1');
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Binary) {
    char* result = func_c(15, 2);
    EXPECT_STREQ(result, "1111");
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Hexadecimal) {
    char* result = func_c(255, 16);
    EXPECT_STREQ(result, "ff");
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_NegativeNumber) {
    char* result = func_c(-10, 10);
    EXPECT_STREQ(result, "-10");
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Zero) {
    char* result = func_c(0, 10);
    EXPECT_TRUE(strlen(result) == 0 || strcmp(result, "0") == 0);
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_InvalidBase) {
    char* result = func_c(100, 50);
    EXPECT_NE(result, nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncD_Hexadecimal) {
    char* result = func_d(255, 16);
    EXPECT_STREQ(result, "FF");
    free(result);
}

TEST_F(CustomPrintfTest, FuncD_Base36) {
    char* result = func_d(35, 36);
    EXPECT_STREQ(result, "Z");
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_PositiveNumber) {
    char* result = func_g(255);
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(strstr(result, "11111111") != nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_NegativeNumber) {
    char* result = func_g(-1);
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(strstr(result, "11111111") != nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_Zero) {
    char* result = func_g(0);
    EXPECT_NE(result, nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncH_UnsignedMax) {
    char* result = func_h(UINT_MAX);
    EXPECT_NE(result, nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncI_DoublePositive) {
    char* result = func_i(4.25);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 71); 
    free(result);
}

TEST_F(CustomPrintfTest, FuncI_DoubleNegative) {
    char* result = func_i(-4.25);
    EXPECT_NE(result, nullptr);
    free(result);
}

TEST_F(CustomPrintfTest, FuncJ_Float) {
    char* result = func_j(3.75f);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 35); 
    free(result);
}


TEST_F(CustomPrintfTest, Oversprintf_StandardFlags) {
    oversprintf(buffer, "Number: %d, String: %s", 42, "test");
    EXPECT_STREQ(buffer, "Number: 42, String: test");
}

TEST_F(CustomPrintfTest, Oversprintf_RomanNumerals) {
    oversprintf(buffer, "Roman: %Ro", 1994);
    EXPECT_STREQ(buffer, "Roman: MCMXCIV");
}

TEST_F(CustomPrintfTest, Oversprintf_Zeckendorf) {
    oversprintf(buffer, "Zeck: %Zr", 10);
    EXPECT_NE(strstr(buffer, "Zeck: "), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_CustomBase) {
    oversprintf(buffer, "Hex: %Cv", 255, 16);
    EXPECT_STREQ(buffer, "Hex: ff");
}

TEST_F(CustomPrintfTest, Oversprintf_CustomBaseUpper) {
    oversprintf(buffer, "Hex: %CV", 255, 16);
    EXPECT_STREQ(buffer, "Hex: FF");
}

TEST_F(CustomPrintfTest, Oversprintf_ToDecimal) {
    oversprintf(buffer, "Dec: %to", "ff", 16);
    EXPECT_STREQ(buffer, "Dec: 255");
}

TEST_F(CustomPrintfTest, Oversprintf_ToDecimalUpper) {
    oversprintf(buffer, "Dec: %TO", "FF", 16);
    EXPECT_STREQ(buffer, "Dec: 255");
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpInt) {
    oversprintf(buffer, "Dump: %mi", 255);
    EXPECT_NE(strstr(buffer, "11111111"), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpUInt) {
    oversprintf(buffer, "Dump: %mu", 255u);
    EXPECT_NE(strstr(buffer, "11111111"), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpDouble) {
    oversprintf(buffer, "Dump: %md", 4.25);
    EXPECT_NE(strstr(buffer, "Dump: "), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpFloat) {
    oversprintf(buffer, "Dump: %mf", 3.75f);
    EXPECT_NE(strstr(buffer, "Dump: "), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_MixedFlags) {
    oversprintf(buffer, "%d + %Cv = %s", 10, 255, 16, "result");
    EXPECT_NE(strstr(buffer, "10"), nullptr);
    EXPECT_NE(strstr(buffer, "ff"), nullptr);
}

TEST_F(CustomPrintfTest, Oversprintf_Percent) {
    oversprintf(buffer, "100%% complete");
    EXPECT_STREQ(buffer, "100% complete");
}

TEST_F(CustomPrintfTest, Overfprintf_StandardOutput) {
    overfprintf(testFile, "Test: %d", 42);
    rewind(testFile);
    fgets(buffer, sizeof(buffer), testFile);
    EXPECT_STREQ(buffer, "Test: 42");
}

TEST_F(CustomPrintfTest, Overfprintf_CustomFlags) {
    overfprintf(testFile, "Roman: %Ro", 100);
    rewind(testFile);
    fgets(buffer, sizeof(buffer), testFile);
    EXPECT_STREQ(buffer, "Roman: C");
}

TEST_F(CustomPrintfTest, Fibonach_GeneratesSequence) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    EXPECT_GT(len, 0);
    EXPECT_EQ(fib[0], 1);
    EXPECT_EQ(fib[1], 2);
    free(fib);
}

TEST_F(CustomPrintfTest, Fibonach_NoOverflow) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    EXPECT_LT(len, 100);
    for (int i = 1; i < len; i++) {
        EXPECT_GE(fib[i], fib[i-1]);
    }
    free(fib);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
