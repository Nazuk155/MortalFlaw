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
        case eFacingAngle::Up:cardRect.y = centeredCardRect.y - cardRect.h;break;
        case eFacingAngle::Right:cardRect.x = centeredCardRect.x + cardRect.w;break;
        case eFacingAngle::Left:cardRect.x = centeredCardRect.x - cardRect.w;;break;
        case eFacingAngle::Down:cardRect.y = centeredCardRect.y + cardRect.h;break;
        case eFacingAngle::UpRight:cardRect.x = centeredCardRect.x + cardRect.w/2;cardRect.y = centeredCardRect.y - cardRect.h/2;break;
        case eFacingAngle::DownLeft:cardRect.x = centeredCardRect.x - cardRect.w/2;cardRect.y = centeredCardRect.y + cardRect.h/2;break;
        case eFacingAngle::UpLeft:cardRect.x = centeredCardRect.x - cardRect.w/2;cardRect.y = centeredCardRect.y - cardRect.h/2;break;
        case eFacingAngle::DownRight:cardRect.x = centeredCardRect.x + cardRect.w/2;cardRect.y = centeredCardRect.y + cardRect.h/2;;break;
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
        setSpritesheetClip(4);
        state = 0;
    }

    ammo-- ;
    active = true;

}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_ForgeStrike::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {

    int hit = 0;
    //start at frame2
    static int animationTracker = 0;
    const int lingeringHitboxTime = 30;
    static int startingFrame = 0;
    if(startingFrame == 0)
    {
        startingFrame = frame;

    }

    if (active) {

        if(startingFrame+ lingeringHitboxTime > frame) {
            if(animationTracker<30&&animationTracker>24){
                setSpritesheetClip(3);
                if(state == 1){ setSpritesheetClip(4);}

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
                                    animationTracker = 0;
                                    startingFrame = 0;
                                }
                                if (e.debuff) {
                                    //if hit enemy is debuffed gain powered up next hit + reforge active
                                    reforge(player);
                                    state = 1;
                                    setSpritesheetClip(4);
                                }
                                animationTracker++;
                                if(animationTracker == 30){animationTracker = 0;}
                                if(startingFrame+lingeringHitboxTime <= frame){startingFrame = 0;}
                                return hit;
                            }
                        }
                    }
                    hit++;

                }
            }
            if(animationTracker<24){
                setSpritesheetClip(2);
            }
            if(animationTracker<18){
                setSpritesheetClip(2);
            }
            if(animationTracker<12){
                setSpritesheetClip(1);
            }
            if(animationTracker<6){
                setSpritesheetClip(0);
            }

            animationTracker++;
        }
        if (startingFrame+ lingeringHitboxTime <= frame) {
            active = false;
            hitIDSet.clear();
            startingFrame = 0;
            animationTracker = 0;
            if(dmg == enhancedDamage){state = 0;}
            return notHitID;
        }
        return notHitID;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

//not needed for this card
void Card_ForgeStrike::move(){}

//regains 2 cards per enemy hit into discard
void Card_ForgeStrike::reforge(Player * player)
{
    if(!player->ashes.empty()){
    for(int i=0;i<2;i++) {
        if(!player->ashes.empty()) {
            player->addCardToDiscard(player->ashes.back());
            player->ashes.pop_back();
        }
    }


    }
}

Card_ForgeStrike::~Card_ForgeStrike()= default;
