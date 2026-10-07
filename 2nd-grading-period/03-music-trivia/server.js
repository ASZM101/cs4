// import modules
const express = require('express'); // Express framework
const fs = require('fs'); // to read JSON data
const path = require('path'); // to handle file dir paths

const app = express();

app.use(express.json()); // parse incoming JSON data from frontend (not read-only)
app.use(express.static(path.join(__dirname, 'public'))); // configure server to serve static files from public dir (route def order matters)

// endpoint returns list of questions
app.get('/api/questions', (request, response) => {
    fs.readFile(path.join(__dirname, 'questions.json'), 'utf8', (err, data) => {
        if (err) {
            return response.status(500).json({
                error: 'Failed reading question data'
            });
        }
        response.json(JSON.parse(data)); // return converted JSON text into JS object array
    });
});

// route root path to trivia.html
app.get('/', (request, response) => {
    response.sendFile(path.join(__dirname, 'public', 'trivia.html'));
});

// export app for Vercel
module.exports = app;

// listen for incoming HTTP network requests (if run locally)
if (require.main === module) { // require.main = entry point file executed by Node, module = current JS file; only true when run from terminal
    const PORT = process.env.PORT || 3000; // process.env.PORT = environment var PORT set by host provider, 3000 = fallback for when running on PC
    app.listen(PORT, () => {
        console.log(`Server running on http://localhost:${PORT}`);
    });
}