#include <stdexcept>
#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include <thread>
#include <mutex>

#include "matrix.h"

// main constructor
Matrix::Matrix(unsigned height, unsigned width){
    this->matrix_ = new double[width * height]; // while matrices are two-dimensional, this is implemented as a one-dimensional array for performance purposes
    this->width_ = width;
    this->height_ = height;
    this->size_ = width * height;
    this->thread_count =  std::thread::hardware_concurrency();
    // fill the matrix with zeroes to avoid undefined behavior
    std::memset(this->matrix_, 0, (sizeof(double) * (this->width_ * this->height_)));

}

// constructs a Matrix from the provided vector, thorws a std::invalid_argument if the vector is the incorrect size
Matrix::Matrix(unsigned height, unsigned width, const std::vector<double>& vec){
    this->width_ = width;
    this->height_ = height;
    this->size_ = width * height;
    this->thread_count =  std::thread::hardware_concurrency();
    // ensure the vector is the correct size
    if (vec.size() != this->size_)
        throw std::invalid_argument("The size of the vector does not match the size of the matrix");
    // copy the data over
    this->matrix_ = new double[this->size_]; 
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] = vec[i];
}

// copy consturctor for the Matrix class
Matrix::Matrix(const Matrix& mat){
    *this = mat;
}

// operator for the copy constructor, also cleans up the assigned matrix
Matrix& Matrix::operator=(const Matrix& mat){
    this->height_ = mat.height_;
    this->width_ = mat.width_;
    this->size_ = mat.size_;
    this->thread_count =  mat.thread_count;
    // copy the contents of the matrix
    this->matrix_ = new double[size_];
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] = mat.matrix_[i];
    return *this;
}

// constructs an identity Matrix of a given size
Matrix Matrix::identity_matrix(int size){
    Matrix identity_mat = Matrix(size, size);
    for (int i = 0; i < size; i++)
        identity_mat.matrix_[(size * i) + i] = 1;
    return identity_mat;    
} 

// constructs a randomized matrix
Matrix Matrix::random_matrix(unsigned width, unsigned height, int min, int max){
    std::srand(time(0));
    Matrix random = Matrix(width, height);
    for (int i = 0; i < random.size_; i++)
        random.matrix_[i] = (min + std::rand()) % max;
    return random;
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
void Matrix::set(unsigned row, unsigned column, int value){
    if (row >= height_ || row >= width_)
        throw std::out_of_range("The row or column are out of range");
    this->matrix_[(row * width_) + column] = value;
}

// returns the value of a single element in the matrix, throws a std::out_of_bounds if the indexes are out of bounds
double Matrix::get(unsigned row, unsigned column) const{
    if (row >= height_ || row >= width_)
        throw std::out_of_range("The row or column are out of range");   
    return this->matrix_[(row * width_) + column];
}

double& Matrix::operator()(unsigned row, unsigned column){
    if (row >= height_ || row >= width_)
        throw std::out_of_range("The row or column are out of range");
    return this->matrix_[(width_ * row) + column];
}

// returns a "row" in the matrix (this should be used with caution, as the resulting row may be used to access other rows) throws a std::out_of_range if the row number is out of bounds
double* Matrix::operator[](unsigned row){
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
        throw std::invalid_argument("Matrices must be the same size to be subtracted");
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] -= mat.matrix_[i];  
}

// multiplies each element in the Matrix by a number
void Matrix::multiply(int n){
    for (int i = 0; i < this->size_; i++)
        this->matrix_[i] *= n;
}

// calculates the next element in the result matrix
void Matrix::multiply_col_() {
    this->multi_mut.lock();
    // we've reached the end of multiplication
    if (this->next_row >= this->height_){
        this->multi_mut.unlock();
        return;
    }
    int local_row = this->next_row;
    int local_col = this->next_col; 
    this->next_col++;
    if (this->next_col==  rhs->width_){
        this->next_col = 0;
        this->next_row++;
    }
    this->multi_mut.unlock();
    // multiply the ith row of this matrix by the jth column of the right hand side
    int row_offset = local_row * this->width_;
    int sum = 0;
    for (int i = 0; i < this->width_; i++)
        sum += (this->matrix_[row_offset + i] * rhs->matrix_[(rhs->width_ * i) + local_col]);
    // update the result matrix (this doesn't need lock the mutex as only one thread should ever access a particular element)
    (*this->result_matrix)[local_row][local_col] = sum;
    multiply_col_();
}

// multiplies two matrices this matrix by a given matrix, and returns the result. Throws a std::invalid_argument if they are the incorrect size 
Matrix Matrix::multiply(Matrix& mat){
    // validate the two matrices are the correct size
    if (this->width_ != mat.height_)
        throw std::invalid_argument("Invalid matrix sizes for multiplication");
    // multiply the matrices
    Matrix result = Matrix(this->height_, mat.width_);
    this->result_matrix = &result;
    this->rhs = &mat;
    std::thread* threads = new std::thread[this->thread_count];
    for (int i = 0; i < this->thread_count; i++)
        threads[i] = std::thread(&Matrix::multiply_col_, this);
    for (int i = 0; i < this->thread_count; i++)
        threads[i].join();
    // clean up temporary variables and thread memory
    delete[] threads;
    this->next_col = 0;
    this->next_row = 0;
    this->rhs = nullptr;
    this->result_matrix = nullptr;
    return std::move(result);
}

// arithmatic operators
void Matrix::operator+=(int n){this->add(n);}
void Matrix::operator+=(const Matrix& mat){this->add(mat);}
void Matrix::operator-=(int n){this->subtract(n);}
void Matrix::operator-=(const Matrix& mat){this->subtract(mat);}
void Matrix::operator*=(int n){this->multiply(n);}
Matrix Matrix::operator*(Matrix& mat) {return this->multiply(mat);} 

// used for these operators
Matrix Matrix::operator+(int n) const {return this->create_from_operation_(&Matrix::add, n);}
Matrix Matrix::operator+(const Matrix& mat) const {return this->create_from_operation_<const Matrix&>(&Matrix::add, mat);}
Matrix Matrix::operator-(int n) const {return this->create_from_operation_(&Matrix::subtract, n);}
Matrix Matrix::operator-(const Matrix& mat) const {return this->create_from_operation_<const Matrix&>(&Matrix::subtract, mat);}
Matrix Matrix::operator*(int n) const {return this->create_from_operation_(&Matrix::multiply, n);}

// comparision operators
bool Matrix::operator==(const Matrix& mat) const {
    if (this->height_ != mat.height_ || this->width_ != mat.width_)
        return false;
    return !memcmp(this->matrix_, mat.matrix_, (this->size_ * sizeof(double)));
}

bool Matrix::operator!=(const Matrix& mat) const{
    return !(*this == mat);
}
