#ifndef MATRIX_HPP
#define MATRIX_HPP 

/**
 * a Matrix represents a 2d array of doubles using a flattened array data structure.
 * index = row_idx * cols + col_idx
 */
class Matrix {
public:
  // === CONSTRUCTORS ===
  Matrix();
  ~Matrix();
  Matrix(Matrix& other_matrix);
  Matrix(Matrix&& other_matrix) noexcept;
  
  /** 
  * constructor to create a matrix with desired size
  * @param random_init 
  * if set as true, initialize matrix with random numbers,
  * else initialize all cells with zero
  */
  Matrix(int num_rows, int num_cols, bool random_init=false);

  // === OPERATOR OVERLOADS ===
  Matrix& operator=(Matrix& other_matrix);
  Matrix& operator=(Matrix&& other_matrix);
  bool operator==(const Matrix& other_matrix);
  bool operator!=(const Matrix& other_matrix);
  
  /**
  * access operator at (row_idx, col_idx).
  * @return A reference to the current matrix.
  */
  double& operator()(int row_idx, int col_idx);
  
  /**
  * access operator at (row_idx, col_idx).
  * @return A reference to the current matrix.
  */
  const double& operator()(int row_idx, int col_idx) const;

  // === GETTERS ===
  int get_cols();
  int get_rows();
  int get_size();
  
  // === METHODS ===
  void print(int index=5);
  void clear_data();
  void multiply(const Matrix& other_matrix);
  void multiply(const Matrix& other_matrix, Matrix& result_matrix);
  void transpose();
  void add_bias_vector(const Matrix& bias_vector);
  double dot_product(const Matrix& other_matrix);
    
private:
  // === ATTRIBUTES ===
  int rows, cols;
  double* data;
  
  // === HELPERS ===
  void randomize_weights();
  void copy_matrix(Matrix& other_matrix);
  void move_matrix(Matrix&& other_matrix);

};

#endif
