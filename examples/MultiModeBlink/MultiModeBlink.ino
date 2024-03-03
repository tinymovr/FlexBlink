#include <FlexBlink.h>

int ledPins[] = {2, 3, 4}; // Define LED pins
FlexBlink ledControl(ledPins, 3);

const int buttonPin = 5; // Define button pin
int lastButtonState = LOW;
int currentMode = 0;

void setup() {
    pinMode(buttonPin, INPUT_PULLUP); // Set the button as an input

    // Setup modes
    ledControl.setupMode(0, 500, 500, ledPins, 3); // Mode 0: All LEDs blink at 500ms intervals
    ledControl.setupMode(1, 200, 800, ledPins, 3); // Mode 1: All LEDs blink at different intervals
}

void loop() {
    // Update LEDs
    ledControl.update();

    // Read the state of the button
    int buttonState = digitalRead(buttonPin);

    // Check if the button is pressed
    if (buttonState == LOW && lastButtonState == HIGH) {
        currentMode = (currentMode + 1) % 2; // Change the mode
        ledControl.changeMode(currentMode);
    }

    lastButtonState = buttonState; // Save the current state as the last state, for next time through the loop
}
