#ifndef ANALYTICS_HPP // check if header symbol is not defined before defining it
#define ANALYTICS_HPP

// standard library headers
#include <string>
#include <vector>

// define class to store methods for analysis rhythm tests
class Analytics {
    public:
        static double calcError(const std::vector<double>& errors); // calculate mean absolute error ($: reference, modifies original)
        static std::vector<double> sortDeviations(const std::vector<double>& errors); // sort absolute timing deviations
        static std::string feedback(double meanError); // generate feedback message
};

#endif // end conditional preprocessor directive for header