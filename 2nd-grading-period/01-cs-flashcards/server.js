// import modules
const express = require('express'); // Express framework
const fs = require('fs'); // to read JSON data
const path = require('path'); // to handle file dir paths

const app = express();
const PORT = 3000;

// configure server to serve static files from public dir
app.use(express.static(path.join(__dirname, 'public')));

// read card data from JSON file
function getCardsData() {
    const rawData = fs.readFileSync(path.join(__dirname, 'cards.json'), 'utf8');
    return JSON.parse(rawData); // convert JSON text into JS object array
}

// endpoint returns list of all flashcards
app.get('/api/cards', (request, response) => {
    const cards = getCardsData();
    response.json(cards);
});

// endpoint returns single random flashcard
app.get('/api/cards/random', (request, response) => {
    const cards = getCardsData();
    const randomIndex = Math.floor(Math.random() * cards.length);
    response.json(cards[randomIndex]);
});

// listening for incoming HTTP network requests
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});