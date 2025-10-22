#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

#include "vector.hpp"

/* double Vector::operator[](size_t index) {
    return element[index];
} */

//Vector::Vector(size_t size): element(size, 0.0) {}

Vector create_vector(size_t size) {
    Vector output;
    output.resize(size); //Resizes vector array to size provided, initialised with 0
    return output;
}

Vector load_vec_from_file(const char* filename) {
    Vector output;

    std::fstream input_stream;
    input_stream.open(filename);
    double value;

    while (input_stream >> value) { //extracts the digit automatically, stops one unit when meets whitespace
        output.push_back(value);
    }

    return output;
}

void print_vec(const Vector& vec) { //Pass by reference the vector vec
    for (size_t i = 0; i < vec.size(); i++) printf("[%zu] = %lf\n", i, vec[i]);
}
