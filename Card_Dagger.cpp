//
// Created by max on 11.07.24.
//

#include "Card_Dagger.h"


// Override castCard method implementation


Card_Dagger::Card_Dagger(u8 cID, u8 dmg, u16 range, u8 uses, bool active,Rect cardRect,Rect clip) : Card(cID,  dmg,  range,  uses, active, cardRect,clip) {

}
void Card_Dagger::castCard()  {
    uses -=1;
    active = true;

//    std::cout << "Casting Dagger Card with CID: " << CID << std::endl;
    // Additional implementation specific to Card_Dagger
}

///TODO refactor whenActive into card and make actual attack logic
void Card_Dagger::doWhenActive(const Vector<Rect>& colliderList,Angle ang)
{

}
Card_Dagger::~Card_Dagger()= default;