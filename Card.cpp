//
// Created by max on 11.07.24.
//

#include <unordered_set>
#include "Card.h"



// Constructor implementation
Card::Card(u8 id, u8 dmg, u16 range, int squaredRange, u8 use, bool act, Angle attackDirection, Rect cardRect,
           Rect clip,
           Point startingPos, Point velocity):cID(id),dmg(dmg),range(range),squaredRange(squaredRange),uses(use),active(act),attackDirection(attackDirection),
                                              cardRect(cardRect),clip(clip), startingPos(startingPos),velocity(velocity) {}

Card::Card() = default;

// Pure virtual destructor needs a definition
Card::~Card() = default;
