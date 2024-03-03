#ifndef FlexBlink_h
#define FlexBlink_h

#include <Arduino.h>

class FlexBlink {
    public:
        FlexBlink(int* _ledPins, int _numberOfLeds, int _maxModes);
        void setupMode(int mode, long onTime, long offTime, int* ledPins, int numberOfLeds);
        void changeMode(int mode);
        void update();
    
    private:
        struct Mode {
            long onTime;
            long offTime;
            int* ledPins;
            int numberOfLeds;
            unsigned long previousMillis;
        };

        Mode* modes;
        int currentMode;
        int totalModes;
        int maxModes;
};

#endif
