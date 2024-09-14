# libMatrixImproved
An improved version of my matrix library
# Roadmap:
- Finish documentation 
- Implement determinant calculation
- Create performance benchmarks for the Matrix Class

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
    - Throws a `std::out_of_range` error if the row is greater than the matrix's height, or if the column is greater than the matrix's width.
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
### Matrix Matrix::multiply(const Matrix& mat):
- Parameters:
  - `const Matrix& mat`: The matrix to multiply this one by
- Returns:
  - The result of Matrix multliplication between this Matrix and `mat`.
- Description: Performs Matrix multiplication by multiplying this Matrix by `mat` and returns the result of the multiplicatio as a new `Matrix` object.
