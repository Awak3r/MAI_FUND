#include <gtest/gtest.h>
#include <cstdio>
#include <climits>
#include <iostream>
#include <string>
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
    
    void writeToFile(const char* data) {
        fprintf(testFile, "%s", data);
        rewind(testFile);
    }
};


TEST_F(ScanfTest, Oversscanf_RomanNumeral_Simple) {
    int result = 0;
    int count = oversscanf("V", "%Ro", &result);
    std::cout << "Test Oversscanf_RomanNumeral_Simple: input=\"V\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=5, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"V\", \"%Ro\") count";
    EXPECT_EQ(result, 5) << "oversscanf(\"V\", \"%Ro\") result";
}

TEST_F(ScanfTest, Oversscanf_RomanNumeral_Complex) {
    int result = 0;
    int count = oversscanf("MCMXCIV", "%Ro", &result);
    std::cout << "Test Oversscanf_RomanNumeral_Complex: input=\"MCMXCIV\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=1994, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"MCMXCIV\", \"%Ro\") count";
    EXPECT_EQ(result, 1994) << "oversscanf(\"MCMXCIV\", \"%Ro\") result";
}

TEST_F(ScanfTest, Oversscanf_RomanNumeral_Large) {
    int result = 0;
    int count = oversscanf("MMMCMXCIX", "%Ro", &result);
    std::cout << "Test Oversscanf_RomanNumeral_Large: input=\"MMMCMXCIX\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=3999, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"MMMCMXCIX\", \"%Ro\") count";
    EXPECT_EQ(result, 3999) << "oversscanf(\"MMMCMXCIX\", \"%Ro\") result";
}

TEST_F(ScanfTest, Oversscanf_Zeckendorf_Simple) {
    unsigned int result = 0;
    int count = oversscanf("101011", "%Zr", &result);
    std::cout << "Test Oversscanf_Zeckendorf_Simple: input=\"101011\", format=\"%Zr\", got result=" << result << ", count=" << count << ", expected result!=0, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"101011\", \"%Zr\") count";
    EXPECT_NE(result, 0u) << "oversscanf(\"101011\", \"%Zr\") result";
}

TEST_F(ScanfTest, Oversscanf_Zeckendorf_One) {
    unsigned int result = 0;
    int count = oversscanf("11", "%Zr", &result);
    std::cout << "Test Oversscanf_Zeckendorf_One: input=\"11\", format=\"%Zr\", got result=" << result << ", count=" << count << ", expected count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"11\", \"%Zr\") count";
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Binary) {
    int result = 0;
    int count = oversscanf("1111", "%Cv", &result, 2);
    std::cout << "Test Oversscanf_CustomBase_Binary: input=\"1111\", format=\"%Cv\", base=2, got result=" << result << ", count=" << count << ", expected result=15, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"1111\", \"%Cv\", base=2) count";
    EXPECT_EQ(result, 15) << "oversscanf(\"1111\", \"%Cv\", base=2) result";
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Hex) {
    int result = 0;
    int count = oversscanf("ff", "%Cv", &result, 16);
    std::cout << "Test Oversscanf_CustomBase_Hex: input=\"ff\", format=\"%Cv\", base=16, got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"ff\", \"%Cv\", base=16) count";
    EXPECT_EQ(result, 255) << "oversscanf(\"ff\", \"%Cv\", base=16) result";
}

TEST_F(ScanfTest, Oversscanf_CustomBase_Octal) {
    int result = 0;
    int count = oversscanf("377", "%Cv", &result, 8);
    std::cout << "Test Oversscanf_CustomBase_Octal: input=\"377\", format=\"%Cv\", base=8, got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"377\", \"%Cv\", base=8) count";
    EXPECT_EQ(result, 255) << "oversscanf(\"377\", \"%Cv\", base=8) result";
}

TEST_F(ScanfTest, Oversscanf_CustomBaseUpper_Hex) {
    int result = 0;
    int count = oversscanf("FF", "%CV", &result, 16);
    std::cout << "Test Oversscanf_CustomBaseUpper_Hex: input=\"FF\", format=\"%CV\", base=16, got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"FF\", \"%CV\", base=16) count";
    EXPECT_EQ(result, 255) << "oversscanf(\"FF\", \"%CV\", base=16) result";
}

