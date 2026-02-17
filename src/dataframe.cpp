#include <iostream>
#include <matrix.hpp>
#include <dataframe.hpp>
#include <fstream>
#include <sstream>
#include <cassert>
#include <tuple>

// === PUBLIC CONSTRUCTORS ===
template <typename T>
DataFrame<T>::DataFrame() : data(), headers(), index(0) {}

// === OPERATOR OVERLOADS ===
template <typename T>
DataFrame<T> DataFrame<T>::operator[](std::string header_name) {
  int col_idx = -1;
  for (int i=0; i<(int)headers.size(); ++i) {
    if (headers[i] != header_name) continue;
    col_idx = i;
    break;
  }
  assert(col_idx != -1 && "header not found");
  
  DataFrame<T> df;
  Matrix<T> m(data.get_rows(), 1);
  for (int i=0; i<data.get_rows(); ++i) {
    m(i, 0) = data(i, col_idx);
  }
  df.set_headers({header_name});
  df.set_data(std::move(m));

  return df;
}

template <typename T>
DataFrame<T> DataFrame<T>::operator[](std::vector<std::string> header_names) {
  DataFrame<T> df;
  Matrix<T> m(data.get_rows(), header_names.size());
  
  for (int k=0; k<(int)header_names.size(); ++k) {
    std::string target = header_names[k];
    int source_idx = -1;
    for (int i=0; i<(int)this->headers.size(); ++i) {
      if (this->headers[i] != target) continue;
      source_idx = i;
      break;
    }

    if (source_idx == -1) continue;
    
    for (int i=0; i<data.get_rows(); ++i) {
      m(i, k) = data(i, source_idx);
    }
  }
  
  df.set_headers(header_names);
  df.set_data(std::move(m));
  return df;
}

// === PUBLIC METHODS ===
template <typename T>
void DataFrame<T>::set_headers(std::vector<std::string> header_names) {
  this->headers = header_names;
}

template <typename T>
void DataFrame<T>::set_data(Matrix<T>&& data) {
  this->data = std::move(data);
}

template <typename T>
void DataFrame<T>::set_index(int index) {
  this->index = index;
}

template <typename T>
DataFrame<T>& DataFrame<T>::drop(std::vector<std::string> targets) {
  for (std::string target: targets) {
    for (int i=(int)headers.size()-1; i>=0; --i) {
      if (headers[i] != target) continue;
      data.drop_col(i);
      headers.erase(headers.begin() + i);
      break;
    }
  }
  return *this;
}

template <typename T>
void DataFrame<T>::read_csv(const std::string& filename, bool has_header, int index) {
  std::ifstream file(filename);
  assert(file.is_open() && "error opening file");
  this->index = index;
  std::string line;
  //TODO: type safety for numeric cols std::vector<bool> column_is_numeric;
  
  int rows = 0;
  int cols = 0;
  
  // pass 1: count rows & columns
  if (has_header) std::getline(file, line);
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    if (rows == 0) {
      std::stringstream ss(line);
      std::string val_str;
      while (std::getline(ss, val_str, ',')) ++cols;
    }
    ++rows;
  }
  
  // reset file read flag
  file.clear();
  file.seekg(0, std::ios::beg);
  
  // pass 2: populate header names + data matrix
  data = Matrix<T>(rows, cols);
  headers.clear();
  
  if (has_header) {
    std::getline(file, line);
    std::stringstream ss(line);
    std::string col_name;
    while (std::getline(ss, col_name, ',')) {
      headers.push_back(col_name);
    }
  } else {
    // generate default headers if none provided
    for(int i=0; i<cols; ++i) {
      this->headers.push_back("col_" + std::to_string(i));
    }
  }
  
  int r = 0;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::stringstream ss(line);
    std::string val_str;
    int c = 0;
    while (std::getline(ss, val_str, ',')) {
      std::stringstream converter(val_str);
      T value;
      converter >> value;
      this->data(r, c) = value;
      c++;
    }
    ++r;
  }
  
  file.close();
}

template <typename T>
void DataFrame<T>::print(int rows) const {
  for (int i=0; i<data.get_cols(); ++i) {
    std::cout << headers[i] << "\t";
  }
  std::cout << std::endl;
  for (int i=0; i<data.get_cols(); ++i) {
    std::cout << "--------";
  }
  std::cout << std::endl;
  data.print(rows);
}

template <typename T>
void DataFrame<T>::info() const {
  std::cout << "RangeIndex: " << std::to_string(data.get_rows()) << " entries" << std::endl;
  std::cout << "Data Columns (total " << std::to_string(data.get_cols()) << " columns):" << std::endl;
  
  std::cout << "#\tColumn\tNull Count\n--------------------------" << std::endl;
  for (int i=0; i<data.get_cols(); ++i) {
    std::cout << std::to_string(i) << "\t" << headers[i] << "\t";
    int null_count = 0;
    for (int j=0; j<data.get_rows(); ++j) {
      if (data(j, i)) {
        ++null_count;
      }
    }
    std::cout << std::to_string(null_count) << std::endl;
  }
}

template <typename T>
std::tuple<int, int> DataFrame<T>::shape() const {
  if (data.get_size() == 0) return {0, 0};
  return {data.get_rows(), data.get_cols()};
}

template <typename T>
double DataFrame<T>::sum() const {
  int rows = data.get_rows();
  int cols = data.get_cols();
  double sum = 0.0;
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      sum += data(i, j);
    }
  }
  return sum;
}

template <typename T>
double DataFrame<T>::max() const {
  int rows = data.get_rows();
  int cols = data.get_cols();
  double max = data(0, 0);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      if (data(i, j) > max) {
        max = data(i, j);
      }
    }
  }
  return max;
}

template <typename T>
double DataFrame<T>::min() const {
  int rows = data.get_rows();
  int cols = data.get_cols();
  double min = data(0, 0);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      if (data(i, j) < min) {
        min = data(i, j);
      }
    }
  }
  return min;
}

template <typename T>
double DataFrame<T>::mean() const {
  return sum()/(data.get_rows() * data.get_cols());
}

template <typename T>
double DataFrame<T>::median() const {
  // TODO
  return 0.0;
}

template <typename T>
double DataFrame<T>::mode() const {
  // TODO
  return 0.0;
}

template class DataFrame<float>;
