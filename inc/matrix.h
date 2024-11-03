#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <random>
#include <mutex>
#include <thread>


class Matrix{
    public:
        Matrix(unsigned height, unsigned width);
        Matrix(unsigned height, unsigned width, const std::vector<double>& vec);
        Matrix(const Matrix& mat);
        static Matrix identity_matrix(int size);
        static Matrix random_matrix(unsigned width, unsigned height, int min = 0, int max = 100);
        ~Matrix();
        // simple getters
        unsigned height() {return height_;}
        unsigned width() {return width_;}
        unsigned size() {return size_;}
        // basic IO functions
        void set(unsigned row, unsigned column, int value);
        double get(unsigned row, unsigned column) const;
        double& operator()(unsigned row, unsigned column); 
        double* operator[] (unsigned row);
        friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);
        // arithmetic functions and operators
        void add(int n);
        void add(const Matrix& mat);
        void operator+=(int n);
        void operator+=(const Matrix& mat);
        Matrix& operator=(const Matrix& mat);
        Matrix operator+(int n) const;
        Matrix operator+(const Matrix& mat) const;
        void subtract(int n);
        void subtract(const Matrix& mat);
        void operator-=(int n);
        void operator-=(const Matrix& mat);
        Matrix operator-(int n) const;
        Matrix operator-(const Matrix& mat) const;
        void multiply(int n);
        Matrix multiply(Matrix& mat);
        void operator*=(int n);
        Matrix operator*(Matrix& mat);
        Matrix operator*(int n) const;
        // coparison operators
        bool operator==(const Matrix& mat) const;
        bool operator!=(const Matrix& mat) const;

    private:   
        double* matrix_{nullptr};
        unsigned height_{0};
        unsigned width_{0};
        unsigned size_{0};
        Matrix deep_copy_() const;
        void multiply_col_();
        // these are used for multithreaded multiplication 
        std::mutex multi_mut;
        int next_col {0};
        int next_row {0};
        int thread_count {0};
        Matrix* rhs {nullptr};
        Matrix* result_matrix {nullptr};
        // this is implemented in the header file because it uses a template
        template <typename T>
        Matrix create_from_operation_(void ( Matrix::*operation)(T), T val) const{
            Matrix copy = this->deep_copy_();
            (copy.*operation)(val);
            return copy;
        }
};

#endif