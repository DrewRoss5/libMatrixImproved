# libMatrixImproved
A Matrix Library in C++ written to prioritize performance. 

# API: 
## Constructors:
### Matrix::Matrix(int height, int width):
- Parameters:
  - `int width`: The width of the matrix.
  - `int height`: The height of the matrix.
- Description:
  - The default constructor for the Matrix class, creates an empty matrix of the specified width and height.
- Notes:
  - By default, all elements of the Matrix are set to 0.
### Matrix::Matrix(int height, int width, const std::vector<double>& data):
- Parameters:
  - `int width`: The width of the matrix.
  - `int height`: The height of the matrix.
  - `const std::vector<double>& data`: The data to populate the Matrix with.
- Description:
  - A constructor for the Matrix class, uses the data from the vector to populate the matrix
- Notes:
  - Throws a `std::invalid_argument` exception if the size of `data` doesn't equal width * height.
 ### Matrix::Matrix(const Matrix& mat):
 - Parameters:
   - `const Matrix& mat`: The matrix to be copied
- Description:
  - The copy constructor for the Matrix class. Creates a deep copy of `mat`
- Notes:
  -  Simmilar behavior can be achieved using the `=` operator.
 ## Getters: 
 ### int Matrix::height():
 - Parameters:
    - None
  - Return type:
    - `int`
  - Returns:
    - The height of the Matrix.
### int Matrix::width():
 - Parameters:
    - None
  - Return type:
    - `int`
  - Returns:
    - The width of the Matrix.
### int Matrix::size():
 - Parameters:
    - None
  - Return type:
    - `int`
  - Returns:
    - The size of the Matrix (width * height).
### double Matrix::get(int row, int col):
  - Parameters:
    - `int row`: The row to get the element from.
    - `int col`: The column to get the element from.
  - Return type:
    - `double`
  - Returns:
    - The element at (row, col)
  - Notes:
    - Like arrays, matrices are zero-indexed, for example to get the element in the first column of the first row: `my_matrix.get(0, 0);`
    - Throws a `std::out_of_range` error if the row is greater than the matrix's height, or if the column is greater than the matrix's width
## Matrix Arithmetic:
### void Matrix::add(const Matrix& mat):
- Parameters: 
  - `const Matrix& mat`: The matrix to add to this one.
- Returns:
  - `void`
- Description: Adds each element of `mat` to each corresponding element of this matrix
- Notes: throws a `std::invalid_argument` if the width or height of either matrix is different.
### void Matrix::subtract(const Matrix& mat):
  - See above, but for subtraction
### Matrix Matrix::multiply(Matrix& mat):
- Parameters:
  - `const Matrix& mat`: The matrix to multiply this one by. 
- Returns:
  - The result of Matrix multliplication between this Matrix and `mat`.
- Description: Performs Matrix multiplication by multiplying this Matrix by `mat` and returns the result of the multiplication as a new `Matrix` object. This will use all cores available on the CPU.
### Matrix Matrix::multiply_singlethread(Matrix& mat):
- Parameters:
  - `const Matrix& mat`: The matrix to multiply this one by. 
- Returns:
  - The result of Matrix multliplication between this Matrix and `mat`.
- Description: Performs Matrix multiplication by multiplying this Matrix by `mat` and returns the result of the multiplication as a new `Matrix` object. This will use only one thread.
## Double Arithmetic:
### void Matrix::add(double n):
- Parameters:
  - `double n`: The number to add to each element in the Matrix.
- Returns:
  - `void`
- Description:
  - adds `n` to each element in the Matrix.
### void Matrix::sub(dobule n):
  - See above, but for subtraction
### void Matrix::multiply(double n).
  - See above, but for multiplication.
## Operators:
### Addition:
#### void operator+=(double n) / void operator+=(const Matrix& mat):
  - Adds `n` or `mat` to the Matrix.
  - Notes:
    - Throws a `std::invalid argument` if `mat` is a different size than this object
#### Matrix operator+(double n) / Matrix operator+(const Matrix& mat):
  - Creates a copy of this object, adds `n` or `mat` to it, and returns it
  - Notes:
    - Throws a `std::invalid argument` if `mat` is a different size than this object
### Subtraction:
#### void operator-=(double n) / void operator-=(const Matrix& mat):
  - Subtract `n` or `mat` from the Matrix:
  - Notes:
    - Throws a `std::invalid argument` if `mat` is a different size than this object
#### Matrix operator-(double n) / Matrix operator-(const Matrix& mat):
  - Creates a copy of this object, subtracts `n` or `mat` from it, and returns it
  - Notes:
    - Throws a `std::invalid argument` if `mat` is a different size than this object
### Multiplication:
#### void operator*=(double n):
  - multiplies each element in the Matrix by `n`
#### Matrix operator*(double n):
  - Creates a copy of this object, multiplies each element in the copy by `n` and returns it.
#### Matrix operator*(Matrix& mat)
  - Returns the product of Matrix multlipication between this object and `mat`
  - Notes:
    - Throws a `std::invalid_argument` if the Matrix sizes are incorrect for Matrix multiplication
    - Uses the multithreaded implementation of multiplication.
