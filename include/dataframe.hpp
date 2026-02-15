#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <iostream>
#include <tuple>
#include <matrix.hpp>

class DataFrame {
public:
  // === CONSTRUCTORS ===
  DataFrame();
  ~DataFrame();
  
  // === METHODS ===
  void read_csv(const std::string& filename, bool header=true, int index=0);
  void print(int rows=5) const;
  void info() const;
  std::tuple<int, int> shape() const;

private:
  // === ATTRIBUTES ===
  Matrix* data_matrix;
  std::string* header_names;
  int index;

};

#endif
