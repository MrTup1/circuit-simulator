#pragma once

#include <vector>

using Vector = std::vector<double>; //type alias

Vector create_vector(std::size_t size);
std::vector<double> load_vec_from_file(const char* filename);
void print_vec(const std::vector<double>& vec);

/*class Vector {
    std::vector<double> element;

    public:
    Vector(size_t size);
    double operator[](size_t index);
};*/