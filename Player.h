//
// Created by max on 01.07.24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <global.h>

class Player
{
public:
    //The dimensions of the dot
     const int PLAYER_WIDTH = 20;
     const int PLAYER_HEIGHT = 20;




    //Maximum axis velocity of the dot
    constexpr static const int PLAYER_VEL = 5;

    Rect _playerRect;
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move();

    //Shows the dot on the screen
    //Point getRenderPos();

    [[nodiscard]] int getXPos() const;
    [[nodiscard]] int getYPos() const;
     int getWidth();
     int getHeight();

     ///not sure about this
     Rect& getRect(){return _playerRect;}
private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;

    //The velocity of the dot
    int mVelX, mVelY;

};




#endif //PLAYER_H
