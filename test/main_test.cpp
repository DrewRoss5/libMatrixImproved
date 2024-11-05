#include <gtest/gtest.h>
#include <chrono>
#include <functional>
#include "matrix.h"


// runs a function and displays the time it took
int benchmark(std::function<void()> func){
    auto t1 = std::chrono::high_resolution_clock::now();
    func();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>((t2 - t1));
    std::cout << "Benchmark completed in " << duration.count() << " milliseconds." << std::endl;
    return 0;
}

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

TEST(MatrixTests, MultiplicationTests){
    Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix m2(3, 2, {2, 4, 6, 8, 10, 12});
    Matrix expected(2, 2, {44, 56, 98, 128});
    EXPECT_EQ((m1 * m2), expected);
}

// this assumes that multiplaction works (see the above test) and functions more as a simple comparative benchmark
TEST(MatrixTests, MultiplicationTestLarge){
    std::cout << "Generating matrices..." << std::endl;
    Matrix m1 = Matrix::random_matrix(1000, 1000);
    Matrix m2 = Matrix::random_matrix(1000, 1000);
    std::cout << "Benchmarking singlethreaded multiplication:" << std::endl;
    int bench = benchmark([&m1, &m2] () {m1.multiply_singlethread(m2);});
    std::cout << "Benchmarking multithreaded multiplication" << std::endl;
    bench = benchmark([&m1, &m2] () {m1.multiply(m2);});
}

// test that identity matrices work properly (that is, a matrix multilplied by an identity matrix results in itseld)
TEST(MatrixTests, IdentityMatrices){
    Matrix m1 = Matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix identity = Matrix::identity_matrix(3);
    Matrix m2 = m1 * identity;
    EXPECT_TRUE(m1 == m2);
}

// test the getter operators
TEST(MatrixTests, GetterOperators){
    Matrix mat = Matrix::identity_matrix(3);
    mat(1, 1) = 5;   
    EXPECT_EQ(mat[1][1], 5);
    mat[0][1] = 10;
    EXPECT_EQ(mat(0, 1), 10);
}

// test the copy constructor
TEST(MatrixTests, CopyConstructors){
    Matrix m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix m2(m1);
    Matrix m3 = m2;
    EXPECT_EQ(m1, m2);
    EXPECT_EQ(m2, m3);
}

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}