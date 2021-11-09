#include "Arduino.h"
#include "Joystick.h"

/**
 * @brief Construct a new Joystick:: Joystick object
 * 
 * @param pinX Analog pin for X axis input.
 * @param pinY Analog pin for Y axis input.
 * @param pinButton Digital pin for button input.
 * @param analogBuffer Buffer size for analog input to allow error room. 
 * @param analogResolution Resolution of analog input.
 */
Joystick::Joystick(int pinX, int pinY, int pinButton, int analogBuffer, int analogResolution)
{
    _pinX = pinX;
    _pinY = pinY;
    _pinButton = pinButton;
    _analogBuffer = analogBuffer;
    _analogResolution = analogResolution;
    
    // Use inbuilt pullup resistor.
    pinMode(pinButton, INPUT_PULLUP);
}

/**
 * @brief Output joystick data to serial port.
 */
void Joystick::debug() {
    Serial.print("x= ");
    Serial.print(Joystick::getX());
    Serial.print(" y= ");
    Serial.print(Joystick::getY());
    Serial.print(" sw= ");
    Serial.print(Joystick::isPressed());
    Serial.print(" dir= ");
    Serial.print(Joystick::getDirection());
    Serial.println("");
}

/**
 * @brief X axis analog value getter.
 * 
 * @return int analog value of X axis.
 */
int Joystick::getX()
{
    return analogRead(_pinX);
}

/**
 * @brief Y axis analog value getter.
 * 
 * @return int analog value of Y axis.
 */
int Joystick::getY()
{
    return analogRead(_pinY);
}

/**
 * @brief Y axis analog value getter.
 * 
 * @return int analog value of Y axis.
 */
bool Joystick::isPressed() {
    int pressed = digitalRead(_pinButton);
    if (pressed == LOW)
        return true;
    else
        return false;
}

/**
 * @brief get direction of joystick.
 * 
 * @return Direction enum of joystick.
 */
Joystick::Direction Joystick::getDirection()
{   
    int xVal = getX();
    int yVal = getY();
    int analogMid = _analogResolution / 2;

    if (xVal > analogMid + _analogBuffer)
    {
        return Joystick::Direction::RIGHT;
    }
    else if (xVal < analogMid - _analogBuffer)
    {
        return Joystick::Direction::LEFT;
    }
    else if (yVal < analogMid - _analogBuffer)
    {
        return Joystick::Direction::UP;
    }
    else if (yVal > analogMid + _analogBuffer)
    {
        return Joystick::Direction::DOWN;
    } 

    return Joystick::Direction::NONE;
}
