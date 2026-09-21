// standard library headers
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// custom header files
#include "practice_engine.hpp"

// start rhythm test
std::vector<double> PracticeEngine::runTest(const Lesson& lesson) {
    std::vector<double> errors; // in milliseconds
    double beatIntervalMs = (60 / lesson.getBpm()) * 1000; // delay between beats from bpm
    std::cout << "\nPress [ENTER] in sync with the " << lesson.getTotalBeats() << " target metronome beats.\n";
    std::cout << "Press [ENTER] to start...";
    std::string input;
    std::getline(std::cin, input); // pause until user hits enter key
    std::cout << "\nGet ready! Test starting...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // sleep for 1sec before starting metronome
    auto startTime = std::chrono::high_resolution_clock::now(); // capture start time
    for (int i = 1; i <= lesson.getTotalBeats(); ++i) {
        double targetBeatTimeMs = i * beatIntervalMs; // expected arrival time for current beat
        std::cout << "Beat " << i << " target: " << static_cast<int>(targetBeatTimeMs) << " ms => Press [ENTER]";
        std::cout.flush(); // flush output buffer (so text appears immediately)
        std::getline(std::cin, input); // capture moment user hits enter key
        auto userPressTime = std::chrono::high_resolution_clock::now(); // capture high resolution timestamp of keypress
        std::chrono::duration<double, std::milli> elapsed = userPressTime - startTime; // elapsed time since test start (as object)
        double actualTimeMs = elapsed.count(); // elapsed duration (as double)
        double error = actualTimeMs - targetBeatTimeMs;
        errors.push_back(error);
        std::cout << " (registered at " << static_cast<int>(actualTimeMs) << " ms, error: "
                  << (error >= 0 ? "+" : "") << static_cast<int>(error) << " ms)\n";
    }
    return errors;
}