TEST_F(ScanfTest, Oversscanf_CustomBaseUpper_Base36) {
    int result = 0;
    int count = oversscanf("Z", "%CV", &result, 36);
    std::cout << "Test Oversscanf_CustomBaseUpper_Base36: input=\"Z\", format=\"%CV\", base=36, got result=" << result << ", count=" << count << ", expected result=35, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"Z\", \"%CV\", base=36) count";
    EXPECT_EQ(result, 35) << "oversscanf(\"Z\", \"%CV\", base=36) result";
}

TEST_F(ScanfTest, Oversscanf_StandardInt) {
    int result = 0;
    int count = oversscanf("42", "%d", &result);
    std::cout << "Test Oversscanf_StandardInt: input=\"42\", format=\"%d\", got result=" << result << ", count=" << count << ", expected result=42, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"42\", \"%d\") count";
    EXPECT_EQ(result, 42) << "oversscanf(\"42\", \"%d\") result";
}

TEST_F(ScanfTest, Oversscanf_StandardUnsigned) {
    unsigned int result = 0;
    int count = oversscanf("255", "%u", &result);
    std::cout << "Test Oversscanf_StandardUnsigned: input=\"255\", format=\"%u\", got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"255\", \"%u\") count";
    EXPECT_EQ(result, 255u) << "oversscanf(\"255\", \"%u\") result";
}

TEST_F(ScanfTest, Oversscanf_StandardHex) {
    int result = 0;
    int count = oversscanf("ff", "%x", &result);
    std::cout << "Test Oversscanf_StandardHex: input=\"ff\", format=\"%x\", got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"ff\", \"%x\") count";
    EXPECT_EQ(result, 0xff) << "oversscanf(\"ff\", \"%x\") result";
}

TEST_F(ScanfTest, Oversscanf_StandardOctal) {
    int result = 0;
    int count = oversscanf("377", "%o", &result);
    std::cout << "Test Oversscanf_StandardOctal: input=\"377\", format=\"%o\", got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"377\", \"%o\") count";
    EXPECT_EQ(result, 0377) << "oversscanf(\"377\", \"%o\") result";
}

TEST_F(ScanfTest, Oversscanf_StandardString) {
    char result[50] = {0};
    int count = oversscanf("hello", "%s", result);
    std::cout << "Test Oversscanf_StandardString: input=\"hello\", format=\"%s\", got result=\"" << result << "\", count=" << count << ", expected result=\"hello\", count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"hello\", \"%s\") count";
    EXPECT_STREQ(result, "hello") << "oversscanf(\"hello\", \"%s\") result";
}

TEST_F(ScanfTest, Oversscanf_StandardChar) {
    char result = 0;
    int count = oversscanf("A", "%c", &result);
    std::cout << "Test Oversscanf_StandardChar: input=\"A\", format=\"%c\", got result='" << result << "', count=" << count << ", expected result='A', count=1\n";
    EXPECT_EQ(count, 1) << "oversscanf(\"A\", \"%c\") count";
    EXPECT_EQ(result, 'A') << "oversscanf(\"A\", \"%c\") result";
}

TEST_F(ScanfTest, Oversscanf_PositionN) {
    int pos = 0;
    int num = 0;
    int count = oversscanf("42", "%d%n", &num, &pos);
    std::cout << "Test Oversscanf_PositionN: input=\"42\", format=\"%d%n\", got num=" << num << ", pos=" << pos << ", count=" << count << ", expected num=42, pos=2\n";
    EXPECT_EQ(num, 42) << "oversscanf(\"42\", \"%d%n\") num";
    EXPECT_EQ(pos, 2) << "oversscanf(\"42\", \"%d%n\") pos";
}

TEST_F(ScanfTest, Oversscanf_Multiple) {
    int a = 0, b = 0;
    int count = oversscanf("10 20", "%d %d", &a, &b);
    std::cout << "Test Oversscanf_Multiple: input=\"10 20\", format=\"%d %d\", got a=" << a << ", b=" << b << ", count=" << count << ", expected a=10, b=20, count=2\n";
    EXPECT_EQ(count, 2) << "oversscanf(\"10 20\", \"%d %d\") count";
    EXPECT_EQ(a, 10) << "oversscanf(\"10 20\", \"%d %d\") a";
    EXPECT_EQ(b, 20) << "oversscanf(\"10 20\", \"%d %d\") b";
}

