//
// Created by max on 10.07.24.
//

#include "Enemy.h"

int Enemy::nextID = 1;

Enemy::Enemy()
{
    EnmRect = {0,0,32,32};
    clip = {0,0,64,64};
    VelX = 0;
    VelY = 0;
    eID = nextID++;
    eHitbox = {EnmRect,eID};

    burn = false;
}

Rect Enemy::getRect() {return EnmRect;}
int Enemy::getID() const {return eID;}
Hitbox Enemy::getHitbox() {return eHitbox;}

void Enemy::move()
{
    //Move the Player left or right
    EnmRect.x += VelX;
    eHitbox.collisionRect.x += VelX;

    //If the Player went too far to the left or right
    if((EnmRect.x < 0 ) || (EnmRect.x + EnmRect.w > SCREEN_WIDTH ) )
    {
        //Move back
        EnmRect.x -= VelX;
        eHitbox.collisionRect.x -= VelX;
    }

    //Move the Player up or down
    EnmRect.y += VelY;
    eHitbox.collisionRect.y += VelY;

    //If the Player went too far up or down
    if((EnmRect.y < 0 ) || (EnmRect.y + EnmRect.h > SCREEN_HEIGHT ) )
    {
        //Move back
        EnmRect.y -= VelY;
        eHitbox.collisionRect.y -= VelY;
    }

}
