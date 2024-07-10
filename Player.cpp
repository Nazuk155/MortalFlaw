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
   collisionRect  = {PosX,PosY,PLAYER_WIDTH,PLAYER_HEIGHT};


}

void Player::handleEvent( SDL_Event& e )
{

//using enum Angle; too much time was wasted trying to get this to work.
//can not get this enum namespace to work in any way. I tried updating compilers and more. Alas my directions come with Angle:: for now

    //If a key was pressed

    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr );


    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_UP: VelY -= PLAYER_VEL;currentAngle =Angle::Up; break;
            case SDLK_DOWN: VelY += PLAYER_VEL;currentAngle =Angle::Down; break;
            case SDLK_LEFT: VelX -= PLAYER_VEL;currentAngle =Angle::Left; break;
            case SDLK_RIGHT: VelX += PLAYER_VEL;currentAngle =Angle::Right; break;
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
    if( currentKeyStates[ SDL_SCANCODE_UP ]&&currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        currentAngle=Angle::UpRight;
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ]&&currentKeyStates[SDL_SCANCODE_RIGHT] )
    {
        currentAngle=Angle::DownRight;
    }
    if( currentKeyStates[ SDL_SCANCODE_UP ]&&currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        currentAngle=Angle::UpLeft;
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ]&&currentKeyStates[SDL_SCANCODE_LEFT] )
    {
        currentAngle=Angle::DownLeft;
    }

}

/*
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: VelY -= PLAYER_VEL;activeFacingDirection +=Up;lastFacingDirection = activeFacingDirection;currentAngle +=Up; break;
        case SDLK_DOWN: VelY += PLAYER_VEL;activeFacingDirection +=Down;lastFacingDirection=activeFacingDirection; break;
        case SDLK_LEFT: VelX -= PLAYER_VEL;activeFacingDirection += Left;lastFacingDirection=activeFacingDirection; break;
        case SDLK_RIGHT: VelX += PLAYER_VEL;activeFacingDirection += Right;lastFacingDirection =activeFacingDirection; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: VelY += PLAYER_VEL;activeFacingDirection -=Up; break;
        case SDLK_DOWN: VelY -= PLAYER_VEL;activeFacingDirection -=Down; break;
        case SDLK_LEFT: VelX += PLAYER_VEL;activeFacingDirection -=Right; break;
        case SDLK_RIGHT: VelX -= PLAYER_VEL;activeFacingDirection -=Left; break;
        }
    }
}
*/
void Player::move(const Vector<Rect>& colliderList)
{
    //Move the Player left or right
    PosX += VelX;
    collisionRect.x += VelX;

    //If the Player went too far to the left or right and check collision list
    for(auto a:colliderList) {
        if ((PosX < 0) || (PosX + PLAYER_WIDTH > SCREEN_WIDTH) || SDL_HasIntersection(&collisionRect,&a)) {
            //Move back
            PosX -= VelX;
            collisionRect.x -= VelX;
        }
    }
    //Move the Player up or down and check collider list
    PosY += VelY;
    collisionRect.y += VelY;

    //If the Player went too far up or down and check collision list
    for(auto a:colliderList) {
        if ((PosY < 0) || (PosY + PLAYER_HEIGHT > SCREEN_HEIGHT)|| SDL_HasIntersection(&collisionRect,
                                                                                       (const SDL_Rect *) &a)) {
            //Move back
            PosY -= VelY;
            collisionRect.y -= VelY;
        }
    }


}
double Player::getFacingAngle() const {
    return static_cast<double>(static_cast<int>(currentAngle));
}


int Player::getXPos() const{return PosX;}
int Player::getYPos() const{return PosY;}
int Player::getWidth() const{return PLAYER_WIDTH;}
int Player::getHeight() const{return PLAYER_HEIGHT;}

Rect * Player::getCollisionRect() {return &collisionRect;}

