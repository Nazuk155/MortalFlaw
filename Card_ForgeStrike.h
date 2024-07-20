//
// Created by max on 18.07.24.
//

#pragma once

#include "Card.h"
#include <unordered_set>



class Card_ForgeStrike: public Card {
private:
    int enhancedDamage;
    void reforge(Player * player);
public:

    explicit Card_ForgeStrike(
            u8 dmg = 3,
            Rect cardRect ={0,0,64,64},
            Rect clip = {192,0,64,64},
            int maxTargets = 3,
            int enhancedDamage = 6);

    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move()noexcept override;
    ~Card_ForgeStrike() override;


};