let audioCtx = null; // web audio context (null for lazy initialization, later changed to AudioContext object)
const waveformSelect = document.getElementById('waveform');
const volumeInput = document.getElementById('volume');
const savePresetBtn = document.getElementById('save-preset-btn');
const presetNameInput = document.getElementById('preset-name');
const presetListSelect = document.getElementById('preset-list');
const keys = document.querySelectorAll('.key'); // data type: NodeList (array-like collection of HTML elements, but not true array)

// play tone at frequency using Web Audio API
function playNote(frequency) {
    // initialize AudioContext on 1st key press
    if (!audioCtx) {
        audioCtx = new (window.AudioContext || window.webkitAudioContext)();
    }

    const osc = audioCtx.createOscillator(); // oscillator node to generate wave
    const gainNode = audioCtx.createGain(); // gain node to control volume
    osc.type = waveformSelect.value; // waveform shape from dropdown
    osc.frequency.value = frequency; // pitch frequency (Hz)
    const volume = parseFloat(volumeInput.value); // volume slider value
    gainNode.gain.setValueAtTime(volume, audioCtx.currentTime); // set volume amplitude level on gain node
    gainNode.gain.exponentialRampToValueAtTime(0.0001, audioCtx.currentTime + 1.2); // quick fade out (prevent clicking sound)
    osc.connect(gainNode); // connect oscillator wave to volume gain node
    gainNode.connect(audioCtx.destination); // connect gain node output to system speakers
    osc.start(); // start audio tone
    osc.stop(audioCtx.currentTime + 1.2); // stop oscillator sound output after 1.2 sec
}

// add click listener to each keyboard btn
keys.forEach(key => {
    key.addEventListener('click', () => {
        const freq = parseFloat(key.getAttribute('data-note'));
        playNote(freq);
        key.classList.add('active');
        setTimeout(() => key.classList.remove('active'), 200);
    });
});

// map keyboard inputs to musical notes
window.addEventListener('keydown', (e) => {
    // ignore typing inside input fields
    if (e.target.tagName === 'INPUT') { // tagName returns uppercase HTML tag name
        return;
    }
    const keyChar = e.key.toLowerCase();
    const matchingKey = document.querySelector(`.key[data-key="${keyChar}"]`); // find key element matching computer letter key
    if (matchingKey) {
        matchingKey.click();
    }
});

// load presets from localStorage
async function loadPresets() {
    let presets = [];
    const localData = localStorage.getItem('piano_presets'); // check browser localStorage

    if (localData) {
        presets = JSON.parse(localData); // convert JSON string from localStorage to JS array
    } else {
        // fallback to fetching defaults from server if localStorage is empty
        try {
            const response = await fetch('/api/presets');
            if (response.ok) {
                presets = await response.json();
                localStorage.setItem('piano_presets', JSON.stringify(presets)); // save default server presets to localStorage
            }
        } catch (err) {
            console.error('Failed to load presets from server, using default fallbacks:', err);
            presets = [
                { id: 1, name: 'Default Sine', waveform: 'sine', volume: 0.5 },
                { id: 2, name: '8-Bit Square', waveform: 'square', volume: 0.3 }
            ];
            localStorage.setItem('piano_presets', JSON.stringify(presets));
        }
    }
    presetListSelect.innerHTML = '<option value="">Select a preset...</option>'; // reset dropdown list options

    // append each preset item to dropdown
    presets.forEach(preset => {
        const opt = document.createElement('option');
        opt.value = preset.id;
        opt.textContent = `${preset.name} (${preset.waveform})`;
        opt.dataset.preset = JSON.stringify(preset); // create data-preset attribute, convert JS object into JSON string, save to attribute
        presetListSelect.appendChild(opt);
    });
}

// update controls when user selects preset from dropdown
presetListSelect.addEventListener('change', (e) => {
    const selectedOption = e.target.options[e.target.selectedIndex];
    if (selectedOption && selectedOption.dataset.preset) {
        const preset = JSON.parse(selectedOption.dataset.preset);
        waveformSelect.value = preset.waveform;
        volumeInput.value = preset.volume;
    }
});

// save preset to localStorage (instead of sending HTTP POST request to API)
savePresetBtn.addEventListener('click', () => {
    const name = presetNameInput.value.trim();
    if (!name) {
        alert('Please enter a preset name.');
        return;
    }

    // read current presets array from localStorage
    const localData = localStorage.getItem('piano_presets');
    const presets = localData ? JSON.parse(localData) : [];

    // create new preset object with timestamp ID
    const newPreset = {
        id: Date.now(),
        name: name,
        waveform: waveformSelect.value,
        volume: parseFloat(volumeInput.value)
    };

    // append new preset, save updated array back to localStorage
    presets.push(newPreset);
    localStorage.setItem('piano_presets', JSON.stringify(presets));

    // clear input field, refresh dropdown list locally
    presetNameInput.value = '';
    loadPresets();
    alert('Preset saved successfully!');
});

// initialize presets dropdown on script load
loadPresets();