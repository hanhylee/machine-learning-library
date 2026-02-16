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

  // === OPERATOR OVERLOADS ===
  
  /**
  * access operator for a column with the given name.
  * @return a pointer to a dataframe with only the data from the column.
  */
  DataFrame* operator[](std::string header_name);
  // const Matrix& operator()(std::string header_name) const;
  
  // === METHODS ===
  void set_header_names(std::string* header_names);
  void set_data_matrix(Matrix&& data);
  void set_index(int index);
  void read_csv(const std::string& filename, bool header=true, int index=0);
  void print(int rows=5) const;
  void info() const;
  std::tuple<int, int> shape() const;
  double sum() const;
  double max() const;
  double min() const;
  double mean() const;
  double median() const;
  double mode() const;

private:
  // === ATTRIBUTES ===
  Matrix* data_matrix;
  std::string* header_names;
  int index;

};

#endif
