#ifndef Obstacle_h
#define Obstacle_h

#include "Arduino.h"

class Obstacle
{
    public: 
        Obstacle() { };
        Obstacle(int x, int y, int width, int height);
        int getX();
        int getY();
        int getWidth();
        int getHeight();

        void setX(int x);
        void setY(int y);
        void setPosition(int x, int y);
        void setSize(int width, int height);

    private:
        int _posX;
        int _posY;
        int _width;
        int _height;
};

#endif 