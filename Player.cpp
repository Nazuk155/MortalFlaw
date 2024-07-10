//
// Created by max on 01.07.24.
//

#include "Player.h"



Player::Player()
{
    ///needs inventory/deck, current hand pointers, facing direction,stats like hp etc.,

    //Initialize the offsets
    PosX = 0;
    PosY = 0;

    //Initialize the velocity
    VelX = 0;
    VelY = 0;
   // _playerRect = {PosX,PosY,PLAYER_WIDTH,PLAYER_HEIGHT};


}

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: VelY -= PLAYER_VEL; break;
        case SDLK_DOWN: VelY += PLAYER_VEL; break;
        case SDLK_LEFT: VelX -= PLAYER_VEL; break;
        case SDLK_RIGHT: VelX += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: VelY += PLAYER_VEL; break;
        case SDLK_DOWN: VelY -= PLAYER_VEL; break;
        case SDLK_LEFT: VelX += PLAYER_VEL; break;
        case SDLK_RIGHT: VelX -= PLAYER_VEL; break;
        }
    }
}

void Player::move()
{
    //Move the Player left or right
    PosX += VelX;

    //If the Player went too far to the left or right
    if((PosX < 0 ) || (PosX + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        PosX -= VelX;
    }

    //Move the Player up or down
    PosY += VelY;

    //If the Player went too far up or down
    if((PosY < 0 ) || (PosY + PLAYER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        PosY -= VelY;
    }
}


int Player::getXPos() const{return PosX;}
int Player::getYPos() const{return PosY;}
int Player::getWidth() const{return PLAYER_WIDTH;}
int Player::getHeight() const{return PLAYER_HEIGHT;}

