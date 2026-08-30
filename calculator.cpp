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

// [1] convert given note to its corresponding frequency based on its semitone distance from A4
void convertNote() {
    std::string nIn = ""; // semitones above A4
    std::cout << "Semitone distance from A4 (ex. + 3 = C5, - 4 = F4): "; // the note C5 is 3 half-steps above A4 (reference note), F4 is 4 half-steps below A4
    std::cin >> nIn;
    std::stringstream nStream(nIn); // store input nIn into stream nStream
    std::string nTemp; // stores temp char from nStream
    while (std::getline(nStream, nTemp, ' ')) { // getline(input_stream, store_str, delim) [delim is optional, default is '\n']
        std::cout << nTemp << std::endl;
    }
    // f = 440 * 2^(n-69)/12 (69 = MIDI note # for A4, n = semitones above A4)
}

// [2] calculate durations of various note values given BPM + beats per measure
void calcDurations() {
    std::cout << "Calculate durations mode selected.\n";
}

// [3] analyze average error of given metronome offsets
void analyzeRhythm() {
    std::cout << "Analyze rhythm mode selected.\n";
}