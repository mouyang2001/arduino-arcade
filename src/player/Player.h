#ifndef Player_h
#define Player_h

#include "Arduino.h"

/**
 * @brief Player class object for lcd game. 
 * @author Matthew Ouyang.
 * @date 10/11/2021.
 */
class Player
{
public:
    Player() {};
    Player(int x, int y);

    int getX();
    int getY();
    int getScore();
    int getLives();

    void setPosition(int x, int y);
    void increaseScore();
    void reduceLives();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void clearScore();
    void addScore(int score);

private:
    int _posX;
    int _posY;
    int _score = 0;
    int life = 3;
};

#endif