//
// Created by max on 10.07.24.
//

#include "Enemy.h"


Enemy::Enemy()
{
    EnmRect = {0,0,32,32};
    VelX = 0;
    VelY = 0;
}

Rect Enemy::getRect() {return EnmRect;}


void Enemy::move()
{
    //Move the Player left or right
    EnmRect.x += VelX;

    //If the Player went too far to the left or right
    if((EnmRect.x < 0 ) || (EnmRect.x + EnmRect.w > SCREEN_WIDTH ) )
    {
        //Move back
        EnmRect.x -= VelX;
    }

    //Move the Player up or down
    EnmRect.y += VelY;

    //If the Player went too far up or down
    if((EnmRect.y < 0 ) || (EnmRect.y + EnmRect.h > SCREEN_HEIGHT ) )
    {
        //Move back
        EnmRect.y -= VelY;
    }

}
