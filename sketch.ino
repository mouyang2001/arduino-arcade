#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "src/Joystick/Joystick.h"
#include "src/Player/Player.h"
#include "src/Obstacle/Obstacle.h"
#include "src/Display/Display.h"

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
#define LCD_ADDRESS 0x27

// Obstacle definitions.
#define NUM_OBSTACLES 10
#define OBSTACLE_START_X 5
#define OBSTACLE_MAX_WIDTH 3

// Character ids.
#define DUCK 0
#define LILYPAD 1
#define BELL 2
#define HEART 3

uint8_t duck[8] = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t lilypad[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t bell[8] = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};

unsigned const long OBSTACLE_DELAY = 1000;
unsigned long lastTimeObstacleDelay = 0;

unsigned const long PLAYER_DELAY = 100;
unsigned long lastTimePlayerDelay = 0;

LiquidCrystal_I2C lcd(LCD_ADDRESS, SCREEN_WIDTH, SCREEN_HEIGHT);
Joystick joyStick(JOY_X, JOY_Y, JOY_BTN, ANALOG_BUFFER, ANALOG_RESOLUTION);
Player player(PLAYER_START_X, PLAYER_START_Y);
Obstacle obstacles[NUM_OBSTACLES];

void setup()
{
    lcd.init();
    lcd.backlight();

    initializeObstacles();
    gameStart();
}

void createCharacters()
{
    lcd.createChar(0, duck);
    lcd.createChar(1, lilypad);
    lcd.createChar(2, bell);
    lcd.createChar(3, heart);
}

void loop()
{
    if ((millis() - lastTimeObstacleDelay) > OBSTACLE_DELAY)
    {
        lastTimeObstacleDelay = millis();

        updateObstacles();
        updateScore();
    }

    if ((millis() - lastTimePlayerDelay) > PLAYER_DELAY)
    {
        lastTimePlayerDelay = millis();

        playerMovementHandler();
    }

    collisionCheck();
}

/* --------------- Scenes --------------- */
void gameStart() {
    while (!joyStick.isPressed()) {
        lcd.setCursor(5, 1);
        lcd.print("Duck Run ");
        lcd.write(DUCK);
        lcd.setCursor(2, 2);
        lcd.print("> press to play");
    }
    lcd.clear();
}

void gameOver()
{
    lcd.clear();
    while(true) {
        lcd.setCursor(5, 1);
        lcd.print("GAME OVER!");
        lcd.setCursor(5, 2);
        lcd.print("Score: ");
        lcd.print(player.getScore());
    }
}

/* --------------- Collision --------------- */
void collisionCheck()
{
    int playerX = player.getX();
    int playerY = player.getY();

    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        int obstacleX = obstacles[i].getX();
        int obstacleY = obstacles[i].getY();
        if (obstacleX == playerX && obstacleY == playerY)
        {
            gameOver();
        }
    }
}

/* --------------- Obstacles --------------- */
void initializeObstacles()
{
    for (int i = 0; i < NUM_OBSTACLES; i++)
    {
        obstacles[i].setPosition(random(OBSTACLE_START_X, SCREEN_WIDTH), random(0, SCREEN_HEIGHT));
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
        lcd.setCursor(x, y);
        lcd.write(' ');
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

/* --------------- Score --------------- */
void updateScore()
{
    player.increaseScore();
    lcd.setCursor(17, 0);
    lcd.print(player.getScore());
}

/* --------------- Player --------------- */
void playerMovementHandler()
{
    Joystick::Direction direction = joyStick.getDirection();
    Serial.println("Direction: " + String(direction));

    if (direction != Joystick::Direction::NONE)
    {
        unrenderPlayer();
    }

    if (direction == Joystick::Direction::UP)
        player.moveUp();
    else if (direction == Joystick::Direction::DOWN)
        player.moveDown();
    else if (direction == Joystick::Direction::LEFT)
        player.moveLeft();
    else if (direction == Joystick::Direction::RIGHT)
        player.moveRight();

    renderPlayer();
}

void unrenderPlayer() {
    lcd.setCursor(player.getX(), player.getY());
    lcd.write(' ');
}

void renderPlayer()
{
    lcd.setCursor(player.getX(), player.getY());
    lcd.write(DUCK);
}
