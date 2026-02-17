#ifndef LINEAR_REGRESSION_HPP
#define LINEAR_REGRESSION_HPP

#include <iostream>
#include <dataframe.hpp>

template <typename T>
class LinearRegression {
public:
  LinearRegression();
  ~LinearRegression();
  
  void fit(const DataFrame<T>& X, const DataFrame<T>& y);
  void predict(const DataFrame<T>& X);
  float score(const DataFrame<T>& X, const DataFrame<T>& y);

private:
  DataFrame<T> X;
  DataFrame<T> y;
  float* coefficients;

};

#endif
