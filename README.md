# FlexBlink

FlexBlink is an Arduino library for controlling LEDs with customizable blinking patterns. It allows users to define multiple modes for their LEDs, each with unique on and off times, and switch between these modes dynamically.

## Installation

1. Download the FlexBlink library as a ZIP file.
2. Open the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library...` and select the downloaded ZIP file.
3. Once installed, you can include it in your projects with `#include <FlexBlink.h>`.

## Usage

Here's a basic example to get started:

```cpp
#include <FlexBlink.h>

// Define LED pins
int ledPins[] = {2, 3, 4}; 
// Initialize FlexBlink with LED pins
FlexBlink ledControl(ledPins, 3);

void setup() {
    // Setup LED modes
    ledControl.setupMode(0, 500, 500, ledPins, 3); // Mode 0
    ledControl.setupMode(1, 200, 800, ledPins, 3); // Mode 1
}

void loop() {
    // Update LED states
    ledControl.update();
}
