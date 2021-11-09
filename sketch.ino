#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "src/Joystick/Joystick.h"
#include "src/Player/Player.h"

// Joystick definitions.
#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 13
#define ANALOG_BUFFER 480
#define ANALOG_RESOLUTION 1024

// Player definitions.
#define PLAYER_START_X 0
#define PLAYER_START_Y 1

// LCD screen definitions.
#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 4
#define LCD_PINS 0x27

// Character ids.
#define DUCK 0
#define LILYPAD 1

// Custom characters.
// e.g {0,1,1,1,0} => 0xe
uint8_t duck[8] = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t lilypad[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t bell[8] = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t note[8] = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};

LiquidCrystal_I2C lcd(LCD_PINS, SCREEN_WIDTH, SCREEN_HEIGHT);
Joystick joyStick(JOY_X, JOY_Y, JOY_BTN, ANALOG_BUFFER, ANALOG_RESOLUTION);
Player player(PLAYER_START_X, PLAYER_START_Y);

void lcdCreateCharacters()
{
    lcd.createChar(0, duck);
    lcd.createChar(1, lilypad);
    lcd.createChar(2, bell);
    lcd.createChar(3, heart);
    lcd.createChar(4, note);
}

void setup()
{
    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    lcdCreateCharacters();
}

void loop()
{
    joyStick.debug();
    render();
    playerMovementHandler();
    delay(200);
}

void playerMovementHandler()
{
    Joystick::Direction direction = joyStick.getDirection();
    Serial.println("Direction: " + String(direction));
    if (direction == Joystick::Direction::UP)
        player.moveUp();
    else if (direction == Joystick::Direction::DOWN)
        player.moveDown();
    else if (direction == Joystick::Direction::LEFT)
        player.moveLeft();
    else if (direction == Joystick::Direction::RIGHT)
        player.moveRight();
}

/**
 * @brief Render various game elements on the LCD screen. Order matters for layers.
 */
void render()
{
    lcd.clear();
    renderPlayer();
    renderObstacles();
    renderScore();
}

void renderObstacles()
{
    // TODO: render obstacles.
}

void renderPlayer()
{
    lcd.setCursor(player.getX(), player.getY());
    lcd.write(DUCK);
}

void renderScore()
{
    lcd.setCursor(17, 0);
    // TODO: score tracker.
    lcd.print("021");
}