#include <gtest/gtest.h>
extern "C" {
#include "../include/func.h"
}

struct FractionTestCase {
    double value;
    int base;
    int expected;
    const char *label;
};

TEST(FiniteDecimal, DetailedBase10) {
    FractionTestCase testCases[] = {
        {0.5,  10, 1, "0.5 in base 10"},
        {0.25, 10, 1, "0.25 in base 10"},
        {0.125,10, 1, "0.125 in base 10"},
        {0.2,  10, 1, "0.2 in base 10"},
        {0.333333,10, 1, "0.333333 in base 10"},
    };
    for (int i = 0; i < 5; ++i) {
        int result = test(testCases[i].value, testCases[i].base);
        std::cout << "Test Base10 #" << (i+1) << ": " << testCases[i].label
                  << " | got=" << result << " | expected=" << testCases[i].expected << "\n";
        EXPECT_EQ(result, testCases[i].expected)
            << " (" << testCases[i].label << ", Test #" << (i+1) << ")";
    }
}

TEST(FiniteDecimal, DetailedBase2) {
    FractionTestCase testCases[] = {
        {0.5,   2, 1, "0.5 in base 2"},
        {0.25,  2, 1, "0.25 in base 2"},
        {0.2,   2, 0, "0.2 in base 2"},
        {0.333, 2, 0, "0.333 in base 2"},
    };
    for (int i = 0; i < 4; ++i) {
        int result = test(testCases[i].value, testCases[i].base);
        std::cout << "Test Base2 #" << (i+1) << ": " << testCases[i].label
                  << " | got=" << result << " | expected=" << testCases[i].expected << "\n";
        EXPECT_EQ(result, testCases[i].expected)
            << " (" << testCases[i].label << ", Test #" << (i+1) << ")";
    }
}

TEST(FiniteDecimal, DetailedBase6) {
    FractionTestCase testCases[] = {
        {1.0/255,      255, 0, "0.5 in base 6"},
        {0.3333333333333333333333333333333333333333,     6, 0, "0.25 in base 6"},
        {0.333333, 6, 0, "0.333333 in base 6"},
        {0.2,      6, 0, "0.2 in base 6"},
    };
    for (int i = 0; i < 4; ++i) {
        int result = test(testCases[i].value, testCases[i].base);
        std::cout << "Test Base6 #" << (i+1) << ": " << testCases[i].label
                  << " | got=" << result << " | expected=" << testCases[i].expected << "\n";
        EXPECT_EQ(result, testCases[i].expected)
            << " (" << testCases[i].label << ", Test #" << (i+1) << ")";
    }
}

TEST(FiniteDecimal, DetailedNegative) {
    FractionTestCase testCases[] = {
        {-0.5, 10, 1, "-0.5 in base 10"},
        {-0.2, 10, 1, "-0.2 in base 10"},
    };
    for (int i = 0; i < 2; ++i) {
        int result = test(testCases[i].value, testCases[i].base);
        std::cout << "Test Negative #" << (i+1) << ": " << testCases[i].label
                  << " | got=" << result << " | expected=" << testCases[i].expected << "\n";
        EXPECT_EQ(result, testCases[i].expected)
            << " (" << testCases[i].label << ", Test #" << (i+1) << ")";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
