#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "src/Joystick/Joystick.h"
#include "src/Player/Player.h"
#include "src/Obstacle/Obstacle.h"

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

// Obstacle definitions.
#define NUM_OBSTACLES 12
#define OBSTACLE_START_X 4
#define OBSTACLE_MAX_WIDTH 3

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

unsigned long lastObstacleDelayTime = 0;
unsigned long obstacleDelay = 1000;

unsigned long lastPlayerDelayTime = 0;
unsigned long playerDelay = 100;

int score = 0;

LiquidCrystal_I2C lcd(LCD_PINS, SCREEN_WIDTH, SCREEN_HEIGHT);
Joystick joyStick(JOY_X, JOY_Y, JOY_BTN, ANALOG_BUFFER, ANALOG_RESOLUTION);
Player player(PLAYER_START_X, PLAYER_START_Y);
Obstacle obstacles[NUM_OBSTACLES];

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
    lcd.init();
    lcd.backlight();

    lcdCreateCharacters();
    initializeObstacles();
}

void loop()
{
    // Game obstacles move and render in 1 second beats.
    // TODO make it so we only render obstacles that are in the screen rather than player.
    if ((millis() - lastObstacleDelayTime) > obstacleDelay)
    {
        lastObstacleDelayTime = millis();

        updateObstacles();
        updateScore();
    }

    if ((millis() - lastPlayerDelayTime) > playerDelay)
    {
        lastPlayerDelayTime = millis();

        renderPlayer();
        playerMovementHandler();
    }
}

/* --------------- Obstacles --------------- */
void initializeObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        obstacles[i].setPosition(random(OBSTACLE_START_X, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
        obstacles[i].setSize(random(1, OBSTACLE_MAX_WIDTH), 1);
    }
}

void updateObstacles()
{
    unrenderObstacles();
    moveObstacles();
    renderObstacles();
}

void moveObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        int newX = obstacles[i].getX() - 1;

        // If off screen, reset to end of screen.
        if (newX == -1)
        {
            newX = SCREEN_WIDTH - 1;
            obstacles[i].setY(random(0, SCREEN_HEIGHT));
        }

        obstacles[i].setX(newX);
    }
}

void unrenderObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        int x = obstacles[i].getX();
        int y = obstacles[i].getY();
        int width = obstacles[i].getWidth();
        lcd.setCursor(x, y);
        for (int j = 0; j < width; j++)
        {
            lcd.write(' ');
        }
    }
}

void renderObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        Obstacle obstacle = obstacles[i];
        lcd.setCursor(obstacle.getX(), obstacle.getY());
        lcd.write(LILYPAD);
    }
}

/* --------------- Scoring --------------- */
void updateScore()
{
    score++;
    renderScore();
}

void renderScore()
{
    // TODO improve positioning of score.
    // This could be done by finding the number of digits in the score.
    lcd.setCursor(17, 0);
    lcd.print(score);
}

/* --------------- Player --------------- */
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

void renderPlayer()
{
    lcd.setCursor(player.getX(), player.getY());
    lcd.write(DUCK);
}
