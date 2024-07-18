//
// Created by max on 15.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_SWORD_H
#define FRESHMORTALFLAW_CARD_SWORD_H

//
// Created by max on 15.07.24.
//

#include "Card.h"
#include <unordered_set>


class Card_Sword : public Card {
public:
    // Constructor

    explicit Card_Sword(
            u8 dmg = 2,
            u16 range = 100,
            int squaredRange = 0,
            u8 ammo = 3,
            bool active = false,
            eFacingAngle attackDirection = eFacingAngle::Up,
            //stretched from original sprite for visual effect
            Rect cardRect ={0,0,96,96},
            Rect clip = {0,0,64,25},
            Point startingPos = {0,0},
            Point velocity = {20,20},
            int maxTargets = 3,
            bool applyStatus = false,
            u8 state = 0,
            eCardName name = eCardName::Sword,
            int maxUses = 3);

    // Override the castCard method
    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move() override;
    ~Card_Sword() override;
};






#endif //FRESHMORTALFLAW_CARD_SWORD_H
