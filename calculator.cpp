// standard library headers
#include <cmath>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void convertNote();
void calcDurations();
void analyzeRhythm();

// display menu options
int main() {
    std::string input = "";
    std::cout << "Welcome to the Music Calculator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Convert note to frequency
[2] Calculate note durations
[3] Analyze metronome consistency
[4] Exit
Selected option (ie. 1, 2, 3, 4): )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "Thank you for using the Music Calculator!\n";
    return 0;
}

// execute selected menu option based on input
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

// [1] convert given note to its corresponding frequency based on its semitone distance from A4 (reference note)
// check converted frequencies: https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies (MIDI note number for A4 is 69)
void convertNote() {
    std::string distance = ""; // semitones above/below A4
    int n = 0; // value used in calculation
    std::string errorMsg = "Please type the semitone distance from A4 in the following format: sign (+ for above A4, - for below A4) immediately followed by the number of half steps from A4 (no spaces in between)."; // error msg displayed after invalid input
    bool error = false;
    while (distance.length() < 2 || error) { // ensure at least 2 chars are provided (sign + num, though num could be > 1 digit)
        std::cout << "Semitone distance from A4 (ex. +3 for C5, -4 for F4): "; // the note C5 is 3 half steps above A4, F4 is 4 half steps below A4
        std::cin >> distance;
        if (distance.length() < 2) {
            std::cout << std::format("{}\n", errorMsg);
        } else {
            std::stringstream convert(distance);
            if (convert >> n) { // try to convert str from stream to int (including sign)
                error = false;
                std::cout << std::format("Distance: {} semitones | Converted frequency: {:.2f} Hz\n", distance, (440 * std::pow(2, n / 12.0))); // f = 440 * 2^(n / 12.0) (n = semitones above A4; must have double in division to get double for answer)
            } else {
                error = true;
                std::cout << std::format("{}\n", errorMsg);
            }
        }
    }
}

// [2] calculate durations of various note values given BPM + beats per measure
void calcDurations() {
    std::cout << "Calculate durations mode selected.\n";
}

// [3] analyze average error of given metronome offsets
void analyzeRhythm() {
    std::cout << "Analyze rhythm mode selected.\n";
}