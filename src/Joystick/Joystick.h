#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

/**
 * @brief Handles the joystick input.
 * 
 * @author Matthew Ouyang
 * @date 09/11/2021
 */
class Joystick {
    public:
        enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

        Joystick(int pinX, int pinY, int pinButton, int analogBuffer, int analogResolution);
        
        void debug();

        int getX();
        int getY();
        bool isPressed();
        Direction getDirection();

    private:
        int _pinX;
        int _pinY;
        int _pinButton;
        int _analogBuffer;
        int _analogResolution;
};

#endif 