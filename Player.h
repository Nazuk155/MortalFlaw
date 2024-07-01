//
// Created by max on 01.07.24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <global.h>

#include "LTexture.h"

class Player
{
public:
    //The dimensions of the dot
    static const int PLAYER_WIDTH = 20;
    static const int PLAYER_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int PLAYER_VEL = 10;

    //Initializes the variables
    Player();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render(LTexture texture);

private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The velocity of the dot
    int mVelX, mVelY;
};




#endif //PLAYER_H
