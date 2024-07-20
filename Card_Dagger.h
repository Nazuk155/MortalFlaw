//
// Created by max on 11.07.24.
//

#pragma once


#include "Card.h"
#include <Player.h>
#include <unordered_set>



class Card_Dagger : public Card {
private:
public:

      explicit Card_Dagger(
              u8 dmg = 1,
              u16 range = 400,
              int squaredRange = 0,
              Rect cardRect ={0,0,12,49},
              Rect clip = {0,0,12,49},
              Point startingPos = {0,0},
              Point velocity = {20,20});


    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move()noexcept override;
    ~Card_Dagger() override;

};