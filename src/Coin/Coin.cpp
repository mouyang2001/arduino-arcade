#include "COin.h"
#include "Arduino.h"

Coin::Coin(int x, int y) {
    _posX = x;
    _posY = y;
}

int Coin::getX() {
    return _posX;
}

int Coin::getY() {
    return _posY;
}

void Coin::setPosition(int x, int y) {
    _posX = x;
    _posY = y;
}