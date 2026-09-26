Pre-AP Computer Science Independent Study Coursework

*2026-2027 (12th Grade)*

[![wakatime](https://wakatime.com/badge/github/ASZM101/cs4.svg)](https://wakatime.com/badge/github/ASZM101/cs4)

## Table of Contents

### 1st Grading Period

1. [Music Calculator](https://aszm101.github.io/cs4/#01-music-calculator)

2. [Health Tracker](https://aszm101.github.io/cs4/#02-health-tracker)

3. [Note Generator](https://aszm101.github.io/cs4/#03-note-generator)

4. [Rhythm Tester](https://aszm101.github.io/cs4/#04-rhythm-tester)

### 2nd Grading Period

1. [CS Flaschards](https://aszm101.github.io/cs4/#01-cs-flashcards)

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

## 2nd Grading Period

### Prerequisites for All Projects

* **Runtime environment:** Node.js (v18 or later)

* **Package manager:** `npm` (included with Node.js)

* **Build tool:** Terminal / command line interface

### `01-cs-flashcards`

* [**Deployed website**](https://aszm101-cs-flashcards.vercel.app)

* [**Demo video**](https://youtu.be/ve5ZesKccBk)

* **What it does:** A full-stack web application featuring an Express.js REST API that serves AP Computer Science A terms and definitions from JSON data to a flashcard interface

* **How to run locally:**
  ```bash
  cd 2nd-grading-period/01-cs-flashcards
  npm install
  node server.js
  ```

  Then open `http://localhost:3000` in your web browser.