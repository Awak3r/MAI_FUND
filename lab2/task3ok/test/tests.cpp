#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <climits>
#include <iostream>
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
    std::cout << "Test FuncA_SmallNumbers #1: func_a(5), got=\"" << result << "\", expected=\"V\"\n";
    EXPECT_STREQ(result, "V") << "func_a(5)";
    free(result);
    
    result = func_a(9);
    std::cout << "Test FuncA_SmallNumbers #2: func_a(9), got=\"" << result << "\", expected=\"IX\"\n";
    EXPECT_STREQ(result, "IX") << "func_a(9)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_MediumNumbers) {
    char* result = func_a(58);
    std::cout << "Test FuncA_MediumNumbers #1: func_a(58), got=\"" << result << "\", expected=\"LVIII\"\n";
    EXPECT_STREQ(result, "LVIII") << "func_a(58)";
    free(result);
    
    result = func_a(1994);
    std::cout << "Test FuncA_MediumNumbers #2: func_a(1994), got=\"" << result << "\", expected=\"MCMXCIV\"\n";
    EXPECT_STREQ(result, "MCMXCIV") << "func_a(1994)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_LargeNumbers) {
    char* result = func_a(3999);
    std::cout << "Test FuncA_LargeNumbers #1: func_a(3999), got=\"" << result << "\", expected=\"MMMCMXCIX\"\n";
    EXPECT_STREQ(result, "MMMCMXCIX") << "func_a(3999)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncA_Zero) {
    char* result = func_a(0);
    std::cout << "Test FuncA_Zero #1: func_a(0), got=\"" << result << "\", expected=\"\"\n";
    EXPECT_STREQ(result, "") << "func_a(0)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_One) {
    char* result = func_b(1);
    std::cout << "Test FuncB_One #1: func_b(1), got=\"" << result << "\", expected=\"11\"\n";
    EXPECT_STREQ(result, "11") << "func_b(1)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_SmallNumbers) {
    char* result = func_b(10);
    std::cout << "Test FuncB_SmallNumbers #1: func_b(10), got=\"" << result << "\", checking last char='1'\n";
    EXPECT_NE(result, nullptr) << "func_b(10) returned nullptr";
    EXPECT_TRUE(result[strlen(result)-1] == '1') << "func_b(10) last char, got='" << result[strlen(result)-1] << "', expected='1'";
    free(result);
}

TEST_F(CustomPrintfTest, FuncB_Hundred) {
    char* result = func_b(100);
    std::cout << "Test FuncB_Hundred #1: func_b(100), got=\"" << result << "\", checking last char='1'\n";
    EXPECT_NE(result, nullptr) << "func_b(100) returned nullptr";
    EXPECT_TRUE(result[strlen(result)-1] == '1') << "func_b(100) last char, got='" << result[strlen(result)-1] << "', expected='1'";
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Binary) {
    char* result = func_c(15, 2);
    std::cout << "Test FuncC_Binary #1: func_c(15, 2), got=\"" << result << "\", expected=\"1111\"\n";
    EXPECT_STREQ(result, "1111") << "func_c(15, 2)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Hexadecimal) {
    char* result = func_c(255, 16);
    std::cout << "Test FuncC_Hexadecimal #1: func_c(255, 16), got=\"" << result << "\", expected=\"ff\"\n";
    EXPECT_STREQ(result, "ff") << "func_c(255, 16)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_NegativeNumber) {
    char* result = func_c(-10, 10);
    std::cout << "Test FuncC_NegativeNumber #1: func_c(-10, 10), got=\"" << result << "\", expected=\"-10\"\n";
    EXPECT_STREQ(result, "-10") << "func_c(-10, 10)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_Zero) {
    char* result = func_c(0, 10);
    std::cout << "Test FuncC_Zero #1: func_c(0, 10), got=\"" << result << "\", expected=\"\" or \"0\"\n";
    EXPECT_TRUE(strlen(result) == 0 || strcmp(result, "0") == 0) << "func_c(0, 10), got=\"" << result << "\"";
    free(result);
}

