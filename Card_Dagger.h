//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_DAGGER_H
#define FRESHMORTALFLAW_CARD_DAGGER_H



#include "Card.h"

class Card_Dagger : public Card {
public:
    // Constructor

      explicit Card_Dagger(
                         u8 dmg = 1,
                         u16 range = 400,
                         int squaredRange = 0,
                         u8 uses = 3,
                         bool active = false,
                         Angle attackDirection = Angle::Up,
                         Rect cardRect ={0,0,12,49},
                         Rect clip = {0,0,12,49},
                         Point startingPos = {0,0},
                         Point velocity = {20,20});

    // Override the castCard method
    void castCard(Angle aim, Point startingPoint) override;
    int doWhileActive(const Vector<Rect>& colliderList) override;
    void move() override;
    ~Card_Dagger() override;
};




#endif //FRESHMORTALFLAW_CARD_DAGGER_H
