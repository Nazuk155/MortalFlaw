//
// Created by max on 11.07.24.
//

#include <unordered_set>
#include "Card.h"


int Card::nextID = 1;

// Constructor implementation
Card::Card(u8 dmg,
           u16 range,
           int squaredRange,
           u8 ammo,
           bool act,
           eFacingAngle attackDirection,
           Rect cardRect,
           Rect clip,
           Point startingPos,
           Point velocity,
           int maxTargets,
           bool applyStatus,
           u8 state,
           eCardName cardName,
           int maxUses)

            : cID(nextID++),
              dmg(dmg),
              range(range),
              squaredRange(squaredRange),
              ammo(ammo),
              active(act),
              attackDirection(attackDirection),
              cardRect(cardRect),
              clip(clip),
              startingPos(startingPos),
              velocity(velocity),
              maxTargets(maxTargets),
              applyDebuff(applyStatus),
              state(state),
              cardName(cardName),
              maxUses(maxUses){}


Card::Card()
        : cID(nextID++), dmg(0), range(0), squaredRange(0), ammo(0), active(false) {}

void Card::setSpritesheetClip(int spriteNr) {
    clip.x = clip.w*spriteNr;

}


// Pure virtual destructor needs a definition
Card::~Card() = default;
