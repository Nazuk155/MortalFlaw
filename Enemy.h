//
// Created by max on 10.07.24.
//
#pragma once
#include <global.h>

class Enemy{
public:

    Enemy();

    bool aliveOrDead = true;
    bool vulnerable;
    u32 vulnerableTimer = 0;
    u16 vulnerableDuration = 300;
    u32 hitReaction = 10;
    //saves the original spawn point
    Point originalSpawn;
    //the time the hit reaction is displayed
    u8 originalHitReactionTime = 10;

    [[nodiscard]] Rect getRect() {return enmRect;}
    [[nodiscard]] Hitbox getHitbox() {return eHitbox;}
    [[nodiscard]] Rect * getClip(){return &clip;}
    [[nodiscard]] bool getAliveOrDead() const{return aliveOrDead;}
    [[nodiscard]] int getHP() const{return hp;}
    [[nodiscard]] int getID() const{return eID;}

    void setXPos(int newX)noexcept{ enmRect.x = newX;eHitbox.collisionRect.x = newX; }
    void setYPos(int newY)noexcept{ enmRect.y = newY;eHitbox.collisionRect.y = newY; }
    void setWidth(int newW)noexcept{ enmRect.w = newW; }
    void setHeight(int newH)noexcept{ enmRect.h = newH;}
    void setRect(Rect newR)noexcept{ enmRect = newR;}
    void setRect(int x,int y,int w,int h)noexcept{ enmRect.x = x;enmRect.y = y;enmRect.w = w;enmRect.h = h;}
    void setClip(Rect newClip)noexcept{clip = newClip;}
    void setVelocity(int newVx = 0,int newVy = 0)noexcept{VelX = newVx;VelY = newVy;}
   // void setDebuff(int type){if(type == 1){ vulnerable = true;}}
    void setAlive(bool state)noexcept{ aliveOrDead = state;}
    void setID(int newID)noexcept{eID = newID; eHitbox.hitboxID = newID;}
    void setHP(int newHP)noexcept{hp = newHP;}
    void setVulnerable(bool newV)noexcept{vulnerable = newV;eHitbox.debuff = newV;}
    void setClipOffset(int newOffset) noexcept{clipOffset = newOffset; clip.x = clip.w *newOffset;}


    void move() noexcept;
    void takeDamage(int damage) noexcept;
    void killEnemyIfHP0() noexcept;
    void resetID() noexcept{eID = respawnID;eHitbox.hitboxID = respawnID;}
    void resetHP() noexcept{hp = hpMax;}
    void respawn(int x,int y) noexcept;
    void saveRespawnID() noexcept;
private:

    //stats
    int hp = 6;
    u8 hpMax = 6;


    Rect enmRect;
    Rect clip;
    int clipOffset;
    int VelX;
    int VelY;
    //gets changed to deadID in case of death
    int eID;
    //keeps the original id in case of respawns
    int respawnID;
    Hitbox eHitbox = {enmRect, eID};

//static
    static int nextID;
};