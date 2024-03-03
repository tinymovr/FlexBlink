#include "FlexBlink.h"

constexpr int NUM_LEDS = 3;
constexpr int NUM_MODES = 1;
int ledPins[NUM_LEDS] = {2, 3, 4};
FlexBlink<NUM_LEDS, NUM_MODES> ledController(ledPins);

// Custom write function
void customWrite(int pin, int val) {
    // Example: Add logging or other functionality
    Serial.print("Writing to pin ");
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(val);

    digitalWrite(pin, val); // Call the original digitalWrite function
}

// Custom read function
int customRead(int pin) {
    // Example: Add logging or other functionality
    int val = digitalRead(pin); // Call the original digitalRead function

    Serial.print("Reading from pin ");
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(val);

    return val;
}

void setup() {
    Serial.begin(9600);

    // Set custom callbacks
    ledController.setWriteCallback(customWrite);
    ledController.setReadCallback(customRead);

    // Setup a simple mode where all LEDs blink together
    bool ledStates[NUM_LEDS] = {true, true, true};
    ledController.setupMode(0, 500, 500, ledStates);
}

void loop() {
    ledController.update();
}
