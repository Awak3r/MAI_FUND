#include <gtest/gtest.h>
extern "C" {
#include "../include/func.h"
}

TEST(FiniteDecimal, Base10) {
    EXPECT_EQ(test(0.5, 10), 1);
    EXPECT_EQ(test(0.25, 10), 1);
    EXPECT_EQ(test(0.125, 10), 1);
    EXPECT_EQ(test(0.2, 10), 1);
    EXPECT_EQ(test(0.333333, 10), 1);
}

TEST(FiniteDecimal, Base2) {
    EXPECT_EQ(test(0.5, 2), 1);
    EXPECT_EQ(test(0.25, 2), 1);
    EXPECT_EQ(test(0.2, 2), 0);
    EXPECT_EQ(test(0.333, 2), 0);
}

TEST(FiniteDecimal, Base6) {
    EXPECT_EQ(test(0.5, 6), 1);
    EXPECT_EQ(test(0.25, 6), 1);
    EXPECT_EQ(test(0.333333, 6), 0);
    EXPECT_EQ(test(0.2, 6), 0);
}

TEST(FiniteDecimal, Negative) {
    EXPECT_EQ(test(-0.5, 10), 1);
    EXPECT_EQ(test(-0.2, 10), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
