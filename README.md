Pre-AP Computer Science Independent Study coursework

*2026-2027 (12th Grade)*

[![wakatime](https://wakatime.com/badge/github/ASZM101/cs4.svg)](https://wakatime.com/badge/github/ASZM101/cs4)

## Table of Contents

### 1st Grading Period

1. [Music Calculator](https://aszm101.github.io/cs4/#01-music-calculator)

2. [Health Tracker](https://aszm101.github.io/cs4/#02-health-tracker)

3. [Note Generator](https://aszm101.github.io/cs4/#03-note-generator) *(WIP)*

4. [Rhythm Tester](https://aszm101.github.io/cs4/#04-rhythm-tester) *(WIP)*

### 2nd Grading Period

1. [CS Flaschards](https://aszm101.github.io/cs4/2nd-grading-period/01-cs-flashcards/public/flashcards.html) *(WIP)*

2. [Piano Synth](https://aszm101.github.io/cs4/2nd-grading-period/02-piano-synth/public/synth.html) *(WIP)*

3. [Music Trivia](https://aszm101.github.io/cs4/2nd-grading-period/03-music-trivia/public/trivia.html) *(WIP)*

4. [Code Explainer](https://aszm101.github.io/cs4/2nd-grading-period/04-code-explainer/public/explainer.html) *(WIP)*

5. [Pitch Tuner](https://aszm101.github.io/cs4/2nd-grading-period/05-pitch-tuner/public/tuner.html) *(WIP)*

## 1st Grading Period

### Prerequisites for All Projects

* **Compiler:** `g++` (supports C++20 or later) or `clang++`

* **Build tool:** Terminal / command line interface

### `01-music-calculator`

* **What it does:** Calculates audio frequencies, delays, and beat intervals based on user-entered tempo (BPM) and note input

* **How to build:**

  ```bash
  cd 1st-grading-period/01-music-calculator
  g++ -std=c++20 calculator.cpp -o calculator
  ./calculator
  ```

### `02-health-tracker`

* **What it does:** Tracks daily physical activity metrics, calculates calories burned, and outputs health summary statistics

* **How to build:**

  ```bash
  cd 1st-grading-period/02-health-tracker
  g++ -std=c++20 tracker.cpp -o tracker
  ./tracker
  ```

### `03-note-generator`

* **What it does:** Generates digital sine wave audio data and outputs raw sound samples based on specified frequencies and durations

* **How to build:**

  ```bash
  cd 1st-grading-period/03-note-generator
  g++ -std=c++20 generator.cpp -o generator
  ./generator
  ```

### `04-rhythm-tester`

* **What it does:** Reads exercise configurations from external files, tests user keypress timing accuracy against a metronome, and computes performance statistics

* **How to build:**

  ```bash
  cd 1st-grading-period/04-rhythm-tester
  g++ -std=c++20 tester.cpp lesson.cpp analytics.cpp practice_engine.cpp -o tester
  ./tester
  ```
