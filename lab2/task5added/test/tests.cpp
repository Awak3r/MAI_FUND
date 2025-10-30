#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iostream>

extern "C" {
#include "../include/func.h"
}

class StringProcessingTest : public ::testing::Test {
protected:
    char buffer[1024];
    
    void SetUp() override {
        memset(buffer, 0, sizeof(buffer));
    }
    
    void TearDown() override {
    }
};

TEST_F(StringProcessingTest, NormString_RemovesMultipleSpaces) {
    strcpy(buffer, "Hello    world    test");
    std::cout << "Test NormString_RemovesMultipleSpaces: input=\"Hello    world    test\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello world test\"\n";
    EXPECT_STREQ(buffer, "Hello world test") << "norm_string with multiple spaces";
}

TEST_F(StringProcessingTest, NormString_RemovesTabs) {
    strcpy(buffer, "Hello\t\tworld\ttest");
    std::cout << "Test NormString_RemovesTabs: input=\"Hello\\t\\tworld\\ttest\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello world test\"\n";
    EXPECT_STREQ(buffer, "Hello world test") << "norm_string with tabs";
}

TEST_F(StringProcessingTest, NormString_RemovesMixedWhitespace) {
    strcpy(buffer, "Hello \t  \t world   \t test");
    std::cout << "Test NormString_RemovesMixedWhitespace: input=\"Hello \\t  \\t world   \\t test\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello world test\"\n";
    EXPECT_STREQ(buffer, "Hello world test") << "norm_string with mixed whitespace";
}

TEST_F(StringProcessingTest, NormString_RemovesTrailingSpace) {
    strcpy(buffer, "Hello world  ");
    std::cout << "Test NormString_RemovesTrailingSpace: input=\"Hello world  \", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello world\"\n";
    EXPECT_STREQ(buffer, "Hello world") << "norm_string with trailing space";
}

TEST_F(StringProcessingTest, NormString_RemovesLeadingSpace) {
    strcpy(buffer, "  Hello world");
    std::cout << "Test NormString_RemovesLeadingSpace: input=\"  Hello world\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello world\"\n";
    EXPECT_STREQ(buffer, "Hello world") << "norm_string with leading space";
}

TEST_F(StringProcessingTest, NormString_HandlesEmptyString) {
    strcpy(buffer, "");
    std::cout << "Test NormString_HandlesEmptyString: input=\"\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"\"\n";
    EXPECT_STREQ(buffer, "") << "norm_string with empty string";
}

TEST_F(StringProcessingTest, NormString_HandlesSingleWord) {
    strcpy(buffer, "Hello");
    std::cout << "Test NormString_HandlesSingleWord: input=\"Hello\", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"Hello\"\n";
    EXPECT_STREQ(buffer, "Hello") << "norm_string with single word";
}

TEST_F(StringProcessingTest, NormString_HandlesOnlySpaces) {
    strcpy(buffer, "     ");
    std::cout << "Test NormString_HandlesOnlySpaces: input=\"     \", ";
    norm_string(buffer);
    std::cout << "got=\"" << buffer << "\", expected=\"\"\n";
    EXPECT_STREQ(buffer, "") << "norm_string with only spaces";
}

