#ifndef FlexBlink_h
#define FlexBlink_h

#include <Arduino.h>

template<int NUM_LEDS, int NUM_MODES>
class FlexBlink {
public:
    FlexBlink(int* ledPins) {
        for (int i = 0; i < NUM_LEDS; i++) {
            this->ledPins[i] = ledPins[i];
            pinMode(ledPins[i], OUTPUT);
        }
    }

    void setupMode(int mode, long onTime, long offTime, const bool* ledStates) {
        if (mode < 0 || mode >= NUM_MODES) return;
        modes[mode].onTime = onTime;
        modes[mode].offTime = offTime;
        for (int i = 0; i < NUM_LEDS; i++) {
            modes[mode].ledStates[i] = ledStates[i];
        }
    }

    void changeMode(int mode) {
        if (mode < 0 || mode >= NUM_MODES) return;
        currentMode = mode;
        previousMillis = millis(); // Reset the timer to avoid immediate switching
    }

    void update() {
        unsigned long currentMillis = millis();
        Mode& mode = modes[currentMode];

        // Check for state change and toggle LEDs accordingly
        if ((currentMillis - previousMillis >= mode.onTime && !readCallback(ledPins[0])) || 
            (currentMillis - previousMillis >= mode.offTime && readCallback(ledPins[0]))) {
            for (int i = 0; i < NUM_LEDS; i++) {
                if (mode.ledStates[i]) {
                    int state = readCallback(ledPins[i]);
                    writeCallback(ledPins[i], !state);
                }
            }
            previousMillis = currentMillis;
        }
    }

    void setWriteCallback(void (*writeFunc)(int, int)) {
        writeCallback = writeFunc;
    }

    void setReadCallback(int (*readFunc)(int)) {
        readCallback = readFunc;
    }

private:
    struct Mode {
        long onTime;
        long offTime;
        bool ledStates[NUM_LEDS]; // States of LEDs in this mode
    };

    int ledPins[NUM_LEDS];
    Mode modes[NUM_MODES];
    int currentMode = 0;
    unsigned long previousMillis = 0;
    void (*writeCallback)(int, int) = [](int pin, int val) { digitalWrite(pin, val); };
    int (*readCallback)(int) = [](int pin) -> int { return digitalRead(pin); };
};

#endif // FlexBlink_h
