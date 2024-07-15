//
// Created by max on 11.07.24.
//

#include <unordered_set>
#include "Card.h"


int Card::nextID = 1;

// Constructor implementation
Card::Card( u8 dmg, u16 range, int squaredRange, u8 use, bool act, Angle attackDirection, Rect cardRect,
           Rect clip,
           Point startingPos, Point velocity):cID(nextID++),dmg(dmg),range(range),squaredRange(squaredRange),uses(use),active(act),attackDirection(attackDirection),
                                              cardRect(cardRect),clip(clip), startingPos(startingPos),velocity(velocity) {}

Card::Card()
        : cID(nextID++), dmg(0), range(0), squaredRange(0), uses(0), active(false) {}



// Pure virtual destructor needs a definition
Card::~Card() = default;