TEST_F(StringProcessingTest, Obrez_ShortString) {
    char* input = (char*)malloc(1024);
    strcpy(input, "Short string");
    std::cout << "Test Obrez_ShortString: input=\"Short string\", ";
    char* result = obrez(input);
    std::cout << "got result=\"" << result << "\", input=\"" << input << "\", expected result=\"Short string\", input length=0\n";
    EXPECT_STREQ(result, "Short string") << "obrez short string result";
    EXPECT_EQ(strlen(input), 0u) << "obrez short string input length";
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_ExactlyEightyChars) {
    char* input = (char*)malloc(1024);
    strcpy(input, "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    std::cout << "Test Obrez_ExactlyEightyChars: input length=" << strlen(input) << ", ";
    char* result = obrez(input);
    std::cout << "got result length=" << strlen(result) << ", expected=80\n";
    EXPECT_EQ(strlen(result), 80u) << "obrez exactly 80 chars";
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_LongStringWithSpaceAt80) {
    char* input = (char*)malloc(1024);
    strcpy(input, "1234567890123456789012345678901234567890123456789012345678901234567890123456789 extra words");
    std::cout << "Test Obrez_LongStringWithSpaceAt80: input has space at position 79, ";
    char* result = obrez(input);
    std::cout << "got result length=" << strlen(result) << ", input=\"" << input << "\", expected result length=79, input=\"extra words\"\n";
    EXPECT_EQ(strlen(result), 79u) << "obrez with space at 80";
    EXPECT_STREQ(input, "extra words") << "obrez remaining input";
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_BreaksAtWordBoundary) {
    char* input = (char*)malloc(1024);
    strcpy(input, "This is a very long string that exceeds eighty characters and should be broken at word boundary");
    std::cout << "Test Obrez_BreaksAtWordBoundary: input length=" << strlen(input) << ", ";
    char* result = obrez(input);
    std::cout << "got result length=" << strlen(result) << ", last char='" << result[strlen(result)-1] << "', expected length<81, last char!=' '\n";
    EXPECT_LT(strlen(result), 81u) << "obrez breaks at word boundary length";
    EXPECT_NE(result[strlen(result) - 1], ' ') << "obrez no trailing space";
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Sdvig_InsertsSpace) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    std::cout << "Test Sdvig_InsertsSpace: input=\"Hello\", position=2, ";
    char* result = sdvig(str, 2);
    std::cout << "got=\"" << result << "\", length=" << strlen(result) << ", expected=\"Hel lo\", length=6\n";
    EXPECT_STREQ(result, "Hel lo") << "sdvig inserts space at position 2";
    EXPECT_EQ(strlen(result), 6u) << "sdvig result length";
    free(result);
}

TEST_F(StringProcessingTest, Sdvig_AtBeginning) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    std::cout << "Test Sdvig_AtBeginning: input=\"Hello\", position=0, ";
    char* result = sdvig(str, 0);
    std::cout << "got=\"" << result << "\", expected=\"H ello\"\n";
    EXPECT_STREQ(result, "H ello") << "sdvig at beginning";
    free(result);
}

TEST_F(StringProcessingTest, Sdvig_AtEnd) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    std::cout << "Test Sdvig_AtEnd: input=\"Hello\", position=4, ";
    char* result = sdvig(str, 4);
    std::cout << "got=\"" << result << "\", expected=\"Hello \"\n";
    EXPECT_STREQ(result, "Hello ") << "sdvig at end";
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_AddsSpacesToReach80) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello world test");
    std::cout << "Test AddProbel_AddsSpacesToReach80: input=\"Hello world test\", input length=16, ";
    char* result = add_probel(str);
    std::cout << "got length=" << strlen(result) << ", expected=80\n";
    EXPECT_EQ(strlen(result), 80u) << "add_probel reaches 80 chars";
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_ShortStringWithSpaces) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hi there");
    std::cout << "Test AddProbel_ShortStringWithSpaces: input=\"Hi there\", input length=8, ";
    char* result = add_probel(str);
    std::cout << "got length=" << strlen(result) << ", expected=80\n";
    EXPECT_EQ(strlen(result), 80u) << "add_probel short string";
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_AlreadyEightyChars) {
    char* str = (char*)malloc(1024);
    strcpy(str, "1234567890123456789012345678901234567890123456789012345678901234567890123456789");
    std::cout << "Test AddProbel_AlreadyEightyChars: input length=79, ";
    char* result = add_probel(str);
    std::cout << "got length=" << strlen(result) << ", expected=80\n";
    EXPECT_EQ(strlen(result), 80u) << "add_probel already 80 chars";
    free(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
