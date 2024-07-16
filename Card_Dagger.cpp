//
// Created by max on 11.07.24.
//


#include "Card_Dagger.h"

Card_Dagger::Card_Dagger(
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
void Card_Dagger::castCard(eFacingAngle aim, Point startingPoint) {

    //set attack angle
    attackDirection = aim;


//maybe polish this logic up for each card later. Good enough for now
    switch (aim)
    {
        case eFacingAngle::Up:startingPoint.x += cardRect.w;  startingPoint.y -= cardRect.w/2;break;
        case eFacingAngle::Right:startingPoint.x += cardRect.w;startingPoint.y -=cardRect.w/2;break;
        case eFacingAngle::Left:startingPoint.x += cardRect.w;startingPoint.y -= cardRect.w/2;break;
        case eFacingAngle::Down:startingPoint.x += cardRect.w;break;
        case eFacingAngle::UpRight:startingPoint.x += cardRect.w;startingPoint.y -= cardRect.w/2;break;
        case eFacingAngle::DownLeft:startingPoint.x += cardRect.w;startingPoint.y -= cardRect.w/2;break;
        case eFacingAngle::UpLeft:startingPoint.x += cardRect.w;startingPoint.y -= cardRect.w/2;;break;
        case eFacingAngle::DownRight:startingPoint.x += cardRect.w;startingPoint.y -= cardRect.w/2;break;
    }

    //current position of attack
    cardRect.x = startingPoint.x;
    cardRect.y = startingPoint.y;
    //starting point from where it starts animating
    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;
    if(state>3){state = 3;}
    if(state>=3){ applyDebuff = true;}
    Card::setSpritesheetClip(state);

    ammo-- ;
    active = true;

//    std::cout << "Casting Dagger Card with CID: " << CID << std::endl;
    // Additional implementation specific to Card_Dagger
}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_Dagger::doWhileActive(const Vector<Hitbox>& colliderList) {

    int hit = 0;
    int noHit = 999;
    if (active) {

        //move the attack, its fine if it overlaps a  when colliding
        move();

        Point current = {cardRect.x, cardRect.y};
        double squaredDistanceTraveled = calculateSquaredDistance(startingPos, current);



        for (Hitbox e: colliderList) {

            // i forgot to adjust the hitbox based on angle.Requires a different Rect from cardRect to not stretch the visual. Maybe polish this later
            if (SDL_HasIntersection(&cardRect,
                                    (const SDL_Rect *) &e)) {
                //if not already hit befor
                if (hitIDSet.find(e.hitboxID) == hitIDSet.end()) {
                    hitIDSet.insert(e.hitboxID);

                    if(hitIDSet.size() == maxTargets) {
                        active = false;
                        hitIDSet.clear();
                        state ++;
                        if(state>=3){ applyDebuff = true;}

                    }
                    state ++;
                    if(state>3){state = 3;}
                    Card::setSpritesheetClip(state);
                    if(state>=3){ applyDebuff = true;}
                    return hit;
                }


            }
            hit ++;
        }
        if (squaredDistanceTraveled >= squaredRange) {
            active = false;
            hitIDSet.clear();

            if(state>=3){ applyDebuff = true;}
            return noHit;

        }
        if(state>=3){ applyDebuff = true;}
        return noHit;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

void Card_Dagger::move()
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

Card_Dagger::~Card_Dagger()= default;