#include <iostream>
#include <matrix.hpp>
#include <dataframe.hpp>
#include <fstream>
#include <sstream>
#include <cassert>
#include <tuple>

// === PUBLIC CONSTRUCTORS ===
DataFrame::DataFrame() : data_matrix(nullptr), header_names(nullptr), index(0) {}

DataFrame::~DataFrame() {
  delete data_matrix;
  delete[] header_names;
}

// === OPERATOR OVERLOADS ===

DataFrame* DataFrame::operator[](std::string header_name) {
  int i = 0;
  int rows = data_matrix->get_rows();
  int cols = data_matrix->get_cols();
  while (i < cols) {
    if (header_names[i] == header_name) {
      DataFrame* df = new DataFrame();
      std::string* header_name_container = new std::string[1];
      header_name_container[0] = header_name;
      df->set_header_names(header_name_container);
      Matrix m(rows, 1);
      for (int j=0; j<rows; ++j) {
        m(j, 0) = (*data_matrix)(j, i);
      }
      df->set_data_matrix(std::move(m));
      return df;
    }
    ++i;
  }
  return nullptr;
}

// === PUBLIC METHODS ===
void DataFrame::set_header_names(std::string* header_names) {
  this->header_names = header_names;
}

void DataFrame::set_data_matrix(Matrix&& data) {
  this->data_matrix = new Matrix(std::move(data));
}

void DataFrame::set_index(int index) {
  this->index = index;
}

void DataFrame::read_csv(const std::string& filename, bool header, int index) {
  std::ifstream file(filename);
  assert(file.is_open() && "error opening file");
  this->index = index;
  std::string line;
  
  // pass 1: count rows & columns
  if (header) std::getline(file, line);
  int rows = 0;
  int cols = 0;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    if (rows == 0) {
      std::stringstream ss(line);
      std::string val_str;
      
      while (std::getline(ss, val_str, ',')) {
        ++cols;
      }
    }
    ++rows;
  }
  
  // reset file read flag
  file.clear();
  file.seekg(0, std::ios::beg);
  
  // pass 2: populate header names + data matrix
  data_matrix = new Matrix(rows, cols);
  header_names = new std::string[cols];
  int r = 0;
  int c = 0;
  if (header) {
    if (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string col_name;
      while (std::getline(ss, col_name, ',')) {
        header_names[c] = col_name;
        ++c;
      }
    }
  }

  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::stringstream ss(line);
    std::string val_str;
    c = 0;
    while (std::getline(ss, val_str, ',')) {
      (*data_matrix)(r, c) = std::stod(val_str);
      ++c;
    }
    ++r;
  }
  
  file.close();
}

void DataFrame::print(int rows) const {
  for (int i=0; i<data_matrix->get_cols(); ++i) {
    std::cout << header_names[i] << "\t";
  }
  std::cout << std::endl;
  for (int i=0; i<data_matrix->get_cols(); ++i) {
    std::cout << "--------";
  }
  std::cout << std::endl;
  data_matrix->print(rows);
}

void DataFrame::info() const {
  std::cout << "RangeIndex: " << std::to_string(data_matrix->get_rows()) << " entries" << std::endl;
  std::cout << "Data Columns (total " << std::to_string(data_matrix->get_cols()) << " columns):" << std::endl;
  
  std::cout << "#\tColumn\tNull Count\n--------------------------" << std::endl;
  for (int i=0; i<data_matrix->get_cols(); ++i) {
    std::cout << std::to_string(i) << "\t" << header_names[i] << "\t";
    int null_count = 0;
    for (int j=0; j<data_matrix->get_rows(); ++j) {
      if (!(*data_matrix)(j, i)) {
        ++null_count;
      }
    }
    std::cout << std::to_string(null_count) << std::endl;
  }
  //TODO: make multi-typal
}

std::tuple<int, int> DataFrame::shape() const {
  if (!data_matrix) return {0, 0};
  return {data_matrix->get_rows(), data_matrix->get_cols()};
}

double DataFrame::sum() const {
  int rows = data_matrix->get_rows();
  int cols = data_matrix->get_cols();
  double sum = 0.0;
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      sum += (*data_matrix)(i, j);
    }
  }
  return sum;
}

double DataFrame::max() const {
  int rows = data_matrix->get_rows();
  int cols = data_matrix->get_cols();
  double max = (*data_matrix)(0, 0);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      //TODO: figure out if this is faster than just doing two read of (*data_matrix)(i, j);
      double temp = (*data_matrix)(i, j);
      if (temp > max) {
        max = temp;
      }
    }
  }
  return max;
}

double DataFrame::min() const {
  int rows = data_matrix->get_rows();
  int cols = data_matrix->get_cols();
  double min = (*data_matrix)(0, 0);
  for (int i=0; i<rows; ++i) {
    for (int j=0; j<cols; ++j) {
      double temp = (*data_matrix)(i, j);
      if (temp < min) {
        min = temp;
      }
    }
  }
  return min;
}

double DataFrame::mean() const {
  return sum()/(data_matrix->get_rows() * data_matrix->get_cols());
}

double DataFrame::median() const {
  // TODO
  return 0.0;
}

double DataFrame::mode() const {
  // TODO
  return 0.0;
}
