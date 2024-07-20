//
// Created by max on 11.07.24.
//


#include "Card_Dagger.h"

/** DESCRIPTION:
 * Daggers are a damaging ranged attack that deal 1 damage each.
 * On hitting the max targets based on current charge level it gains another level going from 1 to 4.
 * For each level it can pierce one more enemy. Making it both stronger and harder to level up.
 * It additionally recharges the draw ressource of the Player by one if maximum targets are hit.
 * On maximum level it activates applyDebuff and makes enemies vulnerable on hit. Then resets its level back to 1.
 *
 * The vulnerable debuff currently only interacts with Card_ForgeStrike but is planned to be expanded upon.
 * */

Card_Dagger::Card_Dagger(
        u8 dmg,
        u16 range,
        int squaredRange,
        Rect cardRect,
        Rect clip,
        Point startingPos,
        Point velocity)
                         : Card(dmg, range, squaredRange, 1, false, eFacingAngle::Up, cardRect, clip,
                                startingPos, velocity, 1, false, 0, eCardName::Dagger, 1,eChargeLevels::LVL0){
        this->squaredRange = this->range * this->range;

}
void Card_Dagger::castCard(eFacingAngle aim, Point startingPoint) {

    attackDirection = aim;

    //center of player sprite
    int centerX = startingPoint.x +  32/ 2;
    int centerY = startingPoint.y + 32/ 2;

    //center the middle of the attack on the middle of the player sprite
    Point centeredCardRect = {centerX -cardRect.w/2,centerY -cardRect.h/2};

    cardRect.x = centeredCardRect.x;
    cardRect.y = centeredCardRect.y;

    //using the center of the player as starting point looks fine for this card
    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;

    //card gains vulnerable on hit on charge level 3 then loses all charge after use
    if(currentChargeLevel == eChargeLevels::FULL){ applyDebuff = true;}
    if(currentChargeLevel == eChargeLevels::LVL0){ applyDebuff = false;}

    //set the card sprite to represent charge level
    Card::setSpritesheetClip(static_cast<int>(currentChargeLevel));

    //Dagger pierces more targets the more charge it has
    maxTargets = static_cast<int>(currentChargeLevel);
    //enum starts at 0 so we increase max targets by one to not hit infinite targets on LVL0
    maxTargets++;

    //if the charge is full reset it but leave applyDebuff on until the full charge finishes
    if(currentChargeLevel == eChargeLevels::FULL){ currentChargeLevel = eChargeLevels::LVL0;}

    ammo-- ;
    active = true;

}


int Card_Dagger::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {

    //saves the index of the hit element for that frame
    int hit = 0;
    if (active) {

        //its fine if it overlaps when colliding
        move();

        Point current = {cardRect.x, cardRect.y};
        double squaredDistanceTraveled = calculateSquaredDistance(startingPos, current);


        for (Hitbox e: colliderList) {

            // i forgot to adjust the hitbox based on angle.Requires a different Rect from cardRect to not stretch the visual. Maybe polish this later
            if (e.hitboxID != deadID) {
                if (SDL_HasIntersection(&cardRect,
                                        (const SDL_Rect *) &e)) {
                    //if not already hit during this projectiles lifetime
                    if (hitIDSet.find(e.hitboxID) == hitIDSet.end()) {
                        hitIDSet.insert(e.hitboxID);

                        if (hitIDSet.size() == maxTargets) {
                            active = false;
                            hitIDSet.clear();

                            //fully charged Dagger does not gain any charge back on hit
                            if(!applyDebuff) {
                                increaseCharge();
                            }
                            setSpritesheetClip(static_cast<int>(currentChargeLevel));
                            //give drawReady+1 to player if max targets based on charge level are hit
                            player->drawsReady++;
                            return hit;
                        }

                        if(!applyDebuff) {
                            increaseCharge();
                        }
                        setSpritesheetClip(static_cast<int>(currentChargeLevel));
                        //reaction to hit will be done in ::Update
                        return hit;
                    }


                }
            }
                hit++;

        }
        if (squaredDistanceTraveled >= squaredRange) {
            active = false;
            hitIDSet.clear();

            //if fully charged reset the charge and disable applyDebuff
            if(currentChargeLevel == eChargeLevels::LVL0 && applyDebuff){ applyDebuff = false;}
            setSpritesheetClip(static_cast<int>(currentChargeLevel));
            return notHitID;

        }
        return notHitID;
    }
    //only goes here if something is really weird is going on. Not throwing an error so i can debug live when i see this in the console
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -10;
}

void Card_Dagger::move() noexcept
{
    using std::round;
    // remember the y axis is inverted due to SDL when changing these
    switch(attackDirection) {
        case eFacingAngle::Right:
            cardRect.x += velocity.x;
            break;
        case eFacingAngle::Left:
            cardRect.x -= velocity.x;
            break;
        case eFacingAngle::Down:
            cardRect.y += velocity.y;
            break;
        case eFacingAngle::Up:
            cardRect.y -= velocity.y;
            break;
        case eFacingAngle::DownRight:
            cardRect.x += static_cast<int>(round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::DownLeft:
            cardRect.x -= static_cast<int>(round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::UpRight:
            cardRect.x += static_cast<int>(round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::UpLeft:
            cardRect.x -= static_cast<int>(round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(round(velocity.y * sqrt2_over_2));
            break;
    }
}

Card_Dagger::~Card_Dagger()= default;