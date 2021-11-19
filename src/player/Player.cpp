#include "Arduino.h"
#include "Player.h"

/**
 * @brief Construct a new Player:: Player object.
 * 
 * @param x initial x position.
 * @param y initial y position.
 */
Player::Player(int x, int y)
{
    _posX = x;
    _posY = y;
}

int Player::getX()
{
    return _posX;
}

int Player::getY()
{
    return _posY;
}

int Player::getScore()
{
    return _score;
}

int Player::getLives()
{
    return life;
}

void Player::reduceLives()
{
    life--;
}

void Player::increaseScore()
{
    _score++;
}

void Player::moveUp()
{
    if (_posY > 0)
    {
        _posY--;
    }
}

void Player::moveDown()
{
    if (_posY < 3)
    {
        _posY++;
    }
}

void Player::moveRight()
{
    if (_posX < 19)
    {
        _posX++;
    }
}

void Player::moveLeft()
{
    if (_posX > 0)
    {
        _posX--;
    }
}

void Player::setPosition(int x, int y)
{
    _posX = x;
    _posY = y;
}

void Player::clearScore()
{
    _score = 0;
}

/**
 * @brief Add certain amount of points to the player's score
 * 
 * @param score number of points to add. 
 */
void Player::addScore(int score)
{
    _score += score;
}