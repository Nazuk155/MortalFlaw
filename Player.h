//
// Created by max on 01.07.24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <global.h>
#include "AngleHelper.h"

class Player
{
public:
    //The dimensions of the dot
      int PLAYER_WIDTH = 32;
      int PLAYER_HEIGHT = 32;

    //Maximum axis velocity of the dot
    constexpr static const int PLAYER_VEL = 5;

    // _playerRect;
    //Initializes the variables
    Player();


    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move(const Vector<Rect>& colliderList);

    //returns angle for rendering rotated sprites based on lastfacingDirection
    [[nodiscard]] double getFacingAngle() const;

    [[nodiscard]] int getXPos() const;
    [[nodiscard]] int getYPos() const;
     [[nodiscard]] int getWidth() const;
     [[nodiscard]] int getHeight() const;
     u16 getActiveFacingDirection();
     Rect * getCollisionRect();
     void setXPos(int newX){ PosX = newX; }
     void setYPos(int newY){ PosY = newY; }
     void setWidth(int newW){ PLAYER_WIDTH = newW; }
     void setHeight(int newH){ PLAYER_HEIGHT = newH;}
     void setVelocity(int newVx = 0,int newVy = 0){VelX = newVx;VelY = newVy;}

private:
    //The X and Y offsets of the dot
    int PosX, PosY;

    //The velocity of the dot
    int VelX, VelY;
    //Collision Box
     SDL_Rect collisionRect;
     //define enum of facing direction of player

    Angle currentAngle;

  //  enum direction{Up= 1,Right = 10,Down =100,Left= 1000,UpRight = 11,DownRight = 110, DownLeft = 1100,UpLeft = 1001,UpDown = 0,LeftRight = 0,All = 0};
    //direction the player is facing during movement
    u16 activeFacingDirection;
    //direction player is facing after movement buttons are released
    u16 lastFacingDirection = 0;


};




#endif //PLAYER_H
