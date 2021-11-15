#include "Obstacle.h"
#include "Arduino.h"

Obstacle::Obstacle(int x, int y, int width, int height)
{
    _posX = x;
    _posY = y;
    _width = width;
    _height = height;
}

int Obstacle::getX()
{
    return _posX;
}

int Obstacle::getY()
{
    return _posY;
}

int Obstacle::getWidth()
{
    return _width;
}

int Obstacle::getHeight()
{
    return _height;
}

void Obstacle::setX(int x)
{
    _posX = x;
}

void Obstacle::setY(int y)
{
    _posY = y;
}

void Obstacle::setPosition(int x, int y) 
{
    _posX = x;
    _posY = y;
}

void Obstacle::setSize(int width, int height)
{
    _width = width;
    _height = height;
}