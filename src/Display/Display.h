#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class Display : public LiquidCrystal_I2C
{
    public:
        Display(uint8_t address, uint8_t width, uint8_t height);

        void generateCharacters();
        void showSplashScreen();

    private:
        int _width;
        int _height;
        LiquidCrystal_I2C _lcd;
};

#endif 