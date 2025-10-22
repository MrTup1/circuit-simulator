#include <iostream>
#include <cstdlib>
#include "circuit.hpp"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        Circuit c(argv[1]);
        c.analyse();
    } else {
        std::cout << "Syntax: " << argv[0] << " <filename>" << std::endl;
    }
    
    return EXIT_SUCCESS;
}