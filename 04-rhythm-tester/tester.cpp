// g++ -std=c++23 tester.cpp lesson.cpp analytics.cpp practice_engine.cpp -o tester
// ./tester
// WIP => maybe update runcpp to accept as many files as given?

// standard library headers
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// custom header files
#include "analytics.hpp"
#include "lesson.hpp"
#include "practice_engine.hpp"
// snake_case is more common for open-source / cross-platform programs, also standard for Google C++ Style Guide: https://google.github.io/styleguide/cppguide.html

// func declarations (both actual def AND prototype MUST match)
std::vector<std::unique_ptr<Lesson>> loadLessons(const std::string& filepath);
void handleMenu(std::string input, std::vector<std::unique_ptr<Lesson>>& lessons); // lessons must be reference b/c unique_ptr cannot be copied

// display exercise options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::vector<std::unique_ptr<Lesson>> lessons = loadLessons("lessons.csv");
    std::string input = "";
    std::cout << "Welcome to the Rhythm Tester!\n";
    while (input != std::to_string(lessons.size() + 1)) {
        std::cout << "\nChoose one of the following options:\n";
        for (size_t i = 0; i < lessons.size(); ++i) {
            std::cout << std::format("[{}] Exercise: {} ({} BPM)\n", (i + 1), lessons[i]->getTitle(), lessons[i]->getBpm()); // exercise #, title, bpm
        }
        std::cout << std::format("[{}] Exit\n", (lessons.size() + 1));
        std::cout << "Enter selected option: ";
        std::cin >> input;
        handleMenu(input, lessons);
    }
    std::cout << "=> Thank you for using the Rhythm Tester!\n";
    return 0;
}

// parse lessons csv
std::vector<std::unique_ptr<Lesson>> loadLessons(const std::string& filepath) {
    std::vector<std::unique_ptr<Lesson>> lessons; // store lesson objects
    std::ifstream file(filepath);
    if (!file.is_open()) { // check if file failed to open from disk
        std::cerr << std::format("(!) Could not open {}. Loading default fallback exercises.\n", filepath);
        lessons.push_back(std::make_unique<Lesson>("Quarter Note Rhythm Stability", 120, 4)); // default fallback exercise 1
        lessons.push_back(std::make_unique<Lesson>("Syncopation Timing Test", 90, 4)); // default fallback exercise 2
        return lessons;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) { // skip empty file lines
            continue;
        }
        std::stringstream ss(line); // wrap inside stringstream for splitting
        std::string titleStr, bpmStr, beatsStr;
        if (std::getline(ss, titleStr, ',') && std::getline(ss, bpmStr, ',') && std::getline(ss, beatsStr, ',')) { // parse up to comma separator
            int bpm = std::stoi(bpmStr); // convert str to int
            int beats = std::stoi(beatsStr);
            lessons.push_back(std::make_unique<Lesson>(titleStr, bpm, beats)); // lesson instance wrapped in unique pointer
        }
    }
    file.close();
    return lessons;
}

// handle selected menu option based on input
void handleMenu(std::string input, std::vector<std::unique_ptr<Lesson>>& lessons) {
    int choice = 0;
    std::string flushBuffer;
    std::getline(std::cin, flushBuffer); // clear remaining input stream
    std::string errorInt = std::format("(!) Please only type a positive integer between 1 and {} (inclusive) to select an exercise.\n", (lessons.size() + 1));
    std::stringstream ss(input);
    if (ss >> choice) { // try to convert str from stream to int
        if (choice == lessons.size() + 1) { // exit option selected
            return;
        } else if (choice < 1 || choice > lessons.size()) {
            std::cout << errorInt;
            return;
        }
    } else { // invalid exercise selection
        std::cout << errorInt;
        return;
    }
    const Lesson& selectedLesson = *lessons[choice - 1]; // dereference unique pointer to lesson reference (access actual value at memory address)
    std::vector<double> errors = PracticeEngine::runTest(selectedLesson);
    double meanError = Analytics::calcError(errors); // mean absolute error
    std::vector<double> sortedDeviations = Analytics::sortDeviations(errors);
    std::string feedback = Analytics::feedback(meanError);
    std::cout << "=> Raw timing errors: [";
    for (size_t i = 0; i < errors.size(); ++i) {
        std::cout << (errors[i] >= 0 ? "+" : "") << static_cast<int>(errors[i]) << " ms"; // signed millisecond error value
        if (i + 1 < errors.size()) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "=> Sorted deviations: [";
    for (size_t i = 0; i < sortedDeviations.size(); ++i) {
        std::cout << static_cast<int>(sortedDeviations[i]) << " ms";
        if (i + 1 < sortedDeviations.size()) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << std::format("=> Mean absolute error:  {:.2f} ms\n", meanError);
    std::cout << std::format("=> Consistency variance: {}\n", (meanError < 500 ? "Low (stable rhythm)" : "High (inconsistent rhythm)")); // consistency evaluation rating
    std::cout << std::format("=> Feedback: {}\n", feedback);
}