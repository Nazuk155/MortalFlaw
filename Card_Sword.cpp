//
// Created by max on 11.07.24.
//


#include "Card_Sword.h"


// Override castCard method implementation


Card_Sword::Card_Sword(
        u8 dmg,
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
        bool applyStatus,
        u8 state,
        eCardName name,
        int maxUses)
        : Card(dmg, range, squaredRange, ammo, active, attackDirection, cardRect, clip,
               startingPos, velocity, maxTargets, applyStatus, state, name, maxUses) {

    this->squaredRange = this->range * this->range;

}
void Card_Sword::castCard(eFacingAngle aim, Point startingPoint) {

    //set attack angle
    attackDirection = aim;

    //manually adjust where the attack starts. very hacky but not time to do it right
    int centerX = cardRect.x + cardRect.w / 2;
    int centerY = cardRect.y + cardRect.h / 2;

    switch (aim)
    {
        case eFacingAngle::Up:startingPoint.x -= cardRect.w/3;startingPoint.y -=cardRect.w/6;break;
        case eFacingAngle::Right:startingPoint.x -=cardRect.w/6;startingPoint.y -=cardRect.w/6;break;
        case eFacingAngle::Left:startingPoint.x -=cardRect.w/3;startingPoint.y -=cardRect.w/6;break;
        case eFacingAngle::Down:startingPoint.x -=cardRect.w/3;startingPoint.y -= cardRect.w/6;break;
        case eFacingAngle::UpRight:startingPoint.x -=cardRect.w/6;startingPoint.y -=cardRect.w/3;break;
        case eFacingAngle::DownLeft:startingPoint.x -=cardRect.w/3;startingPoint.y -=cardRect.w/6;break;
        case eFacingAngle::UpLeft:startingPoint.x -=cardRect.w/3;startingPoint.y -= cardRect.w/3;break;
        case eFacingAngle::DownRight:startingPoint.x -=cardRect.w/6;startingPoint.y -= cardRect.w/4;break;
    }
    cardRect.x = startingPoint.x;
    cardRect.y = startingPoint.y;

    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;

    //we dont use state because the instances only differ in color to distinguish
    //-1 because spritesheet clips are between 0 to 2 * clip.x
    Card::setSpritesheetClip(ammo - 1);


    ammo-- ;
    active = true;

//    std::cout << "Casting Dagger Card with CID: " << CID << std::endl;
    // Additional implementation specific to Card_Dagger
}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_Sword::doWhileActive(const Vector<Hitbox>& colliderList) {

    int hit = 0;
    int noHit = 999;
    if (active) {

        //move the attack, its fine if it overlaps a  when colliding
        move();

        Point current = {cardRect.x, cardRect.y};
        double squaredDistanceTraveled = calculateSquaredDistance(startingPos, current);



        for (Hitbox e: colliderList) {


            if (SDL_HasIntersection(&cardRect,
                                    (const SDL_Rect *) &e)) {
                //if not already hit befor
                if (hitIDSet.find(e.hitboxID) == hitIDSet.end()) {
                    hitIDSet.insert(e.hitboxID);

                    if(hitIDSet.size() == maxTargets) {
                        active = false;
                        hitIDSet.clear();


                    }

                    return hit;
                }


            }
            hit ++;
        }
        if (squaredDistanceTraveled >= squaredRange) {
            active = false;
            hitIDSet.clear();


            return noHit;

        }
        return noHit;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

void Card_Sword::move()
{
    const double sqrt2_over_2 = std::sqrt(2) / 2;  // Precomputed value for cos(45 degrees) and sin(45 degrees)
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