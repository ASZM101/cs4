// standard library headers
#include <algorithm>
#include <cmath>

// custom header files
#include "analytics.hpp"

// calculate mean absolute error
double Analytics::calcError(const std::vector<double>& errors) {
    if (errors.empty()) {
        return 0;
    }
    double sum = 0;
    for (double err : errors) { // iterate through each error value
        sum += std::abs(err);
    }
    return sum / errors.size();
}

// sort absolute timing deviations
std::vector<double> Analytics::sortDeviations(const std::vector<double>& errors) {
    std::vector<double> deviations; // absolute deviation values
    for (double err : errors) { // iterate through raw error values
        deviations.push_back(std::abs(err));
    }
    std::sort(deviations.begin(), deviations.end()); // sort absolute deviation values in ascending order
    return deviations;
}

// generate feedback message (ranges based on practice tests, might depend on connectivity of codespaces?)
std::string Analytics::feedback(double meanError) {
    if (meanError < 250) { // in milliseconds
        return "Great timing stability! Practice accenting Beat 1.";
    } else if (meanError < 500) {
        return "Good rhythm overall! Focus on steady metronome listening to reduce drift.";
    } else {
        return "Timing needs work. Try slowing down the tempo and tapping steadily with a metronome.";
    }
}