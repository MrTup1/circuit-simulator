#include <iostream>
#include <menu.hpp>
#include <circuit.hpp>


void display_welcome() {
    std::cout << "\x1b[1m" << "\nSIMULATOR X, ENTER ONE CHARACTER TO CHOOSE A SIMULATOR TO RUN\n" << "\x1b[0m" << "-> c for circuit simulator\n-> f for fourier graph plotter\n-> l for logic analyser\n";
}

std::string get_filename(std::string file_type) {
    std::string filename;
    std::cout << "Input " << file_type << " filename: ";
    std::getline(std::cin, filename);
    filename = "../data/" + filename;
    return filename;
}


void run_circuit_simulator(){
    std::string f = get_filename("circuit simulator");
};

void run_fourier();
void run_logic() {
    std::string and_path = get_filename("AND");
    std::string or_path = get_filename("OR");
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
            }
        }
    }

    return 0;
}