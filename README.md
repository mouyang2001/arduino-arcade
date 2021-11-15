# Arduino Arcade
My Arduino embedded software project written in c++.

Project aims to implement classic arcade games and more playable on the arduino with a joystick and LCD screen.

# How to install
Firstly you will need an analog Joystick and LCD width I2C module.

Then install the LiquidCrystal_I2C[https://github.com/johnrickman/LiquidCrystal_I2C] by Frank de Brabander to interface with a I2C LCD module.

Adjust PIN constants accordingly to your setup:

```
#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 13
#define LCD_PINS 0x27
```

Then upload sketch.ino to the arduino uno. Have fun!
