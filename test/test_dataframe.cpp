#include <iostream>
#include <cassert>
#include <dataframe.hpp>
#include <constants.hpp>
#include <cmath>

using namespace std;
using namespace ml_on;

int main()
{
  cout << "START: dataframe tests" << endl;

  // test reading simple csv
  DataFrame test_df;
  test_df.read_csv("./test/data/test_dataframe/csv1.csv");
  test_df.print();
  test_df.info();
  auto [rows, cols] = test_df.shape();
  assert(rows == 2 && cols == 4);
  cout << "(" << rows << "," << cols << ")" << endl << endl;
  
  // test getting a series df
  test_df["a"]->print();
  assert(abs(test_df["b"]->sum() - 9.023) < DELTA);
  assert(abs(test_df["b"]->max() - 6.789) < DELTA);
  assert(abs(test_df["b"]->min() - 2.234) < DELTA);
  assert(abs(test_df["b"]->mean() - 4.5115) < DELTA);
  
  cout << "PASS: dataframe tests" << endl;
  
  return 0;
}
