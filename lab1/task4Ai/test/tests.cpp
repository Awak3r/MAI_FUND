#include <gtest/gtest.h>
#include <math.h>

extern "C" {
#include "../include/func.h"
}

class ConstantCalculationTest : public ::testing::Test {
protected:
    double epsilon;
    
    void SetUp() override {
        epsilon = 0.0001;
    }
};

TEST_F(ConstantCalculationTest, E_MethodA) {
    double result = calculate_e_a(epsilon);
    EXPECT_NEAR(result, M_E, 0.01);
}

TEST_F(ConstantCalculationTest, E_MethodB) {
    double result = calculate_e_b(epsilon);
    EXPECT_NEAR(result, M_E, 0.001);
}

TEST_F(ConstantCalculationTest, E_MethodC) {
    double result = calculate_e_c(epsilon);
    EXPECT_NEAR(result, M_E, 0.001);
}

TEST_F(ConstantCalculationTest, Pi_MethodA) {
    double result = calculate_pi_a(epsilon);
    EXPECT_NEAR(result, M_PI, 0.1);
}

TEST_F(ConstantCalculationTest, Pi_MethodB) {
    double result = calculate_pi_b(epsilon);
    EXPECT_NEAR(result, M_PI, 0.01);
}

TEST_F(ConstantCalculationTest, Pi_MethodC) {
    double result = calculate_pi_c(epsilon);
    EXPECT_NEAR(result, M_PI, 0.0001);
}

TEST_F(ConstantCalculationTest, Ln2_MethodA) {
    double result = calculate_ln2_a(epsilon);
    EXPECT_NEAR(result, M_LN2, 0.1);
}

TEST_F(ConstantCalculationTest, Ln2_MethodB) {
    double result = calculate_ln2_b(epsilon);
    EXPECT_NEAR(result, M_LN2, 0.001);
}

TEST_F(ConstantCalculationTest, Ln2_MethodC) {
    double result = calculate_ln2_c(epsilon);
    EXPECT_NEAR(result, M_LN2, 0.0001);
}


TEST_F(ConstantCalculationTest, Sqrt2_MethodA) {
    double result = calculate_sqrt2_a(epsilon);
    EXPECT_NEAR(result, M_SQRT2, 0.001);
}

TEST_F(ConstantCalculationTest, Sqrt2_MethodB) {
    double result = calculate_sqrt2_b(epsilon);
    EXPECT_NEAR(result, M_SQRT2, 0.001);
}

TEST_F(ConstantCalculationTest, Sqrt2_MethodC) {
    double result = calculate_sqrt2_c(epsilon);
    EXPECT_NEAR(result, M_SQRT2, 0.0001);
}

TEST_F(ConstantCalculationTest, Gamma_MethodA) {
    double result = calculate_gamma_a(epsilon);
    EXPECT_NEAR(result, 0.5772156649, 0.1);
}

TEST_F(ConstantCalculationTest, Gamma_MethodB) {
    double result = calculate_gamma_b(epsilon);
    EXPECT_NEAR(result, 0.5772156649, 0.01);
}

TEST_F(ConstantCalculationTest, Gamma_MethodC) {
    double result = calculate_gamma_c(epsilon);
    EXPECT_NEAR(result, 0.5772156649, 0.0001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}