TEST_F(CustomPrintfTest, FuncC_InvalidBase) {
    char* result = func_c(100, 50);
    std::cout << "Test FuncC_InvalidBase #1: func_c(100, 50), got=" << (result ? "non-null" : "null") << ", expected=non-null\n";
    EXPECT_NE(result, nullptr) << "func_c(100, 50)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncD_Hexadecimal) {
    char* result = func_d(255, 16);
    std::cout << "Test FuncD_Hexadecimal #1: func_d(255, 16), got=\"" << result << "\", expected=\"FF\"\n";
    EXPECT_STREQ(result, "FF") << "func_d(255, 16)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncD_Base36) {
    char* result = func_d(35, 36);
    std::cout << "Test FuncD_Base36 #1: func_d(35, 36), got=\"" << result << "\", expected=\"Z\"\n";
    EXPECT_STREQ(result, "Z") << "func_d(35, 36)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_PositiveNumber) {
    char* result = func_g(255);
    std::cout << "Test FuncG_PositiveNumber #1: func_g(255), got=\"" << result << "\", checking contains \"11111111\"\n";
    EXPECT_NE(result, nullptr) << "func_g(255) returned nullptr";
    EXPECT_TRUE(strstr(result, "11111111") != nullptr) << "func_g(255), got=\"" << result << "\"";
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_NegativeNumber) {
    char* result = func_g(-1);
    std::cout << "Test FuncG_NegativeNumber #1: func_g(-1), got=\"" << result << "\", checking contains \"11111111\"\n";
    EXPECT_NE(result, nullptr) << "func_g(-1) returned nullptr";
    EXPECT_TRUE(strstr(result, "11111111") != nullptr) << "func_g(-1), got=\"" << result << "\"";
    free(result);
}

TEST_F(CustomPrintfTest, FuncG_Zero) {
    char* result = func_g(0);
    std::cout << "Test FuncG_Zero #1: func_g(0), got=" << (result ? "non-null" : "null") << ", expected=non-null\n";
    EXPECT_NE(result, nullptr) << "func_g(0)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncH_UnsignedMax) {
    char* result = func_h(UINT_MAX);
    std::cout << "Test FuncH_UnsignedMax #1: func_h(UINT_MAX=" << UINT_MAX << "), got=" << (result ? "non-null" : "null") << ", expected=non-null\n";
    EXPECT_NE(result, nullptr) << "func_h(UINT_MAX)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncI_DoublePositive) {
    char* result = func_i(4.25);
    std::cout << "Test FuncI_DoublePositive #1: func_i(4.25), got=" << (result ? "non-null" : "null") << ", length=" << (result ? strlen(result) : 0) << ", expected=71\n";
    EXPECT_NE(result, nullptr) << "func_i(4.25)";
    EXPECT_EQ(strlen(result), 71) << "func_i(4.25) length";
    free(result);
}

TEST_F(CustomPrintfTest, FuncI_DoubleNegative) {
    char* result = func_i(-4.25);
    std::cout << "Test FuncI_DoubleNegative #1: func_i(-4.25), got=" << (result ? "non-null" : "null") << ", expected=non-null\n";
    EXPECT_NE(result, nullptr) << "func_i(-4.25)";
    free(result);
}

TEST_F(CustomPrintfTest, FuncJ_Float) {
    char* result = func_j(3.75f);
    std::cout << "Test FuncJ_Float #1: func_j(3.75f), got=" << (result ? "non-null" : "null") << ", length=" << (result ? strlen(result) : 0) << ", expected=35\n";
    EXPECT_NE(result, nullptr) << "func_j(3.75f)";
    EXPECT_EQ(strlen(result), 35) << "func_j(3.75f) length";
    free(result);
}

