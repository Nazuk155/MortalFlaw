//
// Created by max on 11.07.24.
//

#include "Card.h"


int Card::nextID = 1;

Card::Card(u8 dmg,
           u16 range,
           int squaredRange,
           u8 ammo,
           bool active,
           eFacingAngle attackDirection,
           Rect cardRect,
           Rect clip,
           Point startingPos,
           Point velocity,
           int maxTargets,
           bool applyDebuff,
           u8 clipOffset,
           eCardName cardName,
           int maxUses,
           eChargeLevels currentChargeLevel)

            : cID(nextID++),
              dmg(dmg),
              range(range),
              squaredRange(squaredRange),
              ammo(ammo),
              active(active),
              attackDirection(attackDirection),
              cardRect(cardRect),
              clip(clip),
              startingPos(startingPos),
              velocity(velocity),
              maxTargets(maxTargets),
              applyDebuff(applyDebuff),
              clipOffset(clipOffset),
              cardName(cardName),
              maxUses(maxUses),
              currentChargeLevel(currentChargeLevel){}



void Card::setSpritesheetClip(int spriteNr) noexcept {
    clip.x = clip.w*spriteNr;
    clipOffset = spriteNr;
}

void Card::increaseCharge() noexcept
{

    switch(currentChargeLevel)
    {
        case eChargeLevels::LVL0:currentChargeLevel = eChargeLevels::LVL1;break;
        case eChargeLevels::LVL1:currentChargeLevel = eChargeLevels::LVL2;break;
        case eChargeLevels::LVL2:currentChargeLevel = eChargeLevels::FULL;break;
        case eChargeLevels::FULL: break;
    }
}

Card::~Card() = default;
