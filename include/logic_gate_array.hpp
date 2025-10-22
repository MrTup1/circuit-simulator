#pragma once

#include <vector>
#include <iterator>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <string>

class Logic {
    private:
        std::vector<std::vector<bool>> and_array;
        std::vector<std::vector<bool>> or_array;
        std::vector<std::string> input_labels = {"A'", "A", "B'", "B", "C'", "C"};
        std::vector<std::string> output_labels = {"x", "y", "z"}; 
        std::vector<std::string> and_outputs = {};
        std::vector<std::string> or_outputs = {};
    public:
        bool load_board_from_file(const std::string&filename, char connection);
        bool print_array();
        void generate_and();
        void generate_or();
        void print_outputs();


};