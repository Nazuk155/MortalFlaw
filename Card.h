//
// Created by max on 11.07.24.
//

#pragma once
#include <unordered_set>
#include "global.h"
#include "AngleHelper.h"
#include "Player.h"

enum class eChargeLevels{LVL0,LVL1,LVL2,FULL};

/** Extra viel Kommentare NUR in dieser Klasse um den Überblick über die Attribute zu behalten.
 * */

class Player;

class Card {
    //all public so they are easy to access. Maybe refector this with getter/setter if this becomes a problem
public:

    //card ID for individual card instances. Increases by 1 for each
    int cID;
    //damage on contact with target
    u8 dmg;
    //range until the max rang
    u16 range;
    //squared range for sidestepping the sqrt math
    int squaredRange = range* range;
    //ammo until card goes into discard. Reset in player::castCard after all ammunition is gone and drawCard if it has changing amounts of ammo
    u8 ammo ;
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
    //maximum amount of targets that can get hit before the card goes inactive
    int maxTargets;
    //toggle for activating applying the derived cards debuffs. probably put all different debuffs in a enum for ease of use
    bool applyDebuff;
    //saves the current clipOffset
    u8 clipOffset ;
    //table for storing already hit targets so no unintended double hit occurs
    std::unordered_set<int> hitIDSet;
    //name of the card in the game. all stored in global.h enum to not carry strings around
    eCardName cardName;
    //used to reset ammo back to maximum in Player::castCard() after ammo reaches 0 and card gets discarded
    int maxUses;
    // many cards have charge states. Can be used instead of specialized card attributes to track these.
    eChargeLevels currentChargeLevel = eChargeLevels::LVL0;

    explicit Card(u8 dmg = 1,
         u16 range = 0,
         int squaredRange = 0,
         u8 ammo = 1,
         bool active = false,
         eFacingAngle attackDirection = eFacingAngle::Up,
         Rect cardRect ={0,0,0,0},
         Rect clip = {0,0,0,0},
         Point startingPos = {0,0},
         Point velocity = {0,0},
         int maxTargets = 1,
         bool applyDebuff = false,
         u8 clipOffset = 0,
         eCardName cardName = eCardName::BaseCard,
         int maxUses = 1,
         eChargeLevels currentChargeLevel = eChargeLevels::LVL0);


    virtual ~Card() = 0;  // Pure virtual destructor

    //sets active = true and prepares card to be active
    virtual void castCard(eFacingAngle aim, Point startingPoint) = 0;
    //repeats until active is false. contains card logic for active card instanceFstat
    virtual int doWhileActive(const Vector<Hitbox> &colliderList, u32 frame, Player *player) =0;

    //sets the Clip Rect x to clip the next viable portion of the spritesheet
    virtual void setSpritesheetClip(int spriteNr) noexcept;

    //moves the card using velocity. usually called in doWhileActive
    virtual void move() = 0;

    //helper to convert the enum to a double for rendering with renderCopy
    [[nodiscard]] double getAttackDirectionDouble() const{return  static_cast<double>(static_cast<int>(attackDirection));};



//static stuff here

    //helper to always add +1 to the cID
    static int nextID;
    //helper function to accurately track range in diagonals
    static double calculateSquaredDistance(const Point& p1, const Point& p2) noexcept {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }

    void increaseCharge() noexcept;
};
