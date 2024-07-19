//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_H
#define FRESHMORTALFLAW_CARD_H

#include <unordered_set>
#include "global.h"
#include "AngleHelper.h"
#include "Player.h"

#ifndef CARD_H
#define CARD_H

class Player;

class Card {
public:
    // Attributes
    //card ID for individual card instances. Increases by 1 for each card
    int cID;
    //damage on contact with target
    u8 dmg;
    //range until the max rang
    u16 range;
    //squared range for sidestepping the sqrt math
    int squaredRange = range* range;
    //ammo until card goes into discard. Reset in player::castCard after all ammunition is gone
    u8 ammo;
    //If active it gets rendered and its doWhileActive keeps getting called
    bool active;
    //determines attack direction in 45 degrees using the AngleHelper enum
    eFacingAngle attackDirection;
    //dimensions of the rendered card effect
    Rect cardRect;
    //dimensions of the spritesheet areas. Offset clip.x by clip.w for the next sprite
    Rect clip;
    //start coordinates of the animation
    Point startingPos;
    //speed at which the card effect gets moved
    Point velocity;
    //vector that captures all colliding targets
    Vector<Rect> collisionTargets;
    //maximum amount of targets that can get hit before the card goes inactive
    int maxTargets;
    //toggle for activating applying the derived cards debuffs. probably put all different debuffs in a enum for ease of use
    bool applyDebuff;
    //multiple uses based on card logic. Often used in setSpritesheetClip to switch to powered up versions of the base sprite
    u8 state;
    //table for storing already hit targets so no unintended double hit occurs
    std::unordered_set<int> hitIDSet;
    //name of the card in the game. all stored in global.h enum to not carry strings around
    eCardName cardName;
    //used to reset ammo back to maximum in Player::castCard() after ammo reaches 0 and card gets discarded
    int maxUses;

    //helper to always add +1 to the cID
    static int nextID;
    // Constructor
    Card();
    Card(u8 dmg, u16 range, int squaredRange, u8 ammo, bool active, eFacingAngle attackDirection, Rect cardRect,
         Rect clip, Point startingPos, Point velocity, int maxTargets, bool applyDebuff, u8 state,eCardName cardName,int maxUses);



    // Virtual destructor
    virtual ~Card() = 0;  // Pure virtual destructor

    // Pure virtual function to be overridden by derived classes
    //sets active = true and prepares card to be active
    virtual void castCard(eFacingAngle aim, Point startingPoint) = 0;
    //repeats until active is false. contains card logic for active card instance
    virtual int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) =0;

    //sets the Clip Rect x to clip the next viable portion of the spritesheet
    virtual void setSpritesheetClip(int spriteNr);
    //helper function to accurately track range in diagonals
    static double calculateSquaredDistance(const Point& p1, const Point& p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    //moves the card using velocity. usually called in doWhileActive
    virtual void move() = 0;
    //helper to convert the enum to a double for rendering with renderCopy
    [[nodiscard]] double getAttackDirectionDouble() const{return  static_cast<double>(static_cast<int>(attackDirection));};
};

#endif // CARD_H




#endif //FRESHMORTALFLAW_CARD_H
