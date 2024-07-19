//
// Created by max on 18.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_FORGESTRIKE_H
#define FRESHMORTALFLAW_CARD_FORGESTRIKE_H

#include "Card.h"
#include <unordered_set>



class Card_ForgeStrike: public Card {
private:
    int enhancedDamage;
    static void reforge(Player * player);
public:
    // Constructor

    explicit Card_ForgeStrike(
            u8 dmg = 1,
            u16 range = 100,
            int squaredRange = 0,
            u8 ammo = 1,
            bool active = false,
            eFacingAngle attackDirection = eFacingAngle::Up,
            Rect cardRect ={0,0,64,64},
            Rect clip = {0,0,64,64},
            Point startingPos = {0,0},
            Point velocity = {0,0},
            int maxTargets = 3,
            bool applyStatus = false,
            u8 state = 0,
            eCardName name = eCardName::ForgeStrike,
            int maxUses = 1,
            int conditionalDamage = 5);

    // Override the castCard method
    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move() override;
    ~Card_ForgeStrike() override;


};







#endif //FRESHMORTALFLAW_CARD_FORGESTRIKE_H
