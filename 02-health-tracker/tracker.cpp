// standard library headers
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// func declarations (both actual def AND prototype MUST match; pass patients vector to all funcs)
void handleMenu(std::string input, std::vector<DailyVitals> &patients);
void record(std::vector<DailyVitals> &patients);
void evaluate(std::vector<DailyVitals> &patients);
void save(std::vector<DailyVitals> &patients);

// define class to store attributes and methods dealing with daily vitals
class DailyVitals {
    private:
        std::string username;
        int heartRate;
        int steps;
        bool medTaken;
    public:
        DailyVitals(std::string un, int hr, int s, bool mt) {
            username = un;
            heartRate = hr;
            steps = s;
            medTaken = mt;
        }
        std::string getUsername() {
            return username;
        }
        int getHeartRate() {
            return heartRate;
        }
        int getSteps() {
            return steps;
        }
        int getMedTaken() {
            return medTaken;
        }
        int compareHeartRate() { // normal resting heart rate for adults: 60-100 BPM (https://my.clevelandclinic.org/health/diagnostics/heart-rate) (maybe allow user to input additional factors in future, like age / exercise)
            if (heartRate < 60) {
                return -1; // below threshold
            }
            else if (heartRate >= 60 && heartRate <= 100) {
                return 0; // within threshold
            }
            else {
                return 1; // above threshold
            }
        }
        int compareSteps() { // recommended goal for adults: 10,000 (https://www.nih.gov/news-events/nih-research-matters/number-steps-day-more-important-step-intensity) (maybe allow user to input their own goal in future)
            if (steps < 10000) {
                return -1; // did not meet goal
            }
            else if (steps == 10000) {
                return 0; // met goal
            }
            else {
                return 1; // exceeded goal
            }
        }
}; // need semicolon b/c class definition treated as declaration statement

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::vector<DailyVitals> patients;
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
        handleMenu(input, patients);
    }
    std::cout << "=> Thank you for using the Health Tracker!\n";
    return 0;
}

// execute selected menu option based on input
void handleMenu(std::string input, std::vector<DailyVitals> &patients) {
    if (input == "1") {
        record(patients);
    } else if (input == "2") {
        evaluate(patients);
    } else if (input == "3") {
        save(patients);
    } else if (input == "4") {
        return;
    } else {
        std::cout << "(!) Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// [1] record given health vitals (ask for input, store in vars)
void record(std::vector<DailyVitals> &patients) {
    std::string input = "";
    std::string username = "";
    int heartRate = 0;
    int steps = 0;
    bool medTaken = false;
    std::string errorInt = "(!) Please only type a positive integer."; // error msg displayed after invalid input for int
    std::string errorBool = "(!) Please only type either 1 (medication taken or not applicable) or 0 (medication not taken)."; // error msg displayed after invalid input for bool
    bool error = false;
    std::cout << "Enter patient username (create username for new users, type existing username for returning users): ";
    std::cin >> username;
    while (input.length() < 1 || error) { // get input for resting heart rate
        std::cout << "Enter resting heart rate (BPM): ";
        std::cin >> input;
        std::stringstream convert(input);
        if (convert >> heartRate && heartRate > 0) { // try to convert str from stream to int, ensure input is positive
            error = false;
        } else {
            error = true;
            std::cout << std::format("{}\n", errorInt);
        }
    }
    input = ""; // reset input for next while loop
    while (input.length() < 1 || error) { // get input for step count
        std::cout << "Enter step count: ";
        std::cin >> input;
        std::stringstream convert(input);
        if (convert >> steps && steps > 0) { // try to convert str from stream to int, ensure input is positive
            error = false;
        } else {
            error = true;
            std::cout << std::format("{}\n", errorInt);
        }
    }
    input = ""; // reset input for next while loop
    while (input.length() < 1 || error) { // get input for medication status
        std::cout << "Enter medication status (1 = taken or not applicable, 0 = missed): ";
        std::cin >> input;
        if (input == "1" || input == "0") { // ensure input is either 1 or 0
            error = false;
            medTaken = input == "1" ? true : false;
        } else {
            error = true;
            std::cout << std::format("{}\n", errorBool);
        }
    }
    std::cout << std::format("=> Username: {}\n", username);
    std::cout << std::format("=> Resting heart rate: {}\n", heartRate);
    std::cout << std::format("=> Step count: {}\n", steps);
    std::cout << std::format("=> Medication status: {}\n", medTaken);
}

// [2] evaluate given health vitals (compare stored vars to pre-defined thresholds, output health scores / ratings)
void evaluate(std::vector<DailyVitals> &patients) {
    std::string input = "";
    std::string username = "";
    int heartRate = 0;
    int steps = 0;
    bool medTaken = false;
    std::string errorInt = "(!) Please only type a positive integer."; // error msg displayed after invalid input for int
    std::string errorBool = "(!) Please only type either 1 (medication taken or not applicable) or 0 (medication not taken)."; // error msg displayed after invalid input for bool
    bool error = false;
    std::cout << "Enter patient username (only for returning users): ";
    std::cin >> username;
    // username not found: ask user if they would like to create account and record today's vitals, call record func
    // vitals not recorded: ask user if they would like to record today's vitals, call record func
}

// [3] save evaluation summary in log (append formatted values to log file, create log file if doesn't exist yet)
void save(std::vector<DailyVitals> &patients) {
    std::string input = "";
    std::string username = "";
    int heartRate = 0;
    int steps = 0;
    bool medTaken = false;
    std::string errorInt = "(!) Please only type a positive integer."; // error msg displayed after invalid input for int
    std::string errorBool = "(!) Please only type either 1 (medication taken or not applicable) or 0 (medication not taken)."; // error msg displayed after invalid input for bool
    bool error = false;
    std::cout << "Enter patient username (only for returning users): ";
    std::cin >> username;
    // username not found: ask user if they would like to create account and record today's vitals, call record func
    // vitals not recorded: ask user if they would like to record today's vitals, call record func
}