#include <iostream>
#include <random>
#include <cmath>
#include <cassert>
#include <matrix.hpp>
#include <constants.hpp>

// === PUBLIC CONSTRUCTORS ===
template <typename T>
Matrix<T>::Matrix() : rows(0), cols(0), data() {}

template <typename T>
Matrix<T>::Matrix(Matrix& other)
  : rows(0), cols(0), data()
{
  copy_matrix(other);
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept 
  : rows(0), cols(0), data()
{
  move_matrix(std::move(other));
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols, bool random_init) 
  : rows(rows), cols(cols), data(rows*cols, T(0))
{
  if (random_init) randomize_weights();
}

// === OPERATOR OVERLOADS ===
template <typename T>
T& Matrix<T>::operator()(int row_idx, int col_idx) {
  assert(row_idx >= 0 && row_idx < rows && "row index out of bounds");
  assert(col_idx >= 0 && col_idx < cols && "col index out of bounds");
  
  return data[row_idx * cols + col_idx];
}

template <typename T>
const T& Matrix<T>::operator()(int row_idx, int col_idx) const {
  assert(row_idx >= 0 && row_idx < rows && "row index out of bounds");
  assert(col_idx >= 0 && col_idx < cols && "col index out of bounds");
  
  return data[row_idx * cols + col_idx];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix& other) {
  copy_matrix(other);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) {
  if (this != &other) {
    move_matrix(std::move(other));
  }
  return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) {
  return !(*this != other);
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) {
  if (rows != other.rows) {return true;}
  if (cols != other.cols) {return true;}
  for (int i=0; i<rows*cols; ++i) {
    if (
      other.data[i]
      && std::abs(data[i] - other.data[i]) > ml_on::DELTA
    ) {
      return true;
    }
  }
  return false;
}

// === PUBLIC GETTERS ===
template <typename T>
int Matrix<T>::get_cols() const {return cols;}

template <typename T>
int Matrix<T>::get_rows() const {return rows;}

template <typename T>
int Matrix<T>::get_size() const {return rows * cols;}

// === PUBLIC METHODS ===
template <typename T>
void Matrix<T>::print(int index) const {
  int lines;
  if (cols < index) {
    lines = cols;
  } else {
    lines = index;
  }
  
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<lines; ++j) {
      std::cout << data[i * cols + j] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
void Matrix<T>::multiply(const Matrix& other, Matrix& result) {
  int other_rows = other.rows;
  int other_cols = other.cols;
  
  assert(cols == other_rows && "dimension mismatch");
  assert(result.rows == rows && result.cols == other_cols && "result shape mismatch");
  
  for (int i=0; i<rows; ++i) {
    for (int k=0; k<cols; ++k) {
      T temp = data[i * cols + k];
      for (int j=0; j<other_cols; ++j) {
        result.data[i * other_cols + j] += temp * other.data[k * other_cols + j];
      }
    }
  }
}

template <typename T>
void Matrix<T>::multiply(const Matrix& other) {
  assert(cols == other.rows && "dimension mismatch");
  Matrix result(rows, other.cols);
  multiply(other, result);
  *this = std::move(result);
}

template <typename T>
void Matrix<T>::transpose() {
  Matrix transposed_matrix(cols, rows);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      transposed_matrix.data[j * rows + i] = data[i * cols + j];
    }
  }
  *this = std::move(transposed_matrix);
}

template <typename T>
void Matrix<T>::add_bias_vector(const Matrix& bias_vector) {
  assert(bias_vector.rows == 1 && bias_vector.cols == cols && "dimension mismatch");
  
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      data[i * cols + j] += bias_vector.data[j];
    }
  }
}

template <typename T>
T Matrix<T>::dot_product(const Matrix& other) {
  assert(rows == 1 && other.cols == 1 && "shape must be (1, N) dot (N, 1)");
  assert(cols == other.rows && "dimension mismatch");
  T sum = 0;
  for (int i=0; i<cols; ++i) {
    sum += data[i] * other.data[i];
  }
  return sum;
}

template <typename T>
Matrix<T>& Matrix<T>::drop_col(int col_idx) {
  assert(col_idx >= 0 && col_idx < cols && "col_idx out of bounds");
  int write_ptr = 0;
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      if (j == col_idx) continue;
      data[write_ptr++] = data[i*cols+j];
    }
  }
  --cols;
  data.resize(rows*cols);
  return *this;
}

// === HELPERS ===
template <typename T>
void Matrix<T>::randomize_weights() {
  std::random_device rd;
  std::mt19937 gen(rd());
  
  // Xavier (i.e. Glorot) initialization
  float limit = sqrt(6.0 / (rows + cols));
  std::uniform_real_distribution<> dis(-limit, limit);
  
  for (int i=0; i<rows*cols; ++i) {
    data[i] = dis(gen);
  }
}

template <typename T>
void Matrix<T>::copy_matrix(Matrix& other) {
  if (*this != other) {
    rows = other.rows;
    cols = other.cols;
    data = other.data;
  }
}

template <typename T>
void Matrix<T>::move_matrix(Matrix&& other) {
  rows = other.rows;
  cols = other.cols;
  data = other.data;
  other.rows = 0;
  other.cols = 0;
  other.data.clear();
}

template class Matrix<float>;
