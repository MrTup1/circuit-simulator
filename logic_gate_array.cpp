#include <vector>
#include <iterator>
#include <fstream> 
#include <iostream>
#include <stdio.h>

#include "logic_gate_array.hpp"



bool Logic::load_board_from_file(const std::string&filename, char connection) {
    std::string line;
    std::ifstream inFile;
    std::vector<std::vector<bool>>* target_array = nullptr;
    inFile.open(filename);

    // The check is from read.cpp, modified to return false instead of exiting
    if (!inFile) {
        std::cout << "Unable to open file, using default inputs." << std::endl;
        return false;
    }

    // Check if file is for and gates or or gates
    if (connection == 'a') {
        target_array = &and_array; //& represents pointer, so the code below modifies original
    } else if (connection == 'o') {
        target_array = &or_array;
    } else {
        return false;
    }

    target_array -> clear();

    while (std::getline(inFile, line)) {
        std::vector<bool> currentRow;

        if (line.empty()) {
            continue;
        }

        for (char c : line) {
            if (isdigit(c)) {
                currentRow.push_back(c -'0');
            }
        }

        target_array->push_back(currentRow);
    }
    
    return true;
};

bool Logic::print_array() {
    for (const auto& row : and_outputs) {
        std::cout << row << " "; 
        std::cout << std::endl;
    }

    return true;
};

void Logic::generate_and() {
    for (const auto& row : and_array) {
        int i = 0;
        std::string gateOutput;
        for (bool val : row) {
            if (val == 1) {
                gateOutput.append(input_labels[i]);
            }
            i += 1;
        }
        and_outputs.push_back(gateOutput);
    }
}

void Logic::generate_or() {
    or_outputs.clear();
    if (or_array.empty()) return;
    size_t num_outputs = or_array[0].size();

    for (int column = 0; column < num_outputs; ++column) {
        std::string current_expression = "";
        for(int row = 0; row < or_array.size(); ++row) {
            if (or_array[row][column] && !and_outputs[row].empty()) {
                if (!current_expression.empty() ) {
                    current_expression += " + ";
                }
                current_expression += and_outputs[row];
            }
        }
        or_outputs.push_back(current_expression);
    }
}

void Logic::print_outputs() {
    for (int i = 0; i < or_outputs.size(); ++i) {
        if (!or_outputs[i].empty()) {
            std::cout << output_labels[i] << ": " << or_outputs[i];
            std::cout << std::endl;
        }
    }
}


/*int main() {
    Logic logicClass;
    logicClass.load_board_from_file("and.txt", 'a');
    logicClass.load_board_from_file("or.txt", 'o');
    logicClass.generate_and();
    logicClass.generate_or();
    logicClass.print_outputs();
}*/