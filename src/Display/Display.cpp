#include "Display.h"
#include "Arduino.h"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

Display::Display(uint8_t address, uint8_t width, uint8_t height)
{
    _width = width;
    _height = height;
    LiquidCrystal_I2C _lcd(address, width, height);
}

void Display::generateCharacters()
{
    uint8_t duck[8] = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
    uint8_t lilypad[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
    uint8_t bell[8] = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
    uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
    uint8_t note[8] = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
    _lcd.createChar(0, duck);
    _lcd.createChar(1, lilypad);
}

void Display::showSplashScreen()
{
    _lcd.setCursor(1, 3);
    _lcd.print("Arduino Arcade");
    _lcd.setCursor(2, 3);
    _lcd.print("By Matthew Ouyang");
    delay(1000);
}