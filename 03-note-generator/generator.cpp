#include <format>
#include <iostream>
#include <string>

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void sound();
void melody();
void visualize();

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::string input = "";
    std::cout << "Welcome to the Note Generator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Synthesize single tone
[2] Play algorithmic melody
[3] View waveform visualization
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
        sound();
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

// [1] synthesize single tone
void sound() {
    std::cout << "Sound generator mode selected.\n";
}

// [2] play algorithmic melody
void melody() {
    std::cout << "Melody generator mode selected.\n";
}

// [3] view waveform visualization
void visualize() {
    std::cout << "Visualization mode selected.\n";
}