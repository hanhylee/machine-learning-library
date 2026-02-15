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

// === PUBLIC METHODS ===
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
  //TODO: make multi-type
}

std::tuple<int, int> DataFrame::shape() const {
  if (!data_matrix) return {0, 0};
  return {data_matrix->get_rows(), data_matrix->get_cols()};
}
