#include <gtest/gtest.h>

extern "C" {
    #include "../include/func.h"
}

class Task2Test : public ::testing::Test {
protected:
    int* primes;
    int count;
    
    void SetUp() override {
        primes = simple_numbers(&count);
        ASSERT_NE(primes, nullptr);
        ASSERT_GT(count, 0);
    }
    
    void TearDown() override {
        free(primes);
    }
};

TEST_F(Task2Test, FirstPrime) {
    EXPECT_EQ(task2(primes, 1), 2);
}

TEST_F(Task2Test, SecondPrime) {
    EXPECT_EQ(task2(primes, 2), 3);
}

TEST_F(Task2Test, ThirdPrime) {
    EXPECT_EQ(task2(primes, 3), 5);
}

TEST_F(Task2Test, FourthPrime) {
    EXPECT_EQ(task2(primes, 4), 7);
}

TEST_F(Task2Test, FifthPrime) {
    EXPECT_EQ(task2(primes, 5), 11);
}

TEST_F(Task2Test, TenthPrime) {
    EXPECT_EQ(task2(primes, 10), 29);
}

TEST_F(Task2Test, TwentyFifthPrime) {
    EXPECT_EQ(task2(primes, 25), 97);
}

TEST_F(Task2Test, FiftiethPrime) {
    EXPECT_EQ(task2(primes, 50), 229);
}

TEST_F(Task2Test, HundredthPrime) {
    EXPECT_EQ(task2(primes, 100), 541);
}

TEST_F(Task2Test, SequentialQueries) {
    EXPECT_EQ(task2(primes, 1), 2);
    EXPECT_EQ(task2(primes, 2), 3);
    EXPECT_EQ(task2(primes, 3), 5);
    EXPECT_EQ(task2(primes, 4), 7);
    EXPECT_EQ(task2(primes, 5), 11);
}

TEST_F(Task2Test, ReverseOrder) {
    EXPECT_EQ(task2(primes, 10), 29);
    EXPECT_EQ(task2(primes, 5), 11);
    EXPECT_EQ(task2(primes, 1), 2);
}

TEST_F(Task2Test, MediumValues) {
    EXPECT_EQ(task2(primes, 75), 379);
    EXPECT_EQ(task2(primes, 150), 863);
    EXPECT_EQ(task2(primes, 200), 1223);
}

TEST_F(Task2Test, RepeatedQueries) {
    EXPECT_EQ(task2(primes, 10), 29);
    EXPECT_EQ(task2(primes, 10), 29);
    EXPECT_EQ(task2(primes, 10), 29);
}

TEST_F(Task2Test, LargeIndices) {
    ASSERT_GE(count, 500);
    EXPECT_EQ(task2(primes, 500), 3571);
}

TEST_F(Task2Test, DifferentRanges) {
    EXPECT_EQ(task2(primes, 6), 13);
    EXPECT_EQ(task2(primes, 20), 71);
    EXPECT_EQ(task2(primes, 30), 113);
    EXPECT_EQ(task2(primes, 40), 173);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}