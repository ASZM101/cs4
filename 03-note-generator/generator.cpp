// standard library headers
#include <cmath>
#include <format>
#include <iostream>
#include <numbers>
#include <string>

// custom header files
#define MINIAUDIO_IMPLEMENTATION // preprocessor directive: creates macro (finds + replaces text in source code before compilation starts; this line can only be in one cpp file, need to define BEFORE including miniaudio.h)
#include "miniaudio.h" // miniaudio source (external library for audio processing): https://github.com/mackron/miniaudio

// func declarations (both actual def AND prototype MUST match)
void handleMenu(std::string input);
void note();
void melody();
void visualize();

// define base class to store attributes + methods for all oscillators
class Oscillator {
    public: // general order (though doesn't truly matter): public first (constructors, destructor, getters / access methods, setters / modify methods, other / worker methods), then protected, private last
        Oscillator(double f) : frequency(f) {} // member initializer list: more efficient than assigning in constructor body (where attributes are first default-constructed, then re-assigned, less efficient, also required for const vars / references)
        virtual ~Oscillator() = default; // standard virtual destructor (~): required for classes w/ virtual func (at bottom of public)
        double getFrequency() { // double should be default for decimals (returned by most math functions, prevents unexpected accuracy loss)
            return frequency;
        }
        void setFrequency(double f) {
            frequency = f;
        }
        void setAmplitude(double amp) {
            amplitude = amp;
        }
        void setSampleRate(double sr) {
            sampleRate = sr;
        }
        void resetPhase() { // to start new note
            phase = 0;
        }
        virtual double getY(double time) = 0; // = 0 makes it a pure virtual method (forces derived classes to implement func, turns class into abstract class / interface, cannot create instance of Oscillator directly)
        virtual double nextY() = 0;
    protected: // protected: allows attributes to be accessed inside derived classes (private: could only be accessed within defining class); better to define default values in declaration
        double frequency; // note pitch (hertz)
        double amplitude = 0.5; // peak height of wave (volume)
        double phase = 0; // current angle within wave's cycle (radians, 0 to 2pi)
        double sampleRate = 48000; // resolution / upper frequency limit of audio (hertz), how much phase increments per audio frame (p = 2pi * f / sr); 48 kHz = standard sample rate in digital audio
}; // need semicolon b/c class definition treated as declaration statement (can declare object / instance of class immediately after closing bracket)

// define derived class to store attributes + methods for sine oscillators (smooth)
class SineOscillator : public Oscillator {
    public:
        SineOscillator(double f) : Oscillator(f) {} // use base constructor
        double getY(double time) override { // return sine sample y(t) at time t (in seconds)
            return amplitude * std::sin(2.0 * std::numbers::pi * frequency * time); // sine sample: y(t) = A * sin(2pi * ft); angle for sine must be in radians
        }
        double nextY() override { // generate next sample, update phase state
            double y = amplitude * std::sin(phase); // sine value at current phase (angle in cycle of wave): y = A * sin(p)
            phase += (2.0 * std::numbers::pi * frequency) / sampleRate; // update phase for next sample: p += 2pi * f / sr
            if (phase >= 2.0 * std::numbers::pi) { // keep phase bound within 2pi rad
                phase -= 2.0 * std::numbers::pi;
            }
            return y;
        }
};

// WIP => define derived class to store attributes + methods for square oscillators (flat top + bottom)
class SquareOscillator : public Oscillator {
    public:
        SquareOscillator(double f) : Oscillator(f) {} // use base constructor
        double getY(double time) override { // return square sample y(t) at time t (in seconds)
            double sine = std::sin(2.0 * std::numbers::pi * frequency * time); // sine value (for reference); angle for sine must be in radians
            return (sine >= 0) ? amplitude : -amplitude; // either top or bottom of square wave
        }
        double nextY() override { // generate next sample, update phase state
            double y = (std::sin(phase) >= 0) ? amplitude : -amplitude; // square wave state (either top or bottom) at current phase (angle in cycle of wave)
            phase += (2.0 * std::numbers::pi * frequency) / sampleRate; // update phase for next sample: p += 2pi * f / sr
            if (phase >= 2.0 * std::numbers::pi) { // keep phase bound within 2pi rad
                phase -= 2.0 * std::numbers::pi;
            }
            return y;
        }
};

// display menu options [=> used for single-line outputs, (!) used for errors]
int main() {
    std::string input = "";
    std::cout << "Welcome to the Note Generator!\n";
    while (input != "4") {
        std::string menu = R"(Choose one of the following options:
[1] Play single note
[2] Generate algorithmic melody
[3] View soundwave visualization
[4] Exit
Enter selected option (ie. 1, 2, 3, 4): )";
        std::cout << std::format("\n{}", menu);
        std::cin >> input;
        handleMenu(input);
    }
    std::cout << "=> Thank you for using the Note Generator!\n";
    return 0;
}

// execute selected menu option based on input
void handleMenu(std::string input) {
    if (input == "1") {
        note();
    } else if (input == "2") {
        melody();
    } else if (input == "3") {
        visualize();
    } else if (input == "4") {
        return;
    } else {
        std::cout << "(!) Please only type 1, 2, 3, or 4 to select an option.\n";
    }
}

// WIP => [1] export note to wav file (given wave type + frequency + duration, use external library for audio processing)
void note() {
    std::cout << "Note generator mode selected.\n";
}

// WIP => [2] export melody to wav file (given root note, use math functions + nested loops for creating sequence of notes, use external library for audio processing)
void melody() {
    std::cout << "Melody generator mode selected.\n";
}

// WIP => [3] view soundwave visualization (given wave type + frequency, use ASCII amplitude plot)
void visualize() {
    std::cout << "Visualization mode selected.\n";
}