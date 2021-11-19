#ifndef Coin_h
#define Coin_h

#include "Arduino.h"

class Coin
{
    public:
        Coin() {};
        Coin(int x, int y);
        void setPosition(int x, int y);
        int getX();
        int getY();

    private:
        int _posX;
        int _posY;
};

#endif 