#ifndef MATRIX_HPP
#define MATRIX_HPP 

/**
 * a Matrix represents a 2d array using a flattened array data structure.
 * index = row_idx * cols + col_idx
 */
template <typename T>
class Matrix {
private:
  int rows, cols;
  std::vector<T> data;
  
  // === HELPERS ===
  void randomize_weights();
  void copy_matrix(Matrix<T>& other);
  void move_matrix(Matrix<T>&& other);

public:
  // === CONSTRUCTORS ===
  Matrix();
  Matrix(Matrix<T>& other);
  Matrix(Matrix<T>&& other) noexcept;
  
  /** 
  * constructor to create a matrix with desired size
  * @param random_init 
  * if set as true, initialize matrix with random numbers,
  * else initialize all cells with zero
  */
  Matrix(int rows, int cols, bool random_init=false);
  
  // === OPERATOR OVERLOADS ===
  Matrix<T>& operator=(Matrix<T>& other);
  Matrix<T>& operator=(Matrix<T>&& other);
  bool operator==(const Matrix<T>& other);
  bool operator!=(const Matrix<T>& other);
  
  /**
  * access operator at (row_idx, col_idx).
  * @return A reference to the current matrix.
  */
  T& operator()(int row_idx, int col_idx);
  const T& operator()(int row_idx, int col_idx) const;
  
  // === GETTERS ===
  int get_cols() const;
  int get_rows() const;
  int get_size() const;
  
  // === METHODS ===
  void print(int rows=5) const;
  void clear_data();
  void multiply(const Matrix<T>& other);
  void multiply(const Matrix<T>& other, Matrix<T>& result);
  void transpose();
  void add_bias_vector(const Matrix<T>& bias_vector);
  T dot_product(const Matrix<T>& other);
  Matrix<T>& drop_col(int col_idx);

};

#endif
