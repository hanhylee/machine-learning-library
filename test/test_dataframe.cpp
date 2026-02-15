#include <iostream>
#include <cassert>
#include <dataframe.hpp>

using namespace std;

int main()
{
  // test reading simple csv
  DataFrame test_df;
  test_df.read_csv("./test/data/test_dataframe/csv1.csv");
  test_df.print();
  test_df.info();
  auto [rows, cols] = test_df.shape();
  assert(rows == 2 && cols == 4);
  cout << "(" << rows << "," << cols << ")" << endl;
  return 0;
}
