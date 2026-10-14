let allQs = []; // raw array fetched from server
let activeQs = []; // shuffled / sliced questions for active quiz
let indexCurrentQ = 0;
let score = 0;

// config menu
const setupCard = document.getElementById('setup-card');
const categorySelect = document.getElementById('category-select');
const questionSlider = document.getElementById('question-slider');
const sliderValDisplay = document.getElementById('slider-val');
const startBtn = document.getElementById('start-btn');

// question + options
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
        allQs = await response.json();
        loadHighScore();
        updateSliderMax(); // set slider max based on question count
    } catch (err) {
        questionText.textContent = 'Failed loading questions';
    }
}

// load high score from localStorage
function loadHighScore() {
    const savedHighScore = localStorage.getItem('music_trivia_highscore') || 0;
    highScoreDisplay.textContent = savedHighScore;
}

// set slider max based on question count
function updateSliderMax() {
    const selectedCat = categorySelect.value;
    const categoryQuestions = selectedCat === 'all' ? allQs : allQs.filter(q => q.category === selectedCat);

    // set slider max value to total available matching questions
    questionSlider.max = categoryQuestions.length;
    
    // adjust current slider value if it exceeds new maximum
    if (parseInt(questionSlider.value) > categoryQuestions.length) {
        questionSlider.value = categoryQuestions.length;
    }
    sliderValDisplay.textContent = questionSlider.value;
}

// shuffle question array in random order (Fisher-Yates algorithm: standard for "randomly permuting sequences"?)
function shuffleArray(arr) {
    const shuffled = [...arr]; // creates copy of arr (not reference to same var in memory)
    for (let i = shuffled.length - 1; i > 0; i--) { // start at end of unshuffled arr
        const j = Math.floor(Math.random() * (i + 1)); // randomly pick one element from remaining unshuffled part of arr (min = 0 inclusive, max = i + 1 exclusive = i b/c rounding down)
        [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]]; // swap element at i w/ element at j
    }
    return shuffled;
}

// display current question + options
function showQuestion() {
    feedbackMsg.textContent = ''; // reset feedback state
    nextBtn.classList.add('hidden');
    optionsContainer.innerHTML = '';
    const currentQ = activeQs[indexCurrentQ];
    questionText.textContent = `${indexCurrentQ + 1}. ${currentQ.question}`;

    // render btn for each option
    currentQ.options.forEach((optionText, index) => {
        const btn = document.createElement('button');
        btn.textContent = optionText;
        btn.classList.add('option');
        btn.addEventListener('click', () => checkAnswer(index, currentQ.answer, btn)); // check selected answer index
        optionsContainer.appendChild(btn);
    });
}

// prepare question subset + start quiz
function startQuiz() {
    const selectedCat = categorySelect.value;
    const filtered = selectedCat === 'all' ? allQs : allQs.filter(q => q.category === selectedCat);
    const numQuestions = parseInt(questionSlider.value);
    activeQs = shuffleArray(filtered).slice(0, numQuestions);

    // reset quiz state variables
    score = 0;
    indexCurrentQ = 0;

    // toggle card views
    setupCard.classList.add('hidden');
    summaryCard.classList.add('hidden'); // doesn't add duplicate class if already added
    quizCard.classList.remove('hidden');

    showQuestion();
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
    if (indexCurrentQ < activeQs.length) {
        showQuestion();
    } else {
        showSummary();
    }
});

// calculate final score + update high score
function showSummary() {
    quizCard.classList.add('hidden');
    summaryCard.classList.remove('hidden');
    finalScoreText.textContent = `You scored ${score} out of ${activeQs.length}!`;
    const savedHighScore = parseInt(localStorage.getItem('music_trivia_highscore') || 0);
    if (score > savedHighScore) {
        localStorage.setItem('music_trivia_highscore', score);
        highScoreDisplay.textContent = score;
    }
}

// event listeners for config menu
categorySelect.addEventListener('change', updateSliderMax);
questionSlider.addEventListener('input', () => {
    sliderValDisplay.textContent = questionSlider.value;
});
startBtn.addEventListener('click', startQuiz);

// return to setup card on restart btn click
restartBtn.addEventListener('click', () => {
    summaryCard.classList.add('hidden');
    setupCard.classList.remove('hidden');
});

// start quiz when script loads
fetchQuestions();