TEST_F(ScanfTest, Oversscanf_MixedFormats) {
    int roman = 0;
    int decimal = 0;
    int count = oversscanf("X 42", "%Ro %d", &roman, &decimal);
    std::cout << "Test Oversscanf_MixedFormats: input=\"X 42\", format=\"%Ro %d\", got roman=" << roman << ", decimal=" << decimal << ", count=" << count << ", expected roman=10, decimal=42, count=2\n";
    EXPECT_EQ(count, 2) << "oversscanf(\"X 42\", \"%Ro %d\") count";
    EXPECT_EQ(roman, 10) << "oversscanf(\"X 42\", \"%Ro %d\") roman";
    EXPECT_EQ(decimal, 42) << "oversscanf(\"X 42\", \"%Ro %d\") decimal";
}

TEST_F(ScanfTest, Oversscanf_EmptyString) {
    int result = 0;
    int count = oversscanf("", "%d", &result);
    std::cout << "Test Oversscanf_EmptyString: input=\"\", format=\"%d\", got count=" << count << ", expected count=0\n";
    EXPECT_EQ(count, 0) << "oversscanf(\"\", \"%d\") count";
}

TEST_F(ScanfTest, Oversscanf_InvalidFormat) {
    int result = 0;
    int count = oversscanf("abc", "%d", &result);
    std::cout << "Test Oversscanf_InvalidFormat: input=\"abc\", format=\"%d\", got count=" << count << ", expected count=0\n";
    EXPECT_EQ(count, 0) << "oversscanf(\"abc\", \"%d\") count";
}


TEST_F(ScanfTest, Overfscanf_RomanNumeral_Simple) {
    writeToFile("IX");
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    std::cout << "Test Overfscanf_RomanNumeral_Simple: file_content=\"IX\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=9, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"IX\", \"%Ro\") count";
    EXPECT_EQ(result, 9) << "overfscanf(file=\"IX\", \"%Ro\") result";
}

TEST_F(ScanfTest, Overfscanf_RomanNumeral_Complex) {
    writeToFile("MCMXCIV");
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    std::cout << "Test Overfscanf_RomanNumeral_Complex: file_content=\"MCMXCIV\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=1994, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"MCMXCIV\", \"%Ro\") count";
    EXPECT_EQ(result, 1994) << "overfscanf(file=\"MCMXCIV\", \"%Ro\") result";
}

TEST_F(ScanfTest, Overfscanf_Zeckendorf) {
    writeToFile("11");
    unsigned int result = 0;
    int count = overfscanf(testFile, "%Zr", &result);
    std::cout << "Test Overfscanf_Zeckendorf: file_content=\"11\", format=\"%Zr\", got result=" << result << ", count=" << count << ", expected count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"11\", \"%Zr\") count";
}

TEST_F(ScanfTest, Overfscanf_CustomBase_Hex) {
    writeToFile("ff");
    int result = 0;
    int count = overfscanf(testFile, "%Cv", &result, 16);
    std::cout << "Test Overfscanf_CustomBase_Hex: file_content=\"ff\", format=\"%Cv\", base=16, got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"ff\", \"%Cv\", base=16) count";
    EXPECT_EQ(result, 255) << "overfscanf(file=\"ff\", \"%Cv\", base=16) result";
}

TEST_F(ScanfTest, Overfscanf_CustomBaseUpper_Hex) {
    writeToFile("FF");
    int result = 0;
    int count = overfscanf(testFile, "%CV", &result, 16);
    std::cout << "Test Overfscanf_CustomBaseUpper_Hex: file_content=\"FF\", format=\"%CV\", base=16, got result=" << result << ", count=" << count << ", expected result=255, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"FF\", \"%CV\", base=16) count";
    EXPECT_EQ(result, 255) << "overfscanf(file=\"FF\", \"%CV\", base=16) result";
}

TEST_F(ScanfTest, Overfscanf_StandardInt) {
    writeToFile("42");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    std::cout << "Test Overfscanf_StandardInt: file_content=\"42\", format=\"%d\", got result=" << result << ", count=" << count << ", expected result=42, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"42\", \"%d\") count";
    EXPECT_EQ(result, 42) << "overfscanf(file=\"42\", \"%d\") result";
}

TEST_F(ScanfTest, Overfscanf_StandardUnsigned) {
    writeToFile("4294967295");
    unsigned int result = 0;
    int count = overfscanf(testFile, "%u", &result);
    std::cout << "Test Overfscanf_StandardUnsigned: file_content=\"4294967295\", format=\"%u\", got result=" << result << ", count=" << count << ", expected result=" << UINT_MAX << ", count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"4294967295\", \"%u\") count";
    EXPECT_EQ(result, UINT_MAX) << "overfscanf(file=\"4294967295\", \"%u\") result";
}

