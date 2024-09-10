#include <gtest/gtest.h>
#include "matrix.h"

TEST(MatrixTests, ArithmeticOpeations){
    Matrix m1(2, 2, {1, 2, 3, 4});
    Matrix m2(2, 2, {2, 4, 6, 8});
    // test equality operator
    EXPECT_FALSE(m1 == m2);
    // test the basic arithmetic functions
    EXPECT_EQ(m1 + 2, Matrix(2, 2, {3, 4, 5, 6}));
    EXPECT_EQ(m2 - 2, Matrix(2, 2, {0, 2, 4, 6}));
    EXPECT_EQ(m1 + m2, Matrix(2, 2, {3, 6, 9, 12}));
    EXPECT_EQ(m2 - m1, Matrix(2, 2, {1, 2, 3, 4}));
    EXPECT_EQ(m1 * 2, m2);
    // test matrix multiplication
    Matrix m3 = m1 * m2;
    EXPECT_EQ(m3, Matrix(2, 2, {14, 20, 30, 44}));
}


int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}