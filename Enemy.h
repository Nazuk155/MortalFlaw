//
// Created by max on 10.07.24.
//

#ifndef FRESHMORTALFLAW_ENEMY_H
#define FRESHMORTALFLAW_ENEMY_H
#include <global.h>

class Enemy{
public:

    Enemy();

    //Enemy has a Rect for its values. This inconsistency is just to test if either approach has any real advantages.
    Rect getRect();

    //setter methods for utility
    void setXPos(int newX){ EnmRect.x = newX; }
    void setYPos(int newY){ EnmRect.y = newY; }
    void setWidth(int newW){ EnmRect.w = newW; }
    void setHeight(int newH){ EnmRect.h = newH; }
    void setRect(Rect newR){ EnmRect = newR;}
    void setRect(int x,int y,int w,int h){EnmRect.x = x;EnmRect.y = y;EnmRect.w = w;EnmRect.h = h;}


private:
    Rect EnmRect;
    int VelX;
    int VelY;


};



#endif //FRESHMORTALFLAW_ENEMY_H
