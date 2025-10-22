#pragma once

#include <vector>

/* Data structure */

using Matrix = std::vector<std::vector<double>>;

/* Interfaces */
Matrix create_matrix(std::size_t n_rows, std::size_t n_cols);
Matrix load_matrix_from_file(const char* filename);
void print_matrix(const Matrix& matrix);