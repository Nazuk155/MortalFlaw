//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_DAGGER_H
#define FRESHMORTALFLAW_CARD_DAGGER_H



#include "Card.h"

class Card_Dagger : public Card {
public:
    // Constructor
    explicit Card_Dagger(u8 cID =1,
                         u8 dmg = 1,
                         u16 range = 400,
                         u8 uses = 3,
                         bool active = false,
                         Rect cardRect ={0,0,12,49}
                         ,Rect clip = {0,0,12,49});

    // Override the castCard method
    void castCard() override;
    void doWhenActive(const Vector<Rect>& colliderList,Angle ang);
    ~Card_Dagger() override;
};




#endif //FRESHMORTALFLAW_CARD_DAGGER_H
