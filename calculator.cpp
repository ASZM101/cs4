// standard library headers
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
void convertNote() {
    std::string distance = ""; // semitones above/below A4
    std::string sign = ""; // "+" = above A4, "-" = below A4
    int n = 0; // value used in calculation
    std::string errorMsg = "Please type the semitone distance from A4 in the following format: sign (+ for above A4, - for below A4) immediately followed by the number of half steps from A4 (no spaces in between)."; // error msg displayed after invalid input
    bool error = false;
    while (distance.length() < 2 || error) { // ensure at least 2 chars are provided (sign + num, though num could be > 1 digit)
        std::cout << "Semitone distance from A4 (ex. +3 for C5, -4 for F4): "; // the note C5 is 3 half steps above A4, F4 is 4 half steps below A4
        std::cin >> distance;
        if (distance.length() < 2) {
            std::cout << std::format("{}\n", errorMsg);
        } else {
            sign = distance.at(0); // extract sign from input
            std::stringstream convert(distance.substr(1, distance.length() - 1)); // substr(index_1st_char, substr_len) [includes 1st char at given index]
            if (convert >> n) { // try to convert str from stream to int
                std::cout << std::format("Success: {} + {} = {}\n", n, 1, (n+1));
                error = false;
            } else {
                std::cout << std::format("{}\n", errorMsg);
                error = true;
            }
            // f = 440 * 2^(n-69)/12 (69 = MIDI note # for A4, n = semitones above A4)
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