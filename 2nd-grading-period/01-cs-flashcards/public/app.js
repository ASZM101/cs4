const flashcard = document.getElementById('flashcard');
const cardFront = document.getElementById('card-front');
const cardBack = document.getElementById('card-back');
const nextBtn = document.getElementById('next-btn');

// track whether current card is showing definition
let isFlipped = false; // let > var (more predictable, block-scoped instead of function-scoped; block = loop, if statement, etc.)

// send fetch request for random card
async function fetchRandomCard() {
    try {
        const response = await fetch('/api/cards/random'); // send async HTTP GET request to endpoint
        const cardData = await response.json(); // parse returned JSON response

        cardFront.innerHTML = `<h2>${cardData.term}</h2>`;
        cardBack.innerHTML = `<p>${cardData.definition}</p>`;

        // reset flip state (to make card open term-side up)
        isFlipped = false;
        cardFront.classList.remove('hidden');
        cardBack.classList.add('hidden');
    } catch (error) {
        console.error('Error fetching flashcard:', error);
    }
}

// toggle card flip state
function flipCard() {
    isFlipped = !isFlipped;
    if (isFlipped) {
        cardFront.classList.add('hidden');
        cardBack.classList.remove('hidden');
    } else {
        cardFront.classList.remove('hidden');
        cardBack.classList.add('hidden');
    }
}

flashcard.addEventListener('click', flipCard);
nextBtn.addEventListener('click', fetchRandomCard);

// load initial flashcard when application loads
fetchRandomCard();