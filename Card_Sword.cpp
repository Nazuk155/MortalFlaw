//
// Created by max on 11.07.24.
//


#include "Card_Sword.h"

/** DESCRIPTION
 * Sword is a close range cleaving attack dealing 2 damage. It can be used up to 3 times before it goes to discard.
 * If it hits no enemies it immediately loses all ammo and gets discarded.
 * If it hits 3 targets it upgrades the next level represented by the color of the visual changing.
 * It has 4 charge levels and the last one resets it back to 0.
 * At max charge it gives up to 2 drawReady tokens to the player.
 * It also applys vulnerable to enemies on max charge.
 *
 * It is a powerful value card that is supposed to help stabilize overwhelming situations but falls off on value on single targets.
 *
 * The vulnerable debuff currently only interacts with Card_ForgeStrike but is planned to be expanded upon.
 * */

Card_Sword::Card_Sword(
        u8 dmg,
        u16 range,
        int squaredRange,
        u8 ammo,
        Rect cardRect,
        Rect clip,
        Point startingPos,
        Point velocity,
        int maxTargets,
        int maxUses,
        bool enhancedStrikeReady)
        : Card(dmg, range, squaredRange, ammo, false, attackDirection, cardRect, clip,
               startingPos, velocity, maxTargets, false,0, eCardName::Sword, maxUses,eChargeLevels::LVL0)
               , enhancedStrikeActive(enhancedStrikeReady) {

    this->squaredRange = this->range * this->range;

}
void Card_Sword::castCard(eFacingAngle aim, Point startingPoint) {

    attackDirection = aim;

    //center of player sprite
    int centerX = startingPoint.x +  32/ 2;
    int centerY = startingPoint.y + 32/ 2;
    //center the middle of the attack on the middle of the player sprite
    Point centeredCardRect = {centerX -cardRect.w/2,centerY -cardRect.h/2};

    cardRect.x = centeredCardRect.x;
    cardRect.y = centeredCardRect.y;


    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;

    setSpritesheetClip(static_cast<int>(currentChargeLevel));

    //if the previous 3 strikes hit 3 targets the next one applies vulnerable and gains up to 2 drawTokens
    if(currentChargeLevel == eChargeLevels::FULL)
    {
        applyDebuff = true;
        enhancedStrikeActive = true;
        setSpritesheetClip(static_cast<int>(eChargeLevels::FULL));
        currentChargeLevel = eChargeLevels::LVL0;

    }else{applyDebuff=false;}

    ammo-- ;
    active = true;
}


int Card_Sword::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {


    //bool to track complete misses.
    static bool missedCompletely = true;
    //
    int hit = 0;
    if (active) {

        //move the attack, its fine if it overlaps a  when colliding
        move();

        Point current = {cardRect.x, cardRect.y};
        double squaredDistanceTraveled = calculateSquaredDistance(startingPos, current);



        for (Hitbox e: colliderList) {

            if (e.hitboxID != deadID) {

                if (SDL_HasIntersection(&cardRect,
                                        (const SDL_Rect *) &e)) {
                    //if not already hit before
                    if (hitIDSet.find(e.hitboxID) == hitIDSet.end()) {
                        hitIDSet.insert(e.hitboxID);

                        if (hitIDSet.size() == maxTargets) {
                            active = false;
                            hitIDSet.clear();


                            //if the attack is not charged increase the charge level
                            if(currentChargeLevel < eChargeLevels::FULL)
                            {
                                //prevent fully charged attack from gaining charge
                                if(!enhancedStrikeActive)
                                {
                                    increaseCharge();
                                }
                                //reset enhancedStrikeActive afte it hits maxTargets
                                if(enhancedStrikeActive)
                                {
                                    enhancedStrikeActive = false;
                                }
                                setSpritesheetClip(static_cast<int>(currentChargeLevel));
                                missedCompletely = true;
                                return hit;
                            }

                        }
                        //draw a card for the first 2 targets hit if fully charged
                        if(enhancedStrikeActive)
                        {
                            if(player->drawsReady < player->maxDrawsReady)
                            {
                                player->drawsReady++;
                            }
                        }
                        missedCompletely = false;
                        return hit;
                    }
                }
            }
            hit++;
        }
        if (squaredDistanceTraveled >= squaredRange) {
            active = false;
            hitIDSet.clear();
            setSpritesheetClip(static_cast<int>(currentChargeLevel));
            enhancedStrikeActive = false;
            //if the attack misses it gets discarded in the drawCard() during ::Update
            if(missedCompletely)
            {
                ammo = 0;
            }

            missedCompletely = true;
            return notHitID;

        }
        return notHitID;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

void Card_Sword::move() noexcept
{
    // remember the y axis is inverted due to SDL
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
            cardRect.x += static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::DownLeft:
            cardRect.x -= static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::UpRight:
            cardRect.x += static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case eFacingAngle::UpLeft:
            cardRect.x -= static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
    }
}




Card_Sword::~Card_Sword()= default;