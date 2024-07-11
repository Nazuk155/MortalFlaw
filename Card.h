//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_H
#define FRESHMORTALFLAW_CARD_H
#include "global.h"
#include "AngleHelper.h"

#ifndef CARD_H
#define CARD_H

class Card {
public:
    // Attributes
    u8 cID;
    u8 dmg;
    u16 range;
    u8 uses;
    bool active;
    Rect cardRect;
    Rect clip;
    // Constructor
    Card(u8 cID, u8 dmg, u16 range, u8 uses, bool active,Rect cardRect,Rect clip);

    // Virtual destructor
    virtual ~Card() = 0;  // Pure virtual destructor

    // Pure virtual function to be overridden by derived classes
    virtual void castCard() = 0;
};

#endif // CARD_H




#endif //FRESHMORTALFLAW_CARD_H
