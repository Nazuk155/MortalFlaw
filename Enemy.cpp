//
// Created by max on 10.07.24.
//

#include "Enemy.h"

int Enemy::nextID = 1;

Enemy::Enemy()
{
    enmRect = {0, 0, 32, 32};
    clip = {128,0,64,64};
    VelX = 0;
    VelY = 0;
    eID = nextID++;
    saveRespawnID();
    eHitbox = {enmRect, eID};
    originalSpawn = {enmRect.x,enmRect.y};

    burn = false;
}

void Enemy::respawn(int x, int y)
{
    enmRect.x = x;
    enmRect.y = y;
    eHitbox.collisionRect.x = x;
    eHitbox.collisionRect.y = y;
    resetHP();
    resetID();
    aliveOrDead = true;
    burn = false;
}
void Enemy::saveRespawnID() {respawnID = eID;}

void Enemy::takeDamage(int damage)
{
    hp -= damage;
}

void Enemy::killEnemyIfHP0()
{
    if(hp <= 0){ aliveOrDead = false;eID = deadID;eHitbox.hitboxID = deadID;};
}

void Enemy::move()
{
    //Move the Player left or right
    enmRect.x += VelX;
    eHitbox.collisionRect.x += VelX;

    //If the Player went too far to the left or right
    if((enmRect.x < 0 ) || (enmRect.x + enmRect.w > SCREEN_WIDTH ) )
    {
        //Move back
        enmRect.x -= VelX;
        eHitbox.collisionRect.x -= VelX;
    }

    //Move the Player up or down
    enmRect.y += VelY;
    eHitbox.collisionRect.y += VelY;

    //If the Player went too far up or down
    if((enmRect.y < 0 ) || (enmRect.y + enmRect.h > SCREEN_HEIGHT ) )
    {
        //Move back
        enmRect.y -= VelY;
        eHitbox.collisionRect.y -= VelY;
    }

}
