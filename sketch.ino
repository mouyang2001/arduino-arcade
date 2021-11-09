#include "src/Joystick/Joystick.h"

#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 13
#define ANALOG_BUFFER 100
#define ANALOG_RESOLUTION 1024

Joystick joyStick(JOY_X, JOY_Y, JOY_BTN, ANALOG_BUFFER, ANALOG_RESOLUTION);

void setup()
{   
    pinMode(JOY_BTN, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop()
{
    joyStick.debug();
    delay(200);
}
