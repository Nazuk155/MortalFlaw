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
      int PLAYER_WIDTH = 20;
      int PLAYER_HEIGHT = 20;




    //Maximum axis velocity of the dot
    constexpr static const int PLAYER_VEL = 5;

    // _playerRect;
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move();



    [[nodiscard]] int getXPos() const;
    [[nodiscard]] int getYPos() const;
     int getWidth() const;
     int getHeight() const;
     void setXPos(int newX){ PosX = newX; }
     void setYPos(int newY){ PosY = newY; }
    void setWidth(int newW){ PLAYER_WIDTH = newW; }
    void setHeight(int newH){ PLAYER_HEIGHT = newH; }

private:
    //The X and Y offsets of the dot
    int PosX, PosY;

    //The velocity of the dot
    int VelX, VelY;


};




#endif //PLAYER_H
