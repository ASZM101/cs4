// standard library headers
#include <cmath>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void convertNote();
void calcDurations();
void analyzeRhythm();

// display menu options [=> used for outputs, (!) used for errors]
int main() {
    std::string input = "";
    std::cout << "Welcome to the Music Calculator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Convert note to frequency
[2] Calculate note durations (milliseconds)
[3] Analyze metronome consistency
[4] Exit
Enter selected option (ie. 1, 2, 3, 4): )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "=> Thank you for using the Music Calculator!\n";
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
    } else if (input == "4") {
        return;
    } else {
        std::cout << "(!) Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// [1] convert given note to its corresponding frequency based on its semitone distance from A4 (reference note)
// check converted frequencies: https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies (MIDI note number for A4 is 69)
void convertNote() {
    std::string distance = ""; // semitones above/below A4
    int n = 0; // value used in calculation
    std::string errorMsg = "(!) Please type the semitone distance from A4 in the following format: sign (+ for above A4, - for below A4) immediately followed by the number of half steps from A4 (no spaces in between)."; // error msg displayed after invalid input
    bool error = false;
    while (distance.length() < 1 || error) { // ensure at least 1 char is provided (num w/o sign = positive)
        std::cout << "Enter semitone distance from A4 (ex. +3 for C5, -4 for F4): "; // the note C5 is 3 half steps above A4, F4 is 4 half steps below A4
        std::cin >> distance;
        if (distance.length() < 1) {
            std::cout << std::format("{}\n", errorMsg);
        } else {
            std::stringstream convert(distance);
            if (convert >> n) { // try to convert str from stream to int (including sign)
                error = false;
                std::cout << std::format("=> Distance: {}{} semitones | Converted frequency: {:.2f} Hz\n", n > 0 ? "+" : "-", std::abs(n), (440 * std::pow(2, n / 12.0))); // f = 440 * 2^(n / 12.0) (n = semitones above A4; must have double in division to get double for answer)
            } else {
                error = true;
                std::cout << std::format("{}\n", errorMsg);
            }
        }
    }
}

// [2] calculate durations of various note values given beats per measure + beats per measure
void calcDurations() {
    std::string input = "";
    int tempo = 0; // beats per minute (# on metronome)
    int beats = 0; // # of beats in one measure (top # in time signature)
    std::string errorMsg = "(!) Please only type a positive integer."; // error msg displayed after invalid input
    bool error = false;
    while (input.length() < 1 || error) { // get input for beats per minute (tempo)
        std::cout << "Enter beats per minute (ex. 120): ";
        std::cin >> input;
        std::stringstream convert(input);
        if (convert >> tempo && tempo > 0) { // try to convert str from stream to int, ensure input is positive
            error = false;
        } else {
            error = true;
            std::cout << std::format("{}\n", errorMsg);
        }
    }
    input = ""; // reset input for next while loop
    while (input.length() < 1 || error) { // get input for beats per measure (beats)
        std::cout << "Enter beats (quarter notes) per measure (ex. 4): ";
        std::cin >> input;
        std::stringstream convert(input);
        if (convert >> beats && beats > 0) { // try to convert str from stream to int, ensure input is positive
            error = false;
        } else {
            error = true;
            std::cout << std::format("{}\n", errorMsg);
        }
    }
    int msPerMin = 60000.0; // milliseconds per minute
    std::cout << std::format("=> Duration of sixteenth note: {} ms\n", std::round((msPerMin / tempo / 4.0)));
    std::cout << std::format("=> Duration of eighth note: {} ms\n", std::round((msPerMin / tempo / 2.0)));
    std::cout << std::format("=> Duration of quarter note: {} ms\n", std::round((msPerMin / tempo)));
    std::cout << std::format("=> Duration of half note: {} ms\n", std::round((msPerMin / tempo * 2.0)));
    std::cout << std::format("=> Duration of full measure: {} ms\n", std::round((msPerMin / tempo * beats)));
}

// [3] analyze average error of given metronome offsets
void analyzeRhythm() {
    std::string input = "";
    int totalReps = 0; // # of metronome practice reps
    std::vector<double> reps; // log of millisecond timing deviations from metronome click
    std::string errorMsg = ""; // error msg displayed after invalid input
    bool error = false;
    while (input.length() < 1 || error) { // get input for # of metronome practice reps (totalReps)
        std::cout << "Enter the number of practice reps you want to log: ";
        std::cin >> input;
        std::stringstream convert(input);
        if (convert >> totalReps && totalReps > 0) { // try to convert str from stream to int, ensure input is positive
            error = false;
        } else {
            error = true;
            std::cout << "(!) Please only type a positive integer.\n";
        }
    }
    for (int i = 0; i < totalReps; ++i) { // get input for each timing deviation (rep in reps); ++i (pre-increment) is generally best practice (more memory-efficient for objects, no difference for integers)
        input = ""; // reset input for next while loop
        while (input.length() < 1 || error) {
            std::cout << std::format("{}. Enter timing deviation in milliseconds (ex. +4 for 4 ms late, -15 for 15 ms early): ", (i + 1));
            std::cin >> input;
            std::stringstream convert(input);
            int temp = 0;
            if (convert >> temp) { // try to convert str from stream to int
                error = false;
                reps.push_back(temp);
            } else {
                error = true;
                std::cout << "(!) Please type the timing deviations in the following format: sign (+ for too late, - for too early) immediately followed by the milliseconds deviated from the metronome click (no spaces in between).\n";
            }
        }
    }
    for (double rep : reps) { // (testing) print each rep in vector
        std::cout << rep << "\n";
    }
}