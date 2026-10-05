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

// fetch stored presets from server API
async function loadPresets() {
    try {
        const response = await fetch('/api/presets');
        const presets = await response.json();
        presetListSelect.innerHTML = '<option value="">Select a preset...</option>'; // reset dropdown list options

        // append each preset item to dropdown
        presets.forEach(preset => {
            const opt = document.createElement('option');
            opt.value = preset.id;
            opt.textContent = `${preset.name} (${preset.waveform})`;
            opt.dataset.preset = JSON.stringify(preset); // create data-preset attribute, convert JS object into JSON string, save to attribute
            presetListSelect.appendChild(opt);
        });
    } catch (err) {
        console.error('Failed to load presets:', err);
    }
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

// send new preset to backend API on btn click
savePresetBtn.addEventListener('click', async () => {
    const name = presetNameInput.value.trim();
    if (!name) {
        alert('Please enter a preset name.');
        return;
    }

    // object for sound settings saved by user
    const payload = {
        name: name,
        waveform: waveformSelect.value,
        volume: parseFloat(volumeInput.value)
    };

    try {
        // send HTTP POST request to API endpoint
        const response = await fetch('/api/presets', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload)
        });

        // clear input field, refresh dropdown list
        if (response.ok) {
            presetNameInput.value = '';
            await loadPresets();
            alert('Preset saved successfully!');
        }
    } catch (err) {
        console.error('Failed to save preset:', err);
    }
});

// initialize presets dropdown on script load
loadPresets();