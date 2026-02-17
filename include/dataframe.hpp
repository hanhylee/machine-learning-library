#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <iostream>
#include <tuple>
#include <matrix.hpp>

template <typename T>
class DataFrame {
private:
  Matrix<T> data;
  std::vector<std::string> headers;
  //TODO std::unordered_map<std::string, int> header_lookup;
  int index;

public:
  // === CONSTRUCTORS ===
  DataFrame();

  // === OPERATOR OVERLOADS ===
  
  /**
  * access operator for columns with the given name(s).
  * @return a reference to a dataframe with only the data from the requested columns.
  */
  DataFrame operator[](std::string header_name);
  DataFrame operator[](std::vector<std::string> header_names);
  
  // === METHODS ===
  void set_headers(std::vector<std::string> header_names);
  void set_data(Matrix<T>&& data);
  void set_index(int index);
  DataFrame& drop(std::vector<std::string> targets);
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
};

#endif