TEST_F(CustomPrintfTest, Oversprintf_StandardFlags) {
    oversprintf(buffer, "Number: %d, String: %s", 42, "test");
    std::cout << "Test Oversprintf_StandardFlags #1: oversprintf(..., 42, \"test\"), got=\"" << buffer << "\", expected=\"Number: 42, String: test\"\n";
    EXPECT_STREQ(buffer, "Number: 42, String: test") << "oversprintf standard flags";
}

TEST_F(CustomPrintfTest, Oversprintf_RomanNumerals) {
    oversprintf(buffer, "Roman: %Ro", 1994);
    std::cout << "Test Oversprintf_RomanNumerals #1: oversprintf(\"Roman: %Ro\", 1994), got=\"" << buffer << "\", expected=\"Roman: MCMXCIV\"\n";
    EXPECT_STREQ(buffer, "Roman: MCMXCIV") << "oversprintf %Ro";
}

TEST_F(CustomPrintfTest, Oversprintf_Zeckendorf) {
    oversprintf(buffer, "Zeck: %Zr", 10);
    std::cout << "Test Oversprintf_Zeckendorf #1: oversprintf(\"Zeck: %Zr\", 10), got=\"" << buffer << "\", checking starts with \"Zeck: \"\n";
    EXPECT_NE(strstr(buffer, "Zeck: "), nullptr) << "oversprintf %Zr, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_CustomBase) {
    oversprintf(buffer, "Hex: %Cv", 255, 16);
    std::cout << "Test Oversprintf_CustomBase #1: oversprintf(\"Hex: %Cv\", 255, 16), got=\"" << buffer << "\", expected=\"Hex: ff\"\n";
    EXPECT_STREQ(buffer, "Hex: ff") << "oversprintf %Cv";
}

TEST_F(CustomPrintfTest, Oversprintf_CustomBaseUpper) {
    oversprintf(buffer, "Hex: %CV", 255, 16);
    std::cout << "Test Oversprintf_CustomBaseUpper #1: oversprintf(\"Hex: %CV\", 255, 16), got=\"" << buffer << "\", expected=\"Hex: FF\"\n";
    EXPECT_STREQ(buffer, "Hex: FF") << "oversprintf %CV";
}

TEST_F(CustomPrintfTest, Oversprintf_ToDecimal) {
    oversprintf(buffer, "Dec: %to", "ff", 16);
    std::cout << "Test Oversprintf_ToDecimal #1: oversprintf(\"Dec: %to\", \"ff\", 16), got=\"" << buffer << "\", expected=\"Dec: 255\"\n";
    EXPECT_STREQ(buffer, "Dec: 255") << "oversprintf %to";
}

