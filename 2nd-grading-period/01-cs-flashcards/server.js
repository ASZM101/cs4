// import modules
const express = require('express'); // Express framework
const fs = require('fs'); // to read JSON data
const path = require('path'); // to handle file dir paths

const app = express();
const PORT = 3000;

// 1. configure server to serve static files from public dir (route def order matters)
app.use(express.static(path.join(__dirname, 'public')));

// 2. read card data from JSON file
function getCardsData() {
    const rawData = fs.readFileSync(path.join(__dirname, 'cards.json'), 'utf8');
    return JSON.parse(rawData); // convert JSON text into JS object array
}

// 3. endpoint returns list of all flashcards (must come before page routing)
app.get('/api/cards', (request, response) => { // need leading slash before api
    const cards = getCardsData();
    response.json(cards);
});

// 3. endpoint returns single random flashcard (must come before page routing)
app.get('/api/cards/random', (request, response) => { // need leading slash before api
    const cards = getCardsData();
    const randomIndex = Math.floor(Math.random() * cards.length);
    response.json(cards[randomIndex]);
});

// 4. route root path to flashcards.html
app.get('/', (request, response) => {
    response.sendFile(path.join(__dirname, 'public', 'flashcards.html'));
});

// listening for incoming HTTP network requests
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});