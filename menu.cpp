#include <iostream>
#include "menu.hpp"
#include "circuit.hpp"
#include "logic_gate_array.hpp"
#include "graph_plotter.hpp"


void display_welcome() {
    std::cout << "\x1b[1m" << "\nSIMULATOR X, ENTER ONE CHARACTER TO CHOOSE A SIMULATOR TO RUN\n" << "\x1b[0m" << "-> c for circuit simulator\n-> f for fourier graph plotter\n-> l for logic analyser\n-> q for quit\n";
}

std::string get_filename(std::string file_type) {
    std::string filename;
    std::cout << "Input " << file_type << " filename: ";
    std::getline(std::cin, filename);
    filename = "data/" + filename;
    return filename;
}


void run_circuit_simulator(){
    std::string f = get_filename("circuit simulator");
};

void run_fourier(){
    Fourier graph;
    graph.getUserInput();
    graph.plotGraph();

    // ADD THESE TWO LINES to clear the leftover newline from getUserInput() leaving a newline 
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};


void run_logic() {
    std::string and_path = get_filename("AND");
    std::string or_path = get_filename("OR");
    Logic logicClass;
    
    // Load the files
    bool and_loaded = logicClass.load_board_from_file(and_path, 'a');
    bool or_loaded = logicClass.load_board_from_file(or_path, 'o');

    // Only proceed if files were loaded successfully
    if (and_loaded && or_loaded) {
        logicClass.generate_and();
        logicClass.generate_or();
        logicClass.print_outputs();
    } else {
        std::cout << "Error loading one or more files. Cannot run logic." << std::endl;
    }
};

int main(int argc, char* argv[]) {
    while (true) {
        display_welcome();

        std::string input;
        std::getline(std::cin, input);

        if (input.size() == 1) {
            char c = input.at(0);

            switch (c) {
                case 'c':  // circuit simulator
                    run_circuit_simulator();
                    break;
                case 'f':
                    run_fourier();
                    break;
                case 'l':
                    run_logic();
                    break;
                case 'q':
                    return 0;
            }
        }
    }

    return 0;
}