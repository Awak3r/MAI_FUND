#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <fstream>

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
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello world test");
}

TEST_F(StringProcessingTest, NormString_RemovesTabs) {
    strcpy(buffer, "Hello\t\tworld\ttest");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello world test");
}

TEST_F(StringProcessingTest, NormString_RemovesMixedWhitespace) {
    strcpy(buffer, "Hello \t  \t world   \t test");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello world test");
}

TEST_F(StringProcessingTest, NormString_RemovesTrailingSpace) {
    strcpy(buffer, "Hello world  ");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello world");
}

TEST_F(StringProcessingTest, NormString_RemovesLeadingSpace) {
    strcpy(buffer, "  Hello world");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello world");
}

TEST_F(StringProcessingTest, NormString_HandlesEmptyString) {
    strcpy(buffer, "");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "");
}

TEST_F(StringProcessingTest, NormString_HandlesSingleWord) {
    strcpy(buffer, "Hello");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "Hello");
}

TEST_F(StringProcessingTest, NormString_HandlesOnlySpaces) {
    strcpy(buffer, "     ");
    norm_string(buffer);
    EXPECT_STREQ(buffer, "");
}

TEST_F(StringProcessingTest, Obrez_ShortString) {
    char* input = (char*)malloc(1024);
    strcpy(input, "Short string");
    char* result = obrez(input);
    EXPECT_STREQ(result, "Short string");
    EXPECT_EQ(strlen(input), 0);
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_ExactlyEightyChars) {
    char* input = (char*)malloc(1024);
    strcpy(input, "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    char* result = obrez(input);
    EXPECT_EQ(strlen(result), 80);
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_LongStringWithSpaceAt80) {
    char* input = (char*)malloc(1024);
    strcpy(input, "1234567890123456789012345678901234567890123456789012345678901234567890123456789 extra words");
    char* result = obrez(input);
    EXPECT_EQ(strlen(result), 79);
    EXPECT_STREQ(input, "extra words");
    free(input);
    free(result);
}

TEST_F(StringProcessingTest, Obrez_BreaksAtWordBoundary) {
    char* input = (char*)malloc(1024);
    strcpy(input, "This is a very long string that exceeds eighty characters and should be broken at word boundary");
    char* result = obrez(input);
    EXPECT_LT(strlen(result), 81);
    EXPECT_NE(result[strlen(result) - 1], ' ');
    free(input);
    free(result);
}


TEST_F(StringProcessingTest, Sdvig_InsertsSpace) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    char* result = sdvig(str, 2);
    EXPECT_STREQ(result, "Hel lo");
    EXPECT_EQ(strlen(result), 6);
    free(result);
}

TEST_F(StringProcessingTest, Sdvig_AtBeginning) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    char* result = sdvig(str, 0);
    EXPECT_STREQ(result, "H ello");
    free(result);
}

TEST_F(StringProcessingTest, Sdvig_AtEnd) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello");
    char* result = sdvig(str, 4);
    EXPECT_STREQ(result, "Hello ");
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_AddsSpacesToReach80) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hello world test");
    char* result = add_probel(str);
    EXPECT_EQ(strlen(result), 80);
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_ShortStringWithSpaces) {
    char* str = (char*)malloc(1024);
    strcpy(str, "Hi there");
    char* result = add_probel(str);
    EXPECT_EQ(strlen(result), 80);
    free(result);
}

TEST_F(StringProcessingTest, AddProbel_AlreadyEightyChars) {
    char* str = (char*)malloc(1024);
    strcpy(str, "1234567890123456789012345678901234567890123456789012345678901234567890123456789");
    char* result = add_probel(str);
    EXPECT_EQ(strlen(result), 80);
    free(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
