#include <stdexcept>
#include <iostream>

#include "matrix.h"

// main constructor
Matrix::Matrix(unsigned int height, unsigned int width){
    this->matrix_ = new double[width * height]; // while matrices are two-dimensional, this is implemented as a one-dimensional array for performance purposes
    this->width_ = width;
    this->height_ = height;
    this->size_ = width * height;
}

// main destructor, frees the memory and overwrites the pointer
Matrix::~Matrix(){
    delete[] this->matrix_;
    this->matrix_ = nullptr;
}

// returns a deep copy of the matix 
Matrix Matrix::deep_copy_() const{
    Matrix new_mat(this->height_, this->width_);
    for (int i = 0; i < this->size_; i++)
        new_mat.matrix_[i] = this->matrix_[i];
    return new_mat;
}

// sets the value of a single element in the matrix, throws a std::out_of_bounds if the indexes are out of bounds
void Matrix::set(unsigned int row, unsigned int column, int value){
    if (row >= height_ || row >= width_)
        throw std::out_of_range("The row or column are out of range");
    this->matrix_[(row * width_) + column] = value;
}

// returns the value of a single element in the matrix, throws a std::out_of_bounds if the indexes are out of bounds
int Matrix::get(unsigned int row, unsigned int column) const{
    if (row >= height_ || row >= width_)
        throw std::out_of_range("The row or column are out of range");   
    return this->matrix_[(row * width_) + column];
}

// returns a "row" in the matrix (this should be used with caution, as the resulting row may be used to access other rows) throws a std::out_of_range if the row number is out of bounds
double* Matrix::operator[](unsigned int row){
    if (row >= this->height_)
        throw std::out_of_range("Row number out of bounds");
    return this->matrix_ + (row * this->width_);
}

// writes the contents of the matrix to an ostream
std::ostream& operator<<(std::ostream& out, const Matrix& mat){
    for (int i = 0; i < mat.size_; i++){
        out << mat.matrix_[i];
        if ((i + 1) % mat.width_ == 0 && i != 0)
            out << std::endl;
        else
            out << ", ";
    }
    return out;
}

// adds an integer to each element in the matrix
void Matrix::add(int n){
    for (int i = 0; i < size_; i++)
        this->matrix_[i] += n;
}

// adds two matrices together, throws a std::invalid_argument if the second matrix is a different size
void Matrix::add(const Matrix& mat){
    if (mat.height_ != this->height_ || mat.width_ != this->width_)
        throw std::invalid_argument("Matrices must be the same size to be added");
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] += mat.matrix_[i];  
}

// subtracts an integer from each element in the matrix
void Matrix::subtract(int n){
    for (int i = 0; i < size_; i++)
        this->matrix_[i] -= n;
}

// subtracts two matrices, throws a std::invalid_argument if the second matrix is a different size
void Matrix::subtract(const Matrix& mat){
    if (mat.height_ != this->height_ || mat.width_ != this->width_)
        throw std::invalid_argument("Matrices must be the same size to be added");
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] -= mat.matrix_[i];  
}

// multiplies each number in a given row by each number in a provided column from this matrix
 int Matrix::multiply_col_(double* row, int column_no, int row_size) const{
    int sum = 0;
    for (int i = 0; i < row_size; i++)
        sum += row[i] * this->matrix_[(i * width_) + column_no];
    return sum;
}

// multiplies each element in the Matrix by a number
void Matrix::multiply(int n){
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] *= n;
}

// multiplies two matrices, throws a std::invalid_argument if they are the incorrect size 
Matrix Matrix::multiply(const Matrix& mat) const{
    // validate the two matrices are the correct size
    if (this->width_ != mat.height_)
        throw std::invalid_argument("Invalid matrix sizes for multiplication");
    Matrix result(this->height_, mat.width_);
    // calculate and insert the values in the matrix
    double* row;
    for (int i = 0; i < this->height_; i++){
        for (int j = 0; j < mat.width_; j++){
            row = this->matrix_ + (this->width_ * i);
            result.matrix_[(mat.width_ * i) + j] = mat.multiply_col_(row, j, this->width_);
        }
    }
    return result;
}

// arithmatic operators
void Matrix::operator+=(int n){this->add(n);}
void Matrix::operator+=(const Matrix& mat){this->add(mat);}
void Matrix::operator-=(int n){this->subtract(n);}
void Matrix::operator-=(const Matrix& mat){this->subtract(mat);}
void Matrix::operator*=(int n){this->multiply(n);}
Matrix Matrix::operator*(const Matrix& mat) const{return this->multiply(mat);} 
// TODO: Condense these using a template
// these are used to create a new matrix and apply an opperation to them
Matrix Matrix::create_from_operation_(void (Matrix::*operation)(int), int n) const{
    Matrix copy = this->deep_copy_();
    (copy.*operation)(n);
    return copy;
}
Matrix Matrix::create_from_operation_(void (Matrix::*operation)(const Matrix& mat), const Matrix& mat) const{
    Matrix copy = this->deep_copy_();
    (copy.*operation)(mat);
    return copy;
}
// used for these operators
Matrix Matrix::operator+(int n) const {return this->create_from_operation_(&Matrix::add, n);}
Matrix Matrix::operator+(const Matrix& mat) const {return this->create_from_operation_(&Matrix::add, mat);}
Matrix Matrix::operator-(int n) const {return this->create_from_operation_(&Matrix::subtract, n);}
Matrix Matrix::operator-(const Matrix& mat) const {return this->create_from_operation_(&Matrix::subtract, mat);}
Matrix Matrix::operator*(int n) const {return this->create_from_operation_(&Matrix::multiply, n);}
