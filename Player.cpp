//
// Created by max on 01.07.24.
//

#include "Player.h"



Player::Player()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    //Point pos {mPosX,mPosY};
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    _playerRect = {mPosX,mPosY,PLAYER_WIDTH,PLAYER_HEIGHT};

    //Not a good idea to have a rect for every instance of the object. Try to keep visual and data apart!
    //SDL_Rect renderQuad = { mPosX, mPosY, PLAYER_WIDTH, PLAYER_HEIGHT };
}

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: mVelY -= PLAYER_VEL; break;
        case SDLK_DOWN: mVelY += PLAYER_VEL; break;
        case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
        case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: mVelY += PLAYER_VEL; break;
        case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
        case SDLK_LEFT: mVelX += PLAYER_VEL; break;
        case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
        }
    }
}

void Player::move()
{
    //Move the Player left or right
    mPosX += mVelX;

    //If the Player went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the Player up or down
    mPosY += mVelY;

    //If the Player went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
}


int Player::getXPos() const{return mPosX;}
int Player::getYPos() const{return mPosY;}
int Player::getWidth(){return PLAYER_WIDTH;}
int Player::getHeight(){return PLAYER_HEIGHT;}