TEST_F(ScanfTest, Overfscanf_StandardString) {
    writeToFile("world");
    char result[50] = {0};
    int count = overfscanf(testFile, "%s", result);
    std::cout << "Test Overfscanf_StandardString: file_content=\"world\", format=\"%s\", got result=\"" << result << "\", count=" << count << ", expected result=\"world\", count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"world\", \"%s\") count";
    EXPECT_STREQ(result, "world") << "overfscanf(file=\"world\", \"%s\") result";
}

TEST_F(ScanfTest, Overfscanf_StandardChar) {
    writeToFile("Z");
    char result = 0;
    int count = overfscanf(testFile, "%c", &result);
    std::cout << "Test Overfscanf_StandardChar: file_content=\"Z\", format=\"%c\", got result='" << result << "', count=" << count << ", expected result='Z', count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"Z\", \"%c\") count";
    EXPECT_EQ(result, 'Z') << "overfscanf(file=\"Z\", \"%c\") result";
}

TEST_F(ScanfTest, Overfscanf_Multiple) {
    writeToFile("100 200 300");
    int a = 0, b = 0, c = 0;
    int count = overfscanf(testFile, "%d %d %d", &a, &b, &c);
    std::cout << "Test Overfscanf_Multiple: file_content=\"100 200 300\", format=\"%d %d %d\", got a=" << a << ", b=" << b << ", c=" << c << ", count=" << count << ", expected a=100, b=200, c=300, count=3\n";
    EXPECT_EQ(count, 3) << "overfscanf(file=\"100 200 300\", \"%d %d %d\") count";
    EXPECT_EQ(a, 100) << "overfscanf(file=\"100 200 300\", \"%d %d %d\") a";
    EXPECT_EQ(b, 200) << "overfscanf(file=\"100 200 300\", \"%d %d %d\") b";
    EXPECT_EQ(c, 300) << "overfscanf(file=\"100 200 300\", \"%d %d %d\") c";
}

TEST_F(ScanfTest, Overfscanf_MixedFormats) {
    writeToFile("L 50");
    int roman = 0, decimal = 0;
    int count = overfscanf(testFile, "%Ro %d", &roman, &decimal);
    std::cout << "Test Overfscanf_MixedFormats: file_content=\"L 50\", format=\"%Ro %d\", got roman=" << roman << ", decimal=" << decimal << ", count=" << count << ", expected roman=50, decimal=50, count=2\n";
    EXPECT_EQ(count, 2) << "overfscanf(file=\"L 50\", \"%Ro %d\") count";
    EXPECT_EQ(roman, 50) << "overfscanf(file=\"L 50\", \"%Ro %d\") roman";
    EXPECT_EQ(decimal, 50) << "overfscanf(file=\"L 50\", \"%Ro %d\") decimal";
}

TEST_F(ScanfTest, Overfscanf_Whitespace) {
    writeToFile("  42  ");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    std::cout << "Test Overfscanf_Whitespace: file_content=\"  42  \", format=\"%d\", got result=" << result << ", count=" << count << ", expected result=42, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=\"  42  \", \"%d\") count";
    EXPECT_EQ(result, 42) << "overfscanf(file=\"  42  \", \"%d\") result";
}

TEST_F(ScanfTest, Overfscanf_Newlines) {
    writeToFile("10\n20\n30");
    int a = 0, b = 0, c = 0;
    int count = overfscanf(testFile, "%d %d %d", &a, &b, &c);
    std::cout << "Test Overfscanf_Newlines: file_content=\"10\\n20\\n30\", format=\"%d %d %d\", got a=" << a << ", b=" << b << ", c=" << c << ", count=" << count << ", expected a=10, b=20, c=30, count=3\n";
    EXPECT_EQ(count, 3) << "overfscanf(file=\"10\\n20\\n30\", \"%d %d %d\") count";
    EXPECT_EQ(a, 10) << "overfscanf(file=\"10\\n20\\n30\", \"%d %d %d\") a";
    EXPECT_EQ(b, 20) << "overfscanf(file=\"10\\n20\\n30\", \"%d %d %d\") b";
    EXPECT_EQ(c, 30) << "overfscanf(file=\"10\\n20\\n30\", \"%d %d %d\") c";
}

