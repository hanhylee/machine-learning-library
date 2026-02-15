#ifndef LINEAR_REGRESSION_HPP
#define LINEAR_REGRESSION_HPP

#include <iostream>
#include <matrix.hpp>

class LinearRegression {
public:
  LinearRegression();
  ~LinearRegression();
  
  void fit(const Matrix& X, const Matrix& y);
  void predict(const Matrix& X);
  float score(const Matrix& X, const Matrix& y);

private:
  Matrix X;
  Matrix y;
  float* coefficients;

};

#endif
