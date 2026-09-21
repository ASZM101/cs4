# CS4

[![wakatime](https://wakatime.com/badge/github/ASZM101/cs4.svg)](https://wakatime.com/badge/github/ASZM101/cs4)

All of my coursework for Computer Science Independent Study KAP (CS4)

*2026-2027 (12th Grade)*

### Prerequisites

* **Compiler:** `g++` (supports C++17 or later) or `clang++`

* **Build tool:** Terminal / command line interface

## `01-music-calculator`

* **What it does:** Calculates audio frequencies, delays, and beat intervals based on user-entered tempo (BPM) and note input

* **How to build:**

  ```bash
  cd 01-music-calculator
  g++ -std=c++17 calculator.cpp -o calculator
  ./calculator
  ```

## `02-health-tracker`

* **What it does:** Tracks daily physical activity metrics, calculates calories burned, and outputs health summary statistics

* **How to build:**

  ```bash
  cd 02-health-tracker
  g++ -std=c++17 tracker.cpp -o tracker
  ./tracker
  ```

## `03-note-generator`

* **What it does:** Generates digital sine wave audio data and outputs raw sound samples based on specified frequencies and durations

* **How to build:**

  ```bash
  cd 03-note-generator
  g++ -std=c++17 generator.cpp -o generator
  ./generator
  ```

## `04-rhythm-tester`

* **What it does:** Reads exercise configurations from external files, tests user keypress timing accuracy against a metronome, and computes performance statistics

* **How to build:**

  ```bash
  cd 04-rhythm-tester
  g++ -std=c++17 tester.cpp lesson.cpp analytics.cpp practice_engine.cpp -o tester
  ./tester
  ```
