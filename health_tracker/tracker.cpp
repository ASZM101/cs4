// standard library headers
#include <format>
#include <iostream>
#include <string>

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void record();
void evaluate();
void save();

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::string input = "";
    std::cout << "Welcome to the Health Tracker!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Record today's vitals
[2] Evaluate today's vitals
[3] Save today's summary in log
[4] Exit
Enter selected option (ie. 1, 2, 3, 4): )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "=> Thank you for using the Health Tracker!\n";
    return 0;
}

// execute selected menu option based on input
void handleMenu(std::string input) {
    if (input == "1") {
        record();
    } else if (input == "2") {
        evaluate();
    } else if (input == "3") {
        save();
    } else if (input == "4") {
        return;
    } else {
        std::cout << "(!) Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// [1] record given health vitals (ask for input, store in vars)
void record() {
    std::cout << "Record mode selected.\n";
}

// [2] evaluate given health vitals (compare stored vars to pre-defined thresholds, output health scores / ratings)
void evaluate() {
    std::cout << "Evaluate mode selected.\n";
}

// [3] save evaluation summary in log (append formatted values to log file, create log file if doesn't exist yet)
void save() {
    std::cout << "Save mode selected.\n";
}