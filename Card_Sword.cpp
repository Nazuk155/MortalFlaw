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
        bool applyDebuff,
        u8 state,
        eCardName name,
        int maxUses)
        : Card(dmg, range, squaredRange, ammo, active, attackDirection, cardRect, clip,
               startingPos, velocity, maxTargets, applyDebuff, state, name, maxUses) {

    this->squaredRange = this->range * this->range;

}
void Card_Sword::castCard(eFacingAngle aim, Point startingPoint) {

    //set attack angle
    attackDirection = aim;

    //set attack angle
    attackDirection = aim;
    //center of player sprite
    int centerX = startingPoint.x +  32/ 2;
    int centerY = startingPoint.y + 32/ 2;
    //center the middle of the attack on the middle of the player sprite
    Point centeredCardRect = {centerX -cardRect.w/2,centerY -cardRect.h/2};

    cardRect.x = centeredCardRect.x;
    cardRect.y = centeredCardRect.y;


    //starting point from where it starts animating
    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;

    //if the previous 3 strikes hit 3 targets the next one applies vulnerable and gains 2 drawTokens
    if(state ==3)
    {
        applyDebuff = true;
        state = 0;
        Card::setSpritesheetClip(3);
    }else{applyDebuff=false;}

    ammo-- ;
    active = true;

//    std::cout << "Casting Dagger Card with CID: " << CID << std::endl;
    // Additional implementation specific to Card_Dagger
}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_Sword::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {

    int hit = 0;
    int noHit = 999;
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
                            //gain power up if 3 strikes hit 3 targets
                            if (state < 3) {
                                state++;
                                Card::setSpritesheetClip(state);
                                if(state == 3){ setSpritesheetClip(3);}
                                return hit;
                            }
                        }
                        Card::setSpritesheetClip(state);
                            if(state == 3)
                            {
                                Card::setSpritesheetClip(3);
                                applyDebuff = true;
                            }


                        if(applyDebuff){Card::setSpritesheetClip(3);if(player->drawsReady<3){player->drawsReady += 2;}}
                        return hit;
                    }
                }
            }
            hit++;
        }
        if (squaredDistanceTraveled >= squaredRange) {
            active = false;
            hitIDSet.clear();
            state;
            Card::setSpritesheetClip(state);
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