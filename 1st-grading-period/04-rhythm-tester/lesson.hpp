#ifndef LESSON_HPP // check if header symbol is not defined before defining it
#define LESSON_HPP

// standard library headers
#include <string>

// define class to store attributes + methods for storing practice exercises
class Lesson {
    public: // constructor + getter methods
        Lesson(const std::string& lessonTitle, int lessonBpm, int beats); // $: reference, modifies original
        std::string getTitle() const;
        int getBpm() const;
        int getTotalBeats() const;
    private:
        std::string title;
        int bpm; // beats per minute (tempo)
        int totalBeats; // total number of beats in test
};

#endif // end conditional preprocessor directive for header