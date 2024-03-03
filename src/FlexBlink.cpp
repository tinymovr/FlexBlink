#include "FlexBlink.h"

FlexBlink::FlexBlink(int* _ledPins, int _numberOfLeds, int _maxModes) {
    // Initialize LEDs
    for (int i = 0; i < _numberOfLeds; i++) {
        pinMode(_ledPins[i], OUTPUT);
    }

    // Allocate memory for modes
    modes = new Mode[_maxModes]; // Adjust this number to support more modes
    maxModes = _maxModes;
    totalModes = 0;
}

void FlexBlink::setupMode(int mode, long onTime, long offTime, int* ledPins, int numberOfLeds) {
    if (mode >= 0 && mode < maxModes) {
        modes[mode].onTime = onTime;
        modes[mode].offTime = offTime;
        modes[mode].ledPins = ledPins;
        modes[mode].numberOfLeds = numberOfLeds;
        modes[mode].previousMillis = 0;

        if (mode == totalModes) totalModes++;
    }
}

void FlexBlink::changeMode(int mode) {
    if (mode >= 0 && mode < totalModes) {
        currentMode = mode;
    }
}

void FlexBlink::update() {
    unsigned long currentMillis = millis();
    Mode& mode = modes[currentMode];

    if ((currentMillis - mode.previousMillis >= mode.onTime) || 
        (currentMillis - mode.previousMillis >= mode.offTime)) {
        mode.previousMillis = currentMillis;

        for (int i = 0; i < mode.numberOfLeds; i++) {
            int state = digitalRead(mode.ledPins[i]);
            digitalWrite(mode.ledPins[i], !state);
        }
    }
}
