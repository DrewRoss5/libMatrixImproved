#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix{
    public:
        Matrix(unsigned int height, unsigned int width);
        Matrix(unsigned int height, unsigned int width, const std::vector<double>& vec);
        static Matrix identity_matrix(int size);
        ~Matrix();
        // simple getters
        unsigned int height() {return height_;}
        unsigned int width() {return width_;}
        unsigned int size() {return size_;}
        // basic IO functions
        void set(unsigned int row, unsigned int column, int value);
        double get(unsigned int row, unsigned int column) const;
        double& operator()(unsigned int row, unsigned int column); 
        double* operator[] (unsigned int row);
        friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);
        // arithmetic functions and operators
        void add(int n);
        void add(const Matrix& mat);
        void operator+=(int n);
        void operator+=(const Matrix& mat);
        Matrix operator+(int n) const;
        Matrix operator+(const Matrix& mat) const;
        void subtract(int n);
        void subtract(const Matrix& mat);
        void operator-=(int n);
        void operator-=(const Matrix& mat);
        Matrix operator-(int n) const;
        Matrix operator-(const Matrix& mat) const;
        void multiply(int n);
        Matrix multiply(const Matrix& mat) const;
        void operator*=(int n);
        Matrix operator*(const Matrix& mat) const;
        Matrix operator*(int n) const;
        // coparison operators
        bool operator==(const Matrix& mat) const;
        bool operator!=(const Matrix& mat) const;

    private:   
        double* matrix_{nullptr};
        unsigned int height_{0};
        unsigned int width_{0};
        unsigned int size_{0};
        Matrix deep_copy_() const;
        int multiply_col_(double* row, int column_no, int row_size) const;
        Matrix create_from_operation_(void ( Matrix::*operation)(int), int n) const;
        Matrix create_from_operation_(void (Matrix::*operation)(const Matrix&), const Matrix& mat) const;
};

#endif