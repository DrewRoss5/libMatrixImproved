#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix{
    public:
        Matrix(unsigned int height, unsigned int width);
        ~Matrix();
        // simple getters
        unsigned int height() {return height_;}
        unsigned int width() {return width_;}
        unsigned int size() {return size_;}
        // basic IO functions
        void set(unsigned int row, unsigned int column, int value);
        const int get(unsigned int row, unsigned int column);
        int* operator[] (unsigned int row);
        friend std::ostream& operator<<(std::ostream& out, Matrix& mat);
        // arithmetic functions and operators
        void add(int n);
        void add(const Matrix& mat);
        void operator+=(int n);
        void operator+=(const Matrix& mat);
        void subtract(int n);
        void subtract(const Matrix& mat);
        void operator-=(int n);
        void operator-=(const Matrix& mat);
        void multiply(int n);
        Matrix multiply(Matrix& mat);
        void operator*=(int n);
        void operator*=(const Matrix& mat);
    private:   
        int* matrix_{nullptr};
        unsigned int height_{0};
        unsigned int width_{0};
        unsigned int size_{0};
        const Matrix deep_copy_();
        const int multiply_col_(int* row, int column_no, int row_size);
};

#endif