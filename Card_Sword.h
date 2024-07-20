//
// Created by max on 15.07.24.
//

#pragma once
#include "Card.h"
#include <unordered_set>


class Card_Sword : public Card {
private:
bool enhancedStrikeActive = false;
public:

    explicit Card_Sword(
            u8 dmg = 2,
            u16 range = 100,
            int squaredRange = 1000,
            u8 ammo = 3,
            //stretched from original sprite for visual effect
            Rect cardRect ={0,0,96,96},
            Rect clip = {0,0,64,25},
            Point startingPos = {0,0},
            Point velocity = {20,20},
            int maxTargets = 3,
            int maxUses = 3,
            bool enhancedStrikeReady = false);

    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move() noexcept override;
    ~Card_Sword() override;
};