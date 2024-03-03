#include "FlexBlink.h"

constexpr int NUM_LEDS = 3;
constexpr int NUM_MODES = 2;
int ledPins[NUM_LEDS] = {2, 3, 4};
FlexBlink<NUM_LEDS, NUM_MODES> ledController(ledPins);

void setup() {
    // Mode 0: LED 1 and 3 blink
    bool mode0States[NUM_LEDS] = {true, false, true};
    ledController.setupMode(0, 1000, 1000, mode0States);

    // Mode 1: Only LED 2 blinks
    bool mode1States[NUM_LEDS] = {false, true, false};
    ledController.setupMode(1, 500, 500, mode1States);

    // Start with mode 0
    ledController.changeMode(0);
}

void loop() {
    ledController.update();

    // Example to change mode based on some condition, e.g., every 10 seconds
    static unsigned long lastChangeMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastChangeMillis > 10000) {
        static int currentMode = 0;
        currentMode = (currentMode + 1) % NUM_MODES; // Cycle through modes
        ledController.changeMode(currentMode);
        lastChangeMillis = currentMillis;
    }
}
