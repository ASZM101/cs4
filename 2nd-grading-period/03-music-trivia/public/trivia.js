let questions = [];
let indexCurrentQ = 0;
let score = 0;

const questionText = document.getElementById('question-text');
const optionsContainer = document.getElementById('options-container');
const feedbackMsg = document.getElementById('feedback-msg');
const nextBtn = document.getElementById('next-btn');
const quizCard = document.getElementById('quiz-card');
const summaryCard = document.getElementById('summary-card');
const finalScoreText = document.getElementById('final-score-text');
const restartBtn = document.getElementById('restart-btn');
const highScoreDisplay = document.getElementById('high-score');

// fetch list of questions from server
async function fetchQuestions() {
    try {
        const response = await fetch('/api/questions');
        questions = await response.json();
        loadHighScore();
        showQuestion();
    } catch (err) {
        questionText.textContent = 'Failed loading questions';
    }
}

// load high score from localStorage
function loadHighScore() {
    const savedHighScore = localStorage.getItem('music_trivia_highscore') || 0;
    highScoreDisplay.textContent = savedHighScore;
}

// display current question + options
function showQuestion() {
    feedbackMsg.textContent = ''; // reset feedback state
    nextBtn.classList.add('hidden');
    optionsContainer.innerHTML = '';
    const currentQ = questions[indexCurrentQ];
    questionText.textContent = `${indexCurrentQ + 1}. ${currentQ.question}`;

    // render btn for each option
    currentQ.options.forEach((optionText, index) => {
        const btn = document.createElement('button');
        btn.textContent = optionText;
        btn.addEventListener('click', () => checkAnswer(index, currentQ.answer, btn)); // check selected answer index
        optionsContainer.appendChild(btn);
    });
}

// evaluate selected answer (immediately after option is clicked)
function checkAnswer(selectedIndex, correctIndex, selectedBtn) {
    const btns = optionsContainer.querySelectorAll('button');
    btns.forEach(btn => btn.disabled = true); // disable all options after one is selected
    if (selectedIndex === correctIndex) {
        score++;
        selectedBtn.classList.add('correct');
        feedbackMsg.textContent = 'Correct!';
    } else {
        selectedBtn.classList.add('incorrect');
        btns[correctIndex].classList.add('correct'); // highlight correct answer
        feedbackMsg.textContent = 'Wrong answer!';
    }
    nextBtn.classList.remove('hidden');
}

// go to next question or show final results
nextBtn.addEventListener('click', () => {
    indexCurrentQ++;
    if (indexCurrentQ < questions.length) {
        showQuestion();
    } else {
        showSummary();
    }
});

// calculate final score + update high score
function showSummary() {
    quizCard.classList.add('hidden');
    summaryCard.classList.remove('hidden');
    finalScoreText.textContent = `You scored ${score} out of ${questions.length}!`;
    const savedHighScore = parseInt(localStorage.getItem('music_trivia_highscore') || 0);
    if (score > savedHighScore) {
        localStorage.setItem('music_trivia_highscore', score);
        highScoreDisplay.textContent = score;
    }
}

// restart quiz state
restartBtn.addEventListener('click', () => {
    score = 0;
    indexCurrentQ = 0;
    summaryCard.classList.add('hidden');
    quizCard.classList.remove('hidden');
    showQuestion();
});

// start quiz when script loads
fetchQuestions();