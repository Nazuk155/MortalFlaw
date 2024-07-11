//
// Created by max on 11.07.24.
//

#include "Card.h"



// Constructor implementation
Card::Card(u8 id, u8 dmg, u16 range, u8 use, bool act,Rect cardRect,Rect clip)
        : cID(id), dmg(dmg), range(range), uses(uses), active(active),cardRect(cardRect),clip(clip) {}

// Pure virtual destructor needs a definition
Card::~Card() {}
