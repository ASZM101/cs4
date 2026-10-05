// import modules
const express = require('express'); // Express framework
const fs = require('fs'); // to read JSON data
const path = require('path'); // to handle file dir paths

const app = express();

app.use(express.json()); // parse incoming JSON data from frontend (not read-only)
app.use(express.static(path.join(__dirname, 'public'))); // configure server to serve static files from public dir (route def order matters)

// load presets from JSON file
function loadPresets() {
    const rawData = fs.readFileSync(path.join(__dirname, 'presets.json'), 'utf8');
    return JSON.parse(rawData); // convert JSON text into JS object array
}

// save presets array into JSON file
function savePresets(presets) {
    const jsonData = JSON.stringify(presets, null, 2); // convert JS object array into JSON text
    fs.writeFileSync(path.join(__dirname, 'presets.json'), jsonData, 'utf8');
}

// endpoint to fetch all stored presets
app.get('/api/presets', (request, response) => {
    const presets = loadPresets();
    response.json(presets);
});

// endpoint to save new preset
app.post('/api/presets', (request, response) => {
    const { name, waveform, volume } = request.body; // read client input data from request body
    const presets = loadPresets();
    const newPreset = {
        id: Date.now(), // unique ID (milliseconds elapsed from 1970-01-01)
        name: name || 'Custom Preset',
        waveform: waveform || 'sine',
        volume: parseFloat(volume) || 0.5
    };
    presets.push(newPreset);
    savePresets(presets);
    response.status(201).json(newPreset); // return created preset as confirmation
});

// route root path to synth.html
app.get('/', (request, response) => {
    response.sendFile(path.join(__dirname, 'public', 'synth.html'));
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