#include <gtest/gtest.h>
#include <iostream>
extern "C" {
#include "../include/func.h"
}

class BracketsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Тесты корректных строк ====================

TEST_F(BracketsTest, ValidBrackets_AllTypes) {
    const char* input = "()[]{}";
    std::cout << "Test ValidBrackets_AllTypes: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "All bracket types should be valid";
}

TEST_F(BracketsTest, ValidBrackets_Nested) {
    const char* input = "([{}])";
    std::cout << "Test ValidBrackets_Nested: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Nested brackets should be valid";
}

TEST_F(BracketsTest, ValidBrackets_DeepNesting) {
    const char* input = "((([[[{{{{}}}}]]])))";
    std::cout << "Test ValidBrackets_DeepNesting: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Deep nesting should be valid";
}

TEST_F(BracketsTest, ValidBrackets_Sequential) {
    const char* input = "()()[][]{}{}";
    std::cout << "Test ValidBrackets_Sequential: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Sequential brackets should be valid";
}

TEST_F(BracketsTest, ValidBrackets_WithText) {
    const char* input = "abc(def[ghi{jkl}mno]pqr)stu";
    std::cout << "Test ValidBrackets_WithText: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Brackets with text should be valid";
}

TEST_F(BracketsTest, ValidBrackets_WithSpaces) {
    const char* input = "( [ { } ] )";
    std::cout << "Test ValidBrackets_WithSpaces: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Brackets with spaces should be valid";
}

TEST_F(BracketsTest, ValidBrackets_AngleBrackets) {
    const char* input = "<><>";
    std::cout << "Test ValidBrackets_AngleBrackets: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Angle brackets should be valid";
}

TEST_F(BracketsTest, ValidBrackets_ComplexNesting) {
    const char* input = "{[()]}({[]})";
    std::cout << "Test ValidBrackets_ComplexNesting: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Complex nesting should be valid";
}

TEST_F(BracketsTest, ValidBrackets_EmptyString) {
    const char* input = "";
    std::cout << "Test ValidBrackets_EmptyString: input=\"\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Empty string should be valid";
}

TEST_F(BracketsTest, ValidBrackets_NoNrackets) {
    const char* input = "abcdefg123456";
    std::cout << "Test ValidBrackets_NoBrackets: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "String without brackets should be valid";
}

// ==================== Тесты некорректных строк ====================

TEST_F(BracketsTest, InvalidBrackets_WrongOrder) {
    const char* input = ")(";
    std::cout << "Test InvalidBrackets_WrongOrder: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Wrong order should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_CrossedNesting) {
    const char* input = "([)]";
    std::cout << "Test InvalidBrackets_CrossedNesting: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Crossed nesting should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_MismatchedTypes) {
    const char* input = "(]";
    std::cout << "Test InvalidBrackets_MismatchedTypes: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Mismatched bracket types should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_Unclosed) {
    const char* input = "(((";
    std::cout << "Test InvalidBrackets_Unclosed: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Unclosed brackets should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_ExtraClosing) {
    const char* input = "())";
    std::cout << "Test InvalidBrackets_ExtraClosing: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Extra closing bracket should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_OnlyClosing) {
    const char* input = ")";
    std::cout << "Test InvalidBrackets_OnlyClosing: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Only closing bracket should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_OnlyOpening) {
    const char* input = "(";
    std::cout << "Test InvalidBrackets_OnlyOpening: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Only opening bracket should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_MismatchCurly) {
    const char* input = "{)";
    std::cout << "Test InvalidBrackets_MismatchCurly: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Curly-round mismatch should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_MismatchSquare) {
    const char* input = "[}";
    std::cout << "Test InvalidBrackets_MismatchSquare: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Square-curly mismatch should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_MismatchAngle) {
    const char* input = "<]";
    std::cout << "Test InvalidBrackets_MismatchAngle: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Angle-square mismatch should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_ComplexMismatch) {
    const char* input = "({)}";
    std::cout << "Test InvalidBrackets_ComplexMismatch: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Complex mismatch should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_MultipleErrors) {
    const char* input = "((([[[{{{";
    std::cout << "Test InvalidBrackets_MultipleErrors: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Multiple unclosed brackets should be invalid";
}

TEST_F(BracketsTest, InvalidBrackets_WithText) {
    const char* input = "abc(def]ghi";
    std::cout << "Test InvalidBrackets_WithText: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=0\n";
    EXPECT_EQ(result, 0) << "Mismatched brackets with text should be invalid";
}

// ==================== Специальные тесты ====================

TEST_F(BracketsTest, SpecialCase_SinglePair) {
    const char* input = "()";
    std::cout << "Test SpecialCase_SinglePair: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Single pair should be valid";
}

TEST_F(BracketsTest, SpecialCase_NestedPairs) {
    const char* input = "((()))";
    std::cout << "Test SpecialCase_NestedPairs: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Nested pairs should be valid";
}

TEST_F(BracketsTest, SpecialCase_MathExpression) {
    const char* input = "((a+b)*[c-d])";
    std::cout << "Test SpecialCase_MathExpression: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Math expression should be valid";
}

TEST_F(BracketsTest, SpecialCase_LongValid) {
    const char* input = "(((((((((()))))))))){[()]}";
    std::cout << "Test SpecialCase_LongValid: input=\"" << input << "\", ";
    int result = check_brackets(input);
    std::cout << "got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Long valid string should be valid";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
