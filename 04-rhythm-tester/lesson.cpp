// custom header files
#include "lesson.hpp"

Lesson::Lesson(const std::string& lessonTitle, int lessonBpm, int beats) : title(lessonTitle), bpm(lessonBpm), totalBeats(beats) {} // initializer list

// getter methods
std::string Lesson::getTitle() const {
    return title;
}
int Lesson::getBpm() const {
    return bpm;
}
int Lesson::getTotalBeats() const {
    return totalBeats;
}