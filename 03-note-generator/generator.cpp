// standard library headers
#include <cmath>
#include <format>
#include <iostream>
#include <string>

// custom header files
#define MINIAUDIO_IMPLEMENTATION // preprocessor directive: creates macro (finds + replaces text in source code before compilation starts; this line can only be in one cpp file, need to define BEFORE including miniaudio.h)
#include "miniaudio.h" // miniaudio source (external library for audio playback): https://github.com/mackron/miniaudio

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void note();
void melody();
void visualize();

// WIP => define base class to store attributes + methods for all oscillators
class Oscillator {
    private:
        double frequency;
        double amplitude;
    public:
        virtual double getY(double time) = 0; // = 0 makes it a pure virtual func (forces derived classes to implement func, turns class into abstract class / interface, cannot create instance of Oscillator directly)
        virtual ~Oscillator() = default; // standard virtual destructor (~): required for classes w/ virtual func
}; // need semicolon b/c class definition treated as declaration statement (can declare object / instance of class immediately after closing bracket)

// WIP => define base class to store attributes + methods for sine oscillators (smooth)
class SineOscillator : public Oscillator {
    public:
        double getY(double time) override {
        }
};

// WIP => define base class to store attributes + methods for square oscillators (flat top + bottom)
class SquareOscillator : public Oscillator {
    public:
        double getY(double time) override {
        }
};

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