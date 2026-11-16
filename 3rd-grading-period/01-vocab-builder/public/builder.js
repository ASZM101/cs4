const wordInput = document.getElementById('word-input');
const searchBtn = document.getElementById('search-btn');
const resultsCard = document.getElementById('results-card');
const displayWord = document.getElementById('display-word');
const displayPhonetic = document.getElementById('display-phonetic');
const definitionsList = document.getElementById('definitions-list');
const synonymsContainer = document.getElementById('synonyms-container');
const errorBanner = document.getElementById('error-banner');

// query Express backend
async function fetchWordData() {
    const query = wordInput.value.trim();
    if (!query) return;

    // reset previous results + errors
    errorBanner.classList.add('hidden');
    resultsCard.classList.add('hidden');

    try {
        // send async GET request to backend
        const response = await fetch(`https://api.dictionaryapi.dev/api/v2/entries/en/${encodeURIComponent(query)}`);
        const data = (await response.json())[0];

        if (!response.ok) {
            throw new Error(data.error || 'failed to fetch word data');
        }

        renderWordData(data);
    } catch (err) {
        errorBanner.textContent = err.message;
        errorBanner.classList.remove('hidden');
    }
}

// render word data
function renderWordData(data) {
    displayWord.textContent = data["word"];

    // get phonetic spelling (if available)
    let phoneticText = '';
    if (data["phonetic"]) {
        phoneticText = data["phonetic"];
    } else if (data["phonetics"]) {
        phoneticText = data["phonetics"].at(-1)["text"];
    }
    displayPhonetic.textContent = phoneticText ? `${phoneticText}` : '';

    // // get definitions
    definitionsList.innerHTML = '';
    if (data["meanings"] && data["meanings"].length > 0) {
        data["meanings"].forEach(res => {
            const li = document.createElement('li');
            li.innerHTML = `<strong>(${res["partOfSpeech"]})</strong> ${res["definitions"][0]["definition"]}`;
            definitionsList.appendChild(li);
        });
    } else {
        const li = document.createElement('li');
        li.textContent = 'no definitions available';
        definitionsList.appendChild(li);
    }

    // show results card
    resultsCard.classList.remove('hidden');
}

searchBtn.addEventListener('click', fetchWordData);
wordInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') fetchWordData();
});