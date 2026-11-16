const wordInput = document.getElementById('word-input');
const searchBtn = document.getElementById('search-btn');
const resultsCard = document.getElementById('results-card');
const displayWord = document.getElementById('display-word');
const displayPhonetic = document.getElementById('display-phonetic');
const definitionsList = document.getElementById('definitions-list');
const examplesContainer = document.getElementById('examples-container');
const examplesTitle = document.getElementById('examples-title');
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
    displayWord.textContent = data['word'];

    // get phonetic spelling (if available)
    let phoneticText = '';
    if (data['phonetic']) {
        phoneticText = data['phonetic'];
    } else if (data['phonetics']) {
        phoneticText = data['phonetics'].at(-1)['text'];
    }
    displayPhonetic.textContent = phoneticText ? `${phoneticText}` : '';

    // get definitions
    definitionsList.innerHTML = '';
    if (data['meanings'] && data['meanings'].length > 0) {
        data['meanings'].forEach(speech => {
            speech['definitions'].forEach(def => {
                const defDisplay = document.createElement('li');
                defDisplay.innerHTML = `(<strong>${speech['partOfSpeech']}</strong>) ${def['definition']}`;
                definitionsList.appendChild(defDisplay);
            })
        });
    } else {
        const noDef = document.createElement('p');
        noDef.textContent = '(no definitions available)';
        definitionsList.appendChild(noDef);
    }

    // get examples
    examplesContainer.innerHTML = '';
    if (data['meanings'] && data['meanings'].length > 0) {
        examplesContainer.classList.remove('hidden');
        examplesTitle.classList.remove('hidden');
        data['meanings'].forEach(speech => {
            speech['definitions'].forEach(def => {
                const exDisplay = document.createElement('li');
                exDisplay.innerHTML = def['example'] ? `(<strong>${speech['partOfSpeech']}</strong>) <em>${def['example']}</em>` : '';
                if (exDisplay.innerHTML.length > 0) {
                    examplesContainer.appendChild(exDisplay);
                }
            });
        });
    }
    if (examplesContainer.innerHTML.length == 0 || !data['meanings']) {
        examplesContainer.classList.add('hidden');
        examplesTitle.classList.add('hidden');
    }

    // show results card
    resultsCard.classList.remove('hidden');
}

searchBtn.addEventListener('click', fetchWordData);
wordInput.addEventListener('keypress', (e) => {
    if (e.key === 'Enter') fetchWordData();
});