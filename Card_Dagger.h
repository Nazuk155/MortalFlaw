//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_DAGGER_H
#define FRESHMORTALFLAW_CARD_DAGGER_H



#include "Card.h"
#include <Player.h>
#include <unordered_set>


class Card_Dagger : public Card {
public:
    // Constructor

      explicit Card_Dagger(
              u8 dmg = 1,
              u16 range = 400,
              int squaredRange = 0,
              u8 ammo = 1,
              bool active = false,
              eFacingAngle attackDirection = eFacingAngle::Up,
              Rect cardRect ={0,0,12,49},
              Rect clip = {0,0,12,49},
              Point startingPos = {0,0},
              Point velocity = {20,20},
              int maxTargets = 1,
              bool applyStatus = false,
              u8 state = 1,
              eCardName name = eCardName::Dagger,
              int maxUses = 1);

    // Override the castCard method
    void castCard(eFacingAngle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) override;
    void move() override;
    ~Card_Dagger() override;
};




#endif //FRESHMORTALFLAW_CARD_DAGGER_H
