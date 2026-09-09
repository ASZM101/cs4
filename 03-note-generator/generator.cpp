#include <cmath>
#include <chrono>
#include <format>
#include <iostream>
#include <string>

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void note();
void melody();
void visualize();

// WIP => define base class to store attributes + methods for all oscillators
class Oscillator {
};

// WIP => define base class to store attributes + methods for sine oscillators (smooth)

// WIP => define base class to store attributes + methods for square oscillators (flat top + bottom)

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::string input = "";
    std::cout << "Welcome to the Note Generator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Play single note
[2] Generate algorithmic melody
[3] View soundwave visualization
[4] Exit
Enter selected option (ie. 1, 2, 3, 4): )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "=> Thank you for using the Note Generator!\n";
    return 0;
}

// execute selected menu option based on input
void handleMenu(std::string input) {
    if (input == "1") {
        note();
    } else if (input == "2") {
        melody();
    } else if (input == "3") {
        visualize();
    } else if (input == "4") {
        return;
    } else {
        std::cout << "(!) Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// WIP => [1] play note through audio output (given wave type + frequency + duration, use external library for audio playback)
void note() {
    std::cout << "Note generator mode selected.\n";
}

// WIP => [2] play melody through audio output (given root note, use math functions + nested loops for creating sequence of notes, use external library for audio playback)
void melody() {
    std::cout << "Melody generator mode selected.\n";
}

// WIP => [3] view soundwave visualization (given wave type + frequency, use ASCII amplitude plot)
void visualize() {
    std::cout << "Visualization mode selected.\n";
}