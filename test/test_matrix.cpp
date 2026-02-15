#include <iostream>
#include <cassert>
#include <cmath>
#include <matrix.hpp>
#include <constants.hpp>

using namespace std;
using namespace ml_on;

int main()
{
  cout << "START: matrix tests" << endl << endl;

  // test empty constructor
  Matrix m1;
  assert(m1.get_rows() == 0);
  assert(m1.get_cols() == 0);
  
  // test zero matrix constructor with size 2x2
  Matrix m2(2, 2);
  assert(m2.get_rows() == 2);
  assert(m2.get_cols() == 2);
  assert(m2(0, 0) == 0);
  assert(m2(0, 1) == 0);
  assert(m2(1, 0) == 0);
  assert(m2(1, 1) == 0);
  
  // test random matrix constructor with size 2x2
  Matrix m3(2, 2, true);
  assert(m3.get_rows() == 2);
  assert(m3.get_cols() == 2);
  cout << "printing randomized 2x2 matrix..." << endl;
  m3.print();
  
  // test copy constructor
  Matrix m4(m3);
  assert(m4.get_rows() == 2);
  assert(m4.get_cols() == 2);
  assert(abs(m4(0, 0) - m3(0, 0)) < DELTA);
  assert(abs(m4(0, 1) - m3(0, 1)) < DELTA);
  assert(abs(m4(1, 0) - m3(1, 0)) < DELTA);
  assert(abs(m4(1, 1) - m3(1, 1)) < DELTA);
  cout << "printing copied 2x2 matrix..." << endl;
  m4.print();
  
  // test transpose
  m4.transpose();
  assert(abs(m4(0, 0) - m3(0, 0)) < DELTA);
  assert(abs(m4(0, 1) - m3(1, 0)) < DELTA);
  assert(abs(m4(1, 0) - m3(0, 1)) < DELTA);
  assert(abs(m4(1, 1) - m3(1, 1)) < DELTA);
  cout << "printing transposed 2x2 matrix..." << endl;
  m4.print();
  
  // test multiply
  Matrix m5(2, 2);
  m2.multiply(m4, m5);
  cout << "printing 2x2 matrix multiplied by zero matrix..." << endl;
  m5.print();
  
  // test add_bias_vector
  Matrix m6(1, 2);
  m6(0, 0) = 4.0;
  m6(0, 1) = 7.0;
  m5.add_bias_vector(m6);
  assert(abs(m5(0, 0) - 4.0) < DELTA);
  assert(abs(m5(0, 1) - 7.0) < DELTA);
  assert(abs(m5(1, 0) - 4.0) < DELTA);
  assert(abs(m5(1, 1) - 7.0) < DELTA);
  cout << "added bias vector (4.0, 7.0)..." << endl;
  m5.print();
  
  // test dot_product
  Matrix m7(2, 1);
  m7(0, 0) = 5.0;
  m7(1, 0) = 5.0;
  assert(abs(m6.dot_product(m7) - 55.0) < DELTA);
  cout << "dot_product of (4, 7) and (5, 5): " << m6.dot_product(m7) << endl;
  
  cout << endl << "PASS: matrix tests" << endl << endl;
  
  return 0;
}
