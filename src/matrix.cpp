#include <iostream>
#include <random>
#include <cmath>
#include <cassert>
#include <matrix.hpp>
#include <constants.hpp>

// === PUBLIC CONSTRUCTORS ===
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::~Matrix() {
  clear_data();
}

Matrix::Matrix(Matrix& other_matrix)
  : rows(0), cols(0), data(nullptr)
{
  copy_matrix(other_matrix);
}

Matrix::Matrix(Matrix&& other_matrix) noexcept 
  : rows(0), cols(0), data(nullptr)
{
  move_matrix(std::move(other_matrix));
}

Matrix::Matrix(int rows, int cols, bool random_init) 
  : rows(rows), cols(cols), data(nullptr)
{
  data = new double[rows * cols]();

  if (random_init) {
    randomize_weights();
  }
}

// === OPERATOR OVERLOADS ===
double& Matrix::operator()(int row_idx, int col_idx) {
  assert(row_idx >= 0 && row_idx < rows && "row index out of bounds");
  assert(col_idx >= 0 && col_idx < cols && "col index out of bounds");
  
  return data[row_idx * cols + col_idx];
}

const double& Matrix::operator()(int row_idx, int col_idx) const {
  assert(row_idx >= 0 && row_idx < rows && "row index out of bounds");
  assert(col_idx >= 0 && col_idx < cols && "col index out of bounds");
  
  return data[row_idx * cols + col_idx];
}

Matrix& Matrix::operator=(Matrix& other_matrix) {
  copy_matrix(other_matrix);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other_matrix) {
  if (this != &other_matrix) {
    move_matrix(std::move(other_matrix));
  }
  return *this;
}

bool Matrix::operator==(const Matrix& other_matrix) {
  return !(*this != other_matrix);
}

bool Matrix::operator!=(const Matrix& other_matrix) {
  if (rows != other_matrix.rows) {return true;}
  if (cols != other_matrix.cols) {return true;}
  for (int i=0; i<rows*cols; ++i) {
    if (
      other_matrix.data[i] 
      && std::abs(data[i] - other_matrix.data[i]) > ml_on::DELTA
    ) {
      return true;
    }
  }
  return false;
}

// === PUBLIC GETTERS ===
int Matrix::get_cols() {return cols;}
int Matrix::get_rows() {return rows;}
int Matrix::get_size() {return rows * cols;}

// === PUBLIC METHODS ===
void Matrix::print(int index) {
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

void Matrix:: clear_data() {
  rows = 0;
  cols = 0;
  delete[] data;
}

void Matrix::multiply(const Matrix& other_matrix, Matrix& result_matrix) {
  int other_rows = other_matrix.rows;
  int other_cols = other_matrix.cols;
  double* other_data = other_matrix.data;
  double* result_data = result_matrix.data;
  
  assert(cols == other_rows && "dimension mismatch");
  assert(result_matrix.rows == rows && result_matrix.cols == other_cols && "result shape mismatch");
  
  for (int i=0; i<rows; ++i) {
    for (int k=0; k<cols; ++k) {
      double temp = data[i * cols + k];
      
      for (int j=0; j<other_cols; ++j) {
        result_data[i * other_cols + j] += temp * other_data[k * other_cols + j];
      }
    }
  }
}

void Matrix::multiply(const Matrix& other_matrix) {
  assert(cols == other_matrix.rows && "dimension mismatch");
  Matrix result_matrix(rows, other_matrix.cols);
  multiply(other_matrix, result_matrix);
  *this = std::move(result_matrix);
}

void Matrix::transpose() {
  Matrix transposed_matrix(cols, rows);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      transposed_matrix.data[j * rows + i] = data[i * cols + j];
    }
  }
  *this = std::move(transposed_matrix);
}

void Matrix::add_bias_vector(const Matrix& bias_vector) {
  assert(bias_vector.rows == 1 && bias_vector.cols == cols && "dimension mismatch");
  
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      data[i * cols + j] += bias_vector.data[j];
    }
  }
}

double Matrix::dot_product(const Matrix& other_matrix) {
  assert(rows == 1 && other_matrix.cols == 1 && "shape must be (1, N) dot (N, 1)");
  assert(cols == other_matrix.rows && "dimension mismatch");
  double sum = 0.0;
  for (int i=0; i<cols; ++i) {
    sum += data[i] * other_matrix.data[i];
  }
  return sum;
}

// === HELPERS ===
void Matrix::randomize_weights() {
  std::random_device rd;
  std::mt19937 gen(rd());
  
  // Xavier (i.e. Glorot) initialization
  double limit = sqrt(6.0 / (rows + cols));
  std::uniform_real_distribution<> dis(-limit, limit);
  
  for (int i=0; i<rows*cols; ++i) {
    data[i] = dis(gen);
  }
}

void Matrix::copy_matrix(Matrix& other_matrix) {
  if (*this != other_matrix) {
    rows = other_matrix.rows;
    cols = other_matrix.cols;
    if (data) {delete[] data;}
    data = new double[rows * cols];
    std::copy(
      other_matrix.data, 
      other_matrix.data + (rows * cols), 
      data
    );
  }
}

void Matrix::move_matrix(Matrix&& other_matrix) {
  if (data) {delete[] data;}
  rows = other_matrix.rows;
  cols = other_matrix.cols;
  data = other_matrix.data;
  other_matrix.rows = 0;
  other_matrix.cols = 0;
  other_matrix.data = nullptr;
}
