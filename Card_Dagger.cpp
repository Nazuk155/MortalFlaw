//
// Created by max on 11.07.24.
//

#include "Card_Dagger.h"


// Override castCard method implementation


Card_Dagger::Card_Dagger(u8 cID,
                         u8 dmg,
                         u16 range,
                         int squaredRange,
                         u8 uses,
                         bool active,
                         Angle attackDirection,
                         Rect cardRect,
                         Rect clip,
                         Point startingPos,
                         Point velocity)
                         : Card(cID, dmg, range, squaredRange, uses, active, attackDirection, cardRect, clip,
                                startingPos, velocity) {

        this->squaredRange = this->range * this->range;

}
void Card_Dagger::castCard(Angle aim, Point startingPoint) {

    //set attack angle
    attackDirection = aim;
    //current position of attack
    cardRect.x = startingPoint.x;
    cardRect.y = startingPoint.y;
    //starting point from where it starts animating
    startingPos.x = cardRect.x;
    startingPos.y = cardRect.y;
    uses -=1;
    active = true;


//    std::cout << "Casting Dagger Card with CID: " << CID << std::endl;
    // Additional implementation specific to Card_Dagger
}


int Card_Dagger::doWhileActive(const Vector<Rect>& colliderList)
{
    ///TODO use the hitIDSet by refactoring colliderList with enemy IDs and storing them to check if the target was already hit
    Card::hitIDSet;

    int hit = 0;
    //move the attack, its fine if it overlaps a  when colliding
    move();

    Point current = {cardRect.x,cardRect.y};
    double squaredDistanceTraveled = calculateSquaredDistance(startingPos,current);

    for(Rect e:colliderList) {
        if ((cardRect.y < 0) || (cardRect.y + cardRect.h > SCREEN_HEIGHT)){
            active = false;
            break;

        }
        if(SDL_HasIntersection(&cardRect,
                            (const SDL_Rect *) &e)) {


            active = false;
            return hit;
        }
        hit ++;
    }
    if(squaredDistanceTraveled>=squaredRange)
    {
        active = false;

    }
}

void Card_Dagger::move()
{
    const double sqrt2_over_2 = std::sqrt(2) / 2;  // Precomputed value for cos(45 degrees) and sin(45 degrees)
    // remember the y axis is inverted due to SDL
    switch(attackDirection) {
        case Angle::Right:
            cardRect.x += velocity.x;
            break;
        case Angle::Left:
            cardRect.x -= velocity.x;
            break;
        case Angle::Down:
            cardRect.y += velocity.y;
            break;
        case Angle::Up:
            cardRect.y -= velocity.y;
            break;
        case Angle::DownRight:
            cardRect.x += static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case Angle::DownLeft:
            cardRect.x -= static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y += static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case Angle::UpRight:
            cardRect.x += static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
        case Angle::UpLeft:
            cardRect.x -= static_cast<int>(std::round(velocity.x * sqrt2_over_2));
            cardRect.y -= static_cast<int>(std::round(velocity.y * sqrt2_over_2));
            break;
    }
}



Card_Dagger::~Card_Dagger()= default;