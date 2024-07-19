//
// Created by max on 10.07.24.
//

#ifndef FRESHMORTALFLAW_ENEMY_H
#define FRESHMORTALFLAW_ENEMY_H
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

    //getter methods
    Rect getRect() {return enmRect;}
    Hitbox getHitbox() {return eHitbox;}
    Rect * getClip(){return &clip;}
    [[nodiscard]] bool getAliveOrDead() const{return aliveOrDead;}
    [[nodiscard]] int getHP() const{return hp;}
    [[nodiscard]] int getID() const{return eID;}

    //setter methods
    void setXPos(int newX){ enmRect.x = newX;eHitbox.collisionRect.x = newX; }
    void setYPos(int newY){ enmRect.y = newY;eHitbox.collisionRect.y = newY; }
    void setWidth(int newW){ enmRect.w = newW; }
    void setHeight(int newH){ enmRect.h = newH;}
    void setRect(Rect newR){ enmRect = newR;}
    void setRect(int x,int y,int w,int h){ enmRect.x = x;enmRect.y = y;enmRect.w = w;enmRect.h = h;}
    void setClip(Rect newClip){clip = newClip;}
    void setVelocity(int newVx = 0,int newVy = 0){VelX = newVx;VelY = newVy;}
   // void setDebuff(int type){if(type == 1){ vulnerable = true;}}
    void setAlive(bool state){ aliveOrDead = state;}
    void setID(int newID){eID = newID; eHitbox.hitboxID = newID;}
    void setHP(int newHP){hp = newHP;}
    void setVulnerable(bool newV){vulnerable = newV;eHitbox.debuff = newV;}




    void move();
    void takeDamage(int damage);
    void killEnemyIfHP0();
    void resetID(){eID = respawnID;eHitbox.hitboxID = respawnID;}
    void resetHP(){hp = hpMax;}
    void respawn(int x,int y);
    void saveRespawnID();
    //sets the clip offset and adjusts the clip on the spritesheet to the new one
    void setClipOffset(int newOffset){clipOffset = newOffset; clip.x = clip.w *newOffset;}
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

    static int nextID;
    Hitbox eHitbox = {enmRect, eID};

    //------------stats

/// TODO add a enemy clipRect and SDL_Point for the x,y values

};



#endif //FRESHMORTALFLAW_ENEMY_H
