//
// Created by max on 11.07.24.
//

#ifndef FRESHMORTALFLAW_CARD_H
#define FRESHMORTALFLAW_CARD_H

#include <unordered_set>
#include "global.h"
#include "AngleHelper.h"

#ifndef CARD_H
#define CARD_H

class Card {
public:
    // Attributes
    u8 cID;
    u8 dmg;
    u16 range;
    int squaredRange = range* range;
    u8 uses;
    bool active;
    Angle attackDirection;
    Rect cardRect;
    Rect clip;
    Point startingPos;
    Point velocity;
    Vector<Rect> collisionTargets;
    std::unordered_set<int> hitIDSet;
    // Constructor
    Card();
    Card(u8 cID, u8 dmg, u16 range, int squaredRange, u8 uses, bool active, Angle attackDirection, Rect cardRect,
         Rect clip, Point startingPos, Point velocity);

    // Virtual destructor
    virtual ~Card() = 0;  // Pure virtual destructor

    // Pure virtual function to be overridden by derived classes
    virtual void castCard(Angle aim, Point startingPoint) = 0;

    virtual int doWhileActive(const Vector<Rect>& colliderList) =0;

    static double calculateSquaredDistance(const Point& p1, const Point& p2) {
        return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    }
    virtual void move() = 0;
    [[nodiscard]] double getAttackDirectionDouble() const{return  static_cast<double>(static_cast<int>(attackDirection));};
};

#endif // CARD_H




#endif //FRESHMORTALFLAW_CARD_H
