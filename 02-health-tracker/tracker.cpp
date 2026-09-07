// standard library headers
#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

// define structure to return numerical score + qualitative analysis in score funcs
struct Score {
    int num;
    std::string analysis;
};  // need semicolon b/c struct definition treated as declaration statement (can declare instance of struct immediately after closing bracket)

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
        bool getMedTaken() {
            return medTaken;
        }
        Score scoreHeartRate() { // normal resting heart rate for adults: 60-100 BPM (https://my.clevelandclinic.org/health/diagnostics/heart-rate) (maybe allow user to input additional factors in future, like age / exercise?)
            if (heartRate >= 60 && heartRate <= 80) {
                return {35, "healthy"};
            } else if (heartRate >= 81 && heartRate <= 100) {
                return {25, "slightly elevated"};
            } else if (heartRate >= 50 && heartRate <= 59) {
                return {25, "low"};
            } else if (heartRate < 50) {
                return {10, "very low"};
            } else { // above 100
                return {10, "very high"};
            }
        }
        Score scoreSteps() { // recommended goal for adults: 10,000 (https://www.nih.gov/news-events/nih-research-matters/number-steps-day-more-important-step-intensity) (maybe allow user to input their own goal in future?)
            if (steps >= 10000) {
                return {35, "highly active"};
            } else if (steps >= 7500 && steps <= 9999) {
                return {25, "moderately active"};
            } else if (steps >= 5000 && steps <=7499) {
                return {15, "slightly active"};
            } else { // under 5,000
                return {5, "mostly inactive"};
            }
        }
        Score scoreMedTaken() { // maybe allow user to specify whether they take medication in future?
            if (medTaken) {
                return {30, "taken or not applicable"};
            } else {
                return {0, "missed"};
            }
        }
        Score scoreOverall() {
            int score = scoreHeartRate().num + scoreSteps().num + scoreMedTaken().num;
            if (score >= 90) {
                return {score, "excellent"};
            } else if (score >= 75 && score <= 89) {
                return {score, "good"};
            } else if (score >= 60 && score <= 74) {
                return {score, "fair"};
            } else {
                return {score, "needs improvement"};
            }
        }
        std::string getSummary() { // return inputted vitals and calculate overall score (heartRate is worth 35 points, steps is worth 35 points, medTaken is worth 30 points)
            auto utc = std::chrono::system_clock::now(); // get precise date and time in UTC (auto: compiler automatically detects var data type)
            auto localTime = std::chrono::current_zone()->to_local(utc); // find active time zone in computer's OS, convert UTC time to local time (-> accesses method of pointer returned by current_zone; pointer stores memory address of other var)
            std::string summary = std::format("\n=== {:%B %d, %Y @ %I:%M %p} [{}] ===\n", localTime, username); // need to start with : when formatting date / time within brackets
            std::unordered_map<std::string, Score> scores = {
                {"heartRate", scoreHeartRate()},
                {"steps", scoreSteps()},
                {"medTaken", scoreMedTaken()},
                {"overall", scoreOverall()}
            };
            summary += std::format("Resting heart rate: {} BPM ({} +{} pts)\n", heartRate, scores.at("heartRate").analysis, scores.at("heartRate").num);
            summary += std::format("Step count: {} ({} +{} pts)\n", steps, scores.at("steps").analysis, scores.at("steps").num);
            summary += std::format("Medication status: {} (+{} pts)\n", scores.at("medTaken").analysis, scores.at("medTaken").num);
            summary += std::format("Overall health score: {}/100 ({})\n", scores.at("overall").num, scores.at("overall").analysis);
            return summary;
        }
}; // need semicolon b/c class definition treated as declaration statement (can declare object / instance of class immediately after closing bracket)

// func declarations (both actual def AND prototype MUST match; pass patients to all funcs)
void handleMenu(std::string input, std::unordered_map<std::string, DailyVitals> &patients);
std::string promptUsername(std::unordered_map<std::string, DailyVitals> &patients);
DailyVitals record(std::unordered_map<std::string, DailyVitals> &patients);
void evaluate(std::unordered_map<std::string, DailyVitals> &patients);
void save(std::unordered_map<std::string, DailyVitals> &patients);

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::unordered_map<std::string, DailyVitals> patients;
    std::string input = "";
    std::cout << "Welcome to the Health Tracker!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Record today's vitals
[2] Evaluate today's vitals (must record first)
[3] Save today's summary in log (must record first)
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
void handleMenu(std::string input, std::unordered_map<std::string, DailyVitals> &patients) {
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

// prompt user to enter existing username (if no recorded vitals, call record func or return to menu)
std::string promptUsername(std::unordered_map<std::string, DailyVitals> &patients) {
    std::string input = "";
    std::string username = "";
    std::cout << "Enter patient username (only for existing users): ";
    std::cin >> username;
    if (!patients.contains(username)) // check if user has recorded vitals yet
    {
        std::cout << "(!) It seems like you have not recorded your vitals for today yet.\n";
        while (input != "y" && input != "n") { // prompt user to record vitals
            std::cout << "Would you like to record today's vitals first? (y/n): ";
            std::cin >> input;
            if (input != "y" && input != "n") { // ensure user only enters y or n
                std::cout << "(!) Please only type y (to record vitals) or n (to return to the main menu).\n";
            }
        }
        return (input == "y") ? record(patients).getUsername() : ""; // y = call record func, n = return to main menu
    } else {
        return username;
    }
}

// [1] record given health vitals (ask for input, store in vars, return patient)
DailyVitals record(std::unordered_map<std::string, DailyVitals> &patients) {
    std::string input = "";
    std::string username = "";
    int heartRate = 0;
    int steps = 0;
    bool medTaken = false;
    std::string errorInt = "(!) Please only type a positive integer."; // error msg displayed after invalid input for int
    std::string errorBool = "(!) Please only type either 1 (medication taken or not applicable) or 0 (medication missed)."; // error msg displayed after invalid input for bool
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
    patients.insert_or_assign(username, DailyVitals(username, heartRate, steps, medTaken)); // add new patient to unordered map, update existing patient if already recorded vitals (as opposed to insert method, which does not insert / update item if already exists)
    std::cout << std::format("=> Vitals successfully recorded for {}.\n", username);
    return patients.at(username);
}

// [2] evaluate given health vitals (compare stored vars to pre-defined thresholds, output health scores)
void evaluate(std::unordered_map<std::string, DailyVitals> &patients) {
    std::string username = promptUsername(patients);
    if (username == "") {
        return; // return to main menu
    }
    DailyVitals patient = patients.at(username);
    std::cout << patient.getSummary();
}

// [3] save evaluation summary in log (append formatted values to log file, create log file if doesn't exist yet)
void save(std::unordered_map<std::string, DailyVitals> &patients) {
    std::string username = promptUsername(patients);
    if (username == "") {
        return; // return to main menu
    }
    DailyVitals patient = patients.at(username);
    // WIP => export summary
    std::cout << std::format("=> Resting heart rate: {}\n", patient.getHeartRate());
    std::cout << std::format("=> Step count: {}\n", patient.getSteps());
    std::cout << std::format("=> Medication status: {}\n", patient.getMedTaken());
}