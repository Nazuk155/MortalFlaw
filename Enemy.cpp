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

    vulnerable = false;
}

void Enemy::respawn(int x, int y) noexcept
{
    enmRect.x = x;
    enmRect.y = y;
    eHitbox.collisionRect.x = x;
    eHitbox.collisionRect.y = y;
    resetHP();
    resetID();
    aliveOrDead = true;
    vulnerable = false;
    setVulnerable(false);
    vulnerableTimer = 0;
}
void Enemy::saveRespawnID() noexcept {respawnID = eID;}

void Enemy::takeDamage(int damage) noexcept
{
    hp -= damage;
}

void Enemy::killEnemyIfHP0()noexcept
{
    if(hp <= 0){ aliveOrDead = false;eID = deadID;eHitbox.hitboxID = deadID;};
}

void Enemy::move() noexcept
{
    enmRect.x += VelX;
    eHitbox.collisionRect.x += VelX;

    if((enmRect.x < 0 ) || (enmRect.x + enmRect.w > SCREEN_WIDTH ) )
    {
        enmRect.x -= VelX;
        eHitbox.collisionRect.x -= VelX;
    }

    enmRect.y += VelY;
    eHitbox.collisionRect.y += VelY;

    if((enmRect.y < 0 ) || (enmRect.y + enmRect.h > SCREEN_HEIGHT ) )
    {
        enmRect.y -= VelY;
        eHitbox.collisionRect.y -= VelY;
    }

}
