// Standard library headers
#include <format>
#include <iostream>
#include <string>

// Func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void convertNote();
void calcDurations();
void analyzeRhythm();

// Display menu options
int main() {
    std::string input = "";
    std::cout << "Welcome to the Music Calculator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Convert note to frequency
[2] Calculate note durations
[3] Analyze metronome consistency
[4] Exit
Selected option: )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "Thank you for using the Music Calculator!\n";
    return 0;
}

// Execute selected menu option based on input
void handleMenu(std::string input) {
    if (input == "1") {
        convertNote();
    } else if (input == "2") {
        calcDurations();
    } else if (input == "3") {
        analyzeRhythm();
    } else {
        std::cout << "Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// Convert given note name to its corresponding frequency
void convertNote() {
    std::cout << "Convert note mode selected.\n";
}

// Calculate durations of various note values given BPM + beats per measure
void calcDurations() {
    std::cout << "Calculate durations mode selected.\n";
}

// Analyze average error of given metronome offsets
void analyzeRhythm() {
    std::cout << "Analyze rhythm mode selected.\n";
}