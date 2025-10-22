#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "matrix.hpp"

Matrix create_matrix(std::size_t n_rows, std::size_t n_cols) {
    Matrix output;
    output.resize(n_rows);
    for (std::size_t i = 0; i < n_rows; ++i) { //loop over every row in matrix
        output[i].resize(n_cols, 0.0);
    }
    return output;
}

Matrix load_matrix_from_file(const char* filename) {
    Matrix output;

    std::fstream input_stream;
    input_stream.open(filename);
    if (!input_stream) {
        std::cout << "Error reading matrix file: " << filename << std::endl;
    }

    std::string line;
    std::stringstream string_stream;
    while (std::getline(input_stream, line)) {
        string_stream << line;

        std::vector<double> current_row;

        double val;
        while (string_stream >> val) {
            current_row.push_back(val);
        }
        output.push_back(current_row);
    }

    // back fill empties
    size_t max_size = 0;
    for (auto& vec : output) {
        if (vec.size() > max_size) max_size = vec.size();
    }
    for (auto& vec : output) {
        vec.resize(max_size, 0.0);
    }
    return output;
}

void print_matrix(const Matrix& matrix) { //Pass by reference the Matrix vec
    size_t i, j;
    for (i = 0; i < matrix.size(); i++) {
        for (j = 0; j < matrix[0].size(); j++) {
            printf("[%zu][%zu] = %f\n", i, j, matrix[i][j]);
        }
    }
}