TEST_F(ScanfTest, Overfscanf_LargeString) {
    std::string largeRoman(1000, 'M');
    writeToFile(largeRoman.c_str());
    int result = 0;
    int count = overfscanf(testFile, "%Ro", &result);
    std::cout << "Test Overfscanf_LargeString: file_content=\"MMM...(1000 M's)\", format=\"%Ro\", got result=" << result << ", count=" << count << ", expected result=1000000, count=1\n";
    EXPECT_EQ(count, 1) << "overfscanf(file=1000xM, \"%Ro\") count";
    EXPECT_EQ(result, 1000000) << "overfscanf(file=1000xM, \"%Ro\") result";
}

TEST_F(ScanfTest, Overfscanf_EmptyFile) {
    writeToFile("");
    int result = 0;
    int count = overfscanf(testFile, "%d", &result);
    std::cout << "Test Overfscanf_EmptyFile: file_content=\"\", format=\"%d\", got count=" << count << ", expected count=0\n";
    EXPECT_EQ(count, 0) << "overfscanf(file=\"\", \"%d\") count";
}

TEST_F(ScanfTest, Overfscanf_PositionTracking) {
    writeToFile("42");
    int num = 0, pos = 0;
    int count = overfscanf(testFile, "%d%n", &num, &pos);
    std::cout << "Test Overfscanf_PositionTracking: file_content=\"42\", format=\"%d%n\", got num=" << num << ", pos=" << pos << ", count=" << count << ", expected num=42, pos>0\n";
    EXPECT_EQ(num, 42) << "overfscanf(file=\"42\", \"%d%n\") num";
    EXPECT_GT(pos, 0) << "overfscanf(file=\"42\", \"%d%n\") pos";
}


TEST(FibonachTest, GeneratesSequence) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    std::cout << "Test FibonachTest_GeneratesSequence: fibonach(&len), got len=" << len << ", fib[0]=" << fib[0] << ", fib[1]=" << fib[1] << ", fib[2]=" << fib[2] << ", expected len>2, fib[0]=1, fib[1]=1, fib[2]=2\n";
    ASSERT_NE(fib, nullptr) << "fibonach returned nullptr";
    EXPECT_GT(len, 2) << "fibonach length";
    EXPECT_EQ(fib[0], 1u) << "fibonach fib[0]";
    EXPECT_EQ(fib[1], 1u) << "fibonach fib[1]";
    EXPECT_EQ(fib[2], 2u) << "fibonach fib[2]";
    free(fib);
}

TEST(FibonachTest, NoOverflow) {
    int len = 0;
    unsigned int* fib = fibonach(&len);
    std::cout << "Test FibonachTest_NoOverflow: fibonach(&len), got len=" << len << ", checking fib[i]=fib[i-1]+fib[i-2] for all i\n";
    ASSERT_NE(fib, nullptr) << "fibonach returned nullptr";
    for (int i = 2; i < len; i++) {
        EXPECT_EQ(fib[i], fib[i-1] + fib[i-2]) << "fibonach[" << i << "]=" << fib[i] << " should equal fib[" << (i-1) << "]+fib[" << (i-2) << "]=" << (fib[i-1] + fib[i-2]);
    }
    free(fib);
}

TEST(FuncCTest, Binary) {
    int result = func_c((char*)"1111", 2);
    std::cout << "Test FuncCTest_Binary: func_c(\"1111\", 2), got result=" << result << ", expected result=15\n";
    EXPECT_EQ(result, 15) << "func_c(\"1111\", 2)";
}

TEST(FuncCTest, Hexadecimal) {
    int result = func_c((char*)"ff", 16);
    std::cout << "Test FuncCTest_Hexadecimal: func_c(\"ff\", 16), got result=" << result << ", expected result=255\n";
    EXPECT_EQ(result, 255) << "func_c(\"ff\", 16)";
}

TEST(FuncCTest, InvalidBase) {
    int result = func_c((char*)"123", 50);
    std::cout << "Test FuncCTest_InvalidBase: func_c(\"123\", 50), got result=" << result << ", expected result=123\n";
    EXPECT_EQ(result, 123) << "func_c(\"123\", 50)";
}

TEST(FuncDTest, UppercaseHex) {
    int result = func_d((char*)"FF", 16);
    std::cout << "Test FuncDTest_UppercaseHex: func_d(\"FF\", 16), got result=" << result << ", expected result=255\n";
    EXPECT_EQ(result, 255) << "func_d(\"FF\", 16)";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