TEST_F(CustomPrintfTest, Oversprintf_ToDecimalUpper) {
    oversprintf(buffer, "Dec: %TO", "FF", 16);
    std::cout << "Test Oversprintf_ToDecimalUpper #1: oversprintf(\"Dec: %TO\", \"FF\", 16), got=\"" << buffer << "\", expected=\"Dec: 255\"\n";
    EXPECT_STREQ(buffer, "Dec: 255") << "oversprintf %TO";
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpInt) {
    oversprintf(buffer, "Dump: %mi", 255);
    std::cout << "Test Oversprintf_MemoryDumpInt #1: oversprintf(\"Dump: %mi\", 255), got=\"" << buffer << "\", checking contains \"11111111\"\n";
    EXPECT_NE(strstr(buffer, "11111111"), nullptr) << "oversprintf %mi, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpUInt) {
    oversprintf(buffer, "Dump: %mu", 255u);
    std::cout << "Test Oversprintf_MemoryDumpUInt #1: oversprintf(\"Dump: %mu\", 255u), got=\"" << buffer << "\", checking contains \"11111111\"\n";
    EXPECT_NE(strstr(buffer, "11111111"), nullptr) << "oversprintf %mu, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpDouble) {
    oversprintf(buffer, "Dump: %md", 4.25);
    std::cout << "Test Oversprintf_MemoryDumpDouble #1: oversprintf(\"Dump: %md\", 4.25), got=\"" << buffer << "\", checking starts with \"Dump: \"\n";
    EXPECT_NE(strstr(buffer, "Dump: "), nullptr) << "oversprintf %md, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_MemoryDumpFloat) {
    oversprintf(buffer, "Dump: %mf", 3.75f);
    std::cout << "Test Oversprintf_MemoryDumpFloat #1: oversprintf(\"Dump: %mf\", 3.75f), got=\"" << buffer << "\", checking starts with \"Dump: \"\n";
    EXPECT_NE(strstr(buffer, "Dump: "), nullptr) << "oversprintf %mf, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_MixedFlags) {
    oversprintf(buffer, "%d + %Cv = %s", 10, 255, 16, "result");
    std::cout << "Test Oversprintf_MixedFlags #1: oversprintf(\"%d + %Cv = %s\", 10, 255, 16, \"result\"), got=\"" << buffer << "\", checking contains \"10\" and \"ff\"\n";
    EXPECT_NE(strstr(buffer, "10"), nullptr) << "oversprintf mixed flags, got=\"" << buffer << "\"";
    EXPECT_NE(strstr(buffer, "ff"), nullptr) << "oversprintf mixed flags, got=\"" << buffer << "\"";
}

TEST_F(CustomPrintfTest, Oversprintf_Percent) {
    oversprintf(buffer, "100%% complete");
    std::cout << "Test Oversprintf_Percent #1: oversprintf(\"100%% complete\"), got=\"" << buffer << "\", expected=\"100% complete\"\n";
    EXPECT_STREQ(buffer, "100% complete") << "oversprintf %%";
}

TEST_F(CustomPrintfTest, Overfprintf_StandardOutput) {
    overfprintf(testFile, "Test: %d", 42);
    rewind(testFile);
    fgets(buffer, sizeof(buffer), testFile);
    std::cout << "Test Overfprintf_StandardOutput #1: overfprintf(file, \"Test: %d\", 42), got=\"" << buffer << "\", expected=\"Test: 42\"\n";
    EXPECT_STREQ(buffer, "Test: 42") << "overfprintf standard";
}

TEST_F(CustomPrintfTest, Overfprintf_CustomFlags) {
    overfprintf(testFile, "Roman: %Ro", 100);
    rewind(testFile);
    fgets(buffer, sizeof(buffer), testFile);
    std::cout << "Test Overfprintf_CustomFlags #1: overfprintf(file, \"Roman: %Ro\", 100), got=\"" << buffer << "\", expected=\"Roman: C\"\n";
    EXPECT_STREQ(buffer, "Roman: C") << "overfprintf %Ro";
}

TEST_F(CustomPrintfTest, Fibonach_GeneratesSequence) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    std::cout << "Test Fibonach_GeneratesSequence #1: fibonach(&len), len=" << len << ", fib[0]=" << fib[0] << ", fib[1]=" << fib[1] << ", expected len>0, fib[0]=1, fib[1]=1\n";
    EXPECT_GT(len, 0) << "fibonach length";
    EXPECT_EQ(fib[0], 1) << "fibonach fib[0]";
    EXPECT_EQ(fib[1], 1) << "fibonach fib[1]";
    free(fib);
}

TEST_F(CustomPrintfTest, Fibonach_NoOverflow) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    std::cout << "Test Fibonach_NoOverflow #1: fibonach(&len), len=" << len << ", checking len<100 and sequence is increasing\n";
    EXPECT_LT(len, 100) << "fibonach length < 100";
    for (int i = 1; i < len; i++) {
        EXPECT_GE(fib[i], fib[i-1]) << "fibonach[" << i << "]=" << fib[i] << " >= fibonach[" << (i-1) << "]=" << fib[i-1];
    }
    free(fib);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
