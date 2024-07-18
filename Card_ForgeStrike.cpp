//
// Created by max on 18.07.24.
//

#include "Card_ForgeStrike.h"



Card_ForgeStrike::Card_ForgeStrike(
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
        int maxUses,
        int conditionalDamage)
        : Card(dmg, range, squaredRange, ammo, active, attackDirection, cardRect, clip,
               startingPos, velocity, maxTargets, applyStatus, state, name, maxUses),
          enhancedDamage(conditionalDamage){

    this->squaredRange = this->range * this->range;

}
void Card_ForgeStrike::castCard(eFacingAngle aim, Point playerPos) {

    //set attack angle
    attackDirection = aim;
    //center of player sprite
    int centerX = playerPos.x +  32/ 2;
    int centerY = playerPos.y + 32/ 2;
    //center the middle of the attack on the middle of the player sprite
    Point centeredCardRect = {centerX -cardRect.w/2,centerY -cardRect.h/2};

    cardRect.x = centeredCardRect.x;
    cardRect.y = centeredCardRect.y;

//maybe polish this logic up for each card later. Good enough for now
    switch (aim)
    {
        case eFacingAngle::Up:cardRect.y = centeredCardRect.y + cardRect.h;break;
        case eFacingAngle::Right:cardRect.x = centeredCardRect.x + cardRect.w;break;
        case eFacingAngle::Left:cardRect.x = centeredCardRect.x - cardRect.w;;break;
        case eFacingAngle::Down:cardRect.y = centeredCardRect.y + cardRect.h;break;
        case eFacingAngle::UpRight:cardRect.x = centeredCardRect.x + cardRect.w;cardRect.y = centeredCardRect.y - cardRect.h;break;
        case eFacingAngle::DownLeft:cardRect.x = centeredCardRect.x - cardRect.w;cardRect.y = centeredCardRect.y + cardRect.h;break;
        case eFacingAngle::UpLeft:cardRect.x = centeredCardRect.x - cardRect.w;cardRect.y = centeredCardRect.y - cardRect.h;break;
        case eFacingAngle::DownRight:cardRect.x = centeredCardRect.x + cardRect.w;cardRect.y = centeredCardRect.y + cardRect.h;;break;
    }

    //current position of attack

    //starting point from where it starts animating
    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;
    if(state == 0)
    {
        //should make new attribute to save original damage
        dmg = 1;
    }

    //if debuffed enemy was hit use enhanced damage
    if(state == 1)
    {
        dmg = enhancedDamage;
        state = 0;
    }

    ammo-- ;
    active = true;

}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_ForgeStrike::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {

    int hit = 0;
    const int lingeringHitboxTime = 10;
    static int startingFrame = 0;
    if(startingFrame == 0)
    {
        startingFrame = frame;
    }

    if (active) {

        if(startingFrame+ lingeringHitboxTime > frame) {

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
                            }
                            if (e.debuff) {
                                //if hit enemy is debuffed gain powered up next hit + reforge active
                                reforge(player);
                                state = 1;
                            }
                            return hit;
                        }
                    }
                }
                hit++;

            }
        }
        if (startingFrame+ lingeringHitboxTime < frame) {
            active = false;
            hitIDSet.clear();
            return notHitID;
        }
        return notHitID;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

void Card_ForgeStrike::move()
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

void Card_ForgeStrike::reforge(Player  player)
{

    for(int i=0;i<2;i++) {
        player.addCardToDiscard(player.ashes.back());
        player.ashes.pop_back();

    }
}

Card_ForgeStrike::~Card_ForgeStrike()= default;
