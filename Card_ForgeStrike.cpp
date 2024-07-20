//
// Created by max on 18.07.24.
//

#include "Card_ForgeStrike.h"


/** DESCRIPTION:
 * Forge cards are essential for the game to function. They restore cards back into the discard based on conditions being fulfilled.
 *
 * ForgeStrike interacts with the vulnerable debuff.
 * If used normally it deals 3 damage after a delayed animation.
 * If used on debuffed enemies it triggers reforge() and adds cards back into the deck based on the amount of debuffed enemies hit.
 * It also gains double damage and a enhanced state.
 * Enhanced hits on debuffed enemies restore double the normal amount of cards.
 *
 * The attack has a delayed hitbox as it represents a big slow hammer strike that erupts the ground.
 * It is only active from frame 26-30.
 * */


Card_ForgeStrike::Card_ForgeStrike(
        u8 dmg,
        Rect cardRect,
        Rect clip,
        int maxTargets,
        int enhancedDamage)

        : Card(dmg,
               0,
               0,
               1,
               false,
               eFacingAngle::Up,
               cardRect,
               clip,
               {0,0},
               {0,0},
               maxTargets,
               false,
               clipOffset,
               eCardName::ForgeStrike,
               1,
               eChargeLevels::LVL0),
          enhancedDamage(enhancedDamage){}

void Card_ForgeStrike::castCard(eFacingAngle aim, Point playerPos) {

    attackDirection = aim;
    //center of player sprite
    int centerX = playerPos.x +  32/ 2;
    int centerY = playerPos.y + 32/ 2;
    //center the middle of the attack on the middle of the player sprite
    Point centeredCardRect = {centerX -cardRect.w/2,centerY -cardRect.h/2};
    cardRect.x = centeredCardRect.x;
    cardRect.y = centeredCardRect.y;

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

    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;


    if(currentChargeLevel == eChargeLevels::LVL0)
    {
        //should make new attribute to save original damage
        dmg = 1;
    }

    //if debuffed enemy was hit use enhanced damage on next use
    if(currentChargeLevel == eChargeLevels::FULL)
    {
        dmg = enhancedDamage;
        setSpritesheetClip(4);
        currentChargeLevel = eChargeLevels::LVL0 ;
    }

    ammo-- ;
    active = true;
}

/// TODO think of burning cards mechanics. Include Player in the specific cards to access their deck and add cards to the temporary deck that get deleted when inactive.
//int Card_Dagger::doWhileIgnited(const Vector<Hitbox>& hitboxList,Player &p){ p.addCardtoDeck}

int Card_ForgeStrike::doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) {

    int hit = 0;
    static int animationFrame = 0;
    const int animationDuration = 30;

    if (active) {
        if(animationFrame <= animationDuration) {
            if(animationFrame < 30 && animationFrame > 24){
                setSpritesheetClip(3);
                if(dmg == enhancedDamage){ setSpritesheetClip(4);}

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
                                    animationFrame = 0;
                                }
                                if (e.debuff) {
                                    //if hit enemy is debuffed gain powered up next hit + reforge active
                                    reforge(player);
                                    currentChargeLevel = eChargeLevels::FULL;
                                }
                                animationFrame++;
                                if(animationFrame == 30){ animationFrame = 0;}
                                return hit;
                            }
                        }
                    }
                    hit++;

                }
            }
            if(animationFrame < 24){
                setSpritesheetClip(2);
            }
            if(animationFrame < 18){
                setSpritesheetClip(2);
            }
            if(animationFrame < 12){
                setSpritesheetClip(1);
            }
            if(animationFrame < 6){
                setSpritesheetClip(0);
            }

            animationFrame++;
        }
        if (animationFrame >= animationDuration) {
            active = false;
            hitIDSet.clear();
            animationFrame = 0;

            //if the enhanced strike was used set the it back to uncharged unless debuffed enemy hit with it
            if(dmg == enhancedDamage){currentChargeLevel = eChargeLevels::LVL0;}
            //if a debuffed enemy was hit change to clip 4 to show powered up attack in hand icon
            if(currentChargeLevel == eChargeLevels::FULL){ setSpritesheetClip(4);}
            return notHitID;
        }
        return notHitID;
    }
    else{ printf("Card %d not active in doWhileActive for some reason?!",cID);}
    return -1;
}

//not needed for this card
void Card_ForgeStrike::move()noexcept{}

//regains cards based on enemy hit. More if the strike is powered up
void Card_ForgeStrike::reforge(Player * player)
{
    int amountOfCardsRestored = 1;
    if(dmg == enhancedDamage){
        amountOfCardsRestored = 2;
    }
        if(!player->ashes.empty()) {
            for (int i = 0; i < amountOfCardsRestored; i++) {
                if (!player->ashes.empty()) {
                    player->addCardToDiscard(player->ashes.back());
                    player->ashes.pop_back();
                }
            }
        }

}

Card_ForgeStrike::~Card_ForgeStrike()= default;
