#ifndef PRACTICE_ENGINE_HPP // checks if header symbol is not defined before defining it
#define PRACTICE_ENGINE_HPP

// standard library headers
#include <vector>

// custom header files
#include "lesson.hpp"

// define class to store method for capturing rhythm timing
class PracticeEngine {
    public:
        static std::vector<double> runTest(const Lesson& lesson); // start rhythm test
};

#endif // end conditional preprocessor directive for header