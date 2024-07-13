//
// Created by max on 01.07.24.
//

#include "Player.h"



Player::Player()
{
    ///needs inventory/deck, current hand pointers, facing direction,stats like hp etc.,

    //Initialize the offsets
    pos.x = 0;
    pos.y = 0;

    //Initialize the velocity
    VelX = 0;
    VelY = 0;

   collisionRect  = {pos.x,pos.y,PLAYER_WIDTH,PLAYER_HEIGHT};
   hand.push_back(nullptr);
   hand.push_back(nullptr);
   hand.push_back(nullptr);


}
void Player::addCardToDeck(Card * newCard)
{
    if(newCard != nullptr) {
        deck.push_back(newCard);
    }
    else{ printf("addCard failed due to nullptr");}

}

void Player::triggerSlot(HandPosition id) {

    switch (id) {
        case HandPosition::L:
            //useCard(&hand[0]);
            useCard(&slotLeft);
            break;
        case HandPosition::M:
           // useCard(&hand[1]);
            useCard(&slotMiddle);
            break;
        case HandPosition::R:
           // useCard(&hand[2]);
           useCard(&slotRight);
            break;
    }
}

//takes an actual card pointer so that cards that cast other cards are easy to implement later
bool Player::useCard(Card ** slot)
{
    if(*slot != nullptr) {
        (*slot)->castCard(getFacingAngle(), pos);

        discard.push_back(*slot);
        *slot = nullptr;
        return true;
    }
    return false;

}


void Player::drawCard()
{
    //ugly but no time to refactor
    //handsize never changes so this is fine
    /*
    for(int i = 0;i<3;i++) {
        if (!deck.empty()) {
            if (hand[i] == nullptr) {
                drawsReady -= 1;
                hand[i] = deck[0];
                deck.pop_back();
            }
        }
    }
    */
    if(slotLeft == nullptr)
    {
        if(drawsReady>0 && !deck.empty())
        {
            drawsReady -=1;
            slotLeft = deck.back();
            deck.pop_back();
        }
    }
    if(slotMiddle == nullptr)
    {
        if(drawsReady>0&& !deck.empty())
        {
            drawsReady -=1;
            slotMiddle = deck.back();
            deck.pop_back();
        }
    }
    if(slotRight == nullptr)
    {
        if(drawsReady>0&& !deck.empty())
        {
            drawsReady -=1;
            slotRight = deck.back();
            deck.pop_back();
        }
    }


}

void Player::handleEvent( SDL_Event& e )
{

//using enum Angle; too much time was wasted trying to get this to work.
//can not get this enum namespace to work in any way. I tried updating compilers and more. Alas my directions come with Angle:: for now

    //If a key was pressed
    static bool w=false,a=false,s=false,d=false;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr );


    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
       // switch( e.key.keysym.sym )
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            ///maybe display a aiming line on press and fire on release?
           // case SDLK_SPACE:VelY = VelY/2;VelX = VelX/2;break; cant do it like this for obvious reasons. better modify the move() with an additional toggle
            case SDLK_LEFT:triggerSlot(HandPosition::L);break;
            case SDLK_UP:triggerSlot(HandPosition::M);break;
            case SDLK_RIGHT:triggerSlot(HandPosition::R);break;
            case SDLK_w: VelY -= PLAYER_VEL;currentAngle =Angle::Up;w=true; break;
            case SDLK_s: VelY += PLAYER_VEL;currentAngle =Angle::Down;s=true; break;
            case SDLK_a: VelX -= PLAYER_VEL;currentAngle =Angle::Left;a=true;break;
            case SDLK_d: VelX += PLAYER_VEL;currentAngle =Angle::Right;d=true; break;
        }
    }
        //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_w: VelY += PLAYER_VEL;w=false; break;
            case SDLK_s: VelY -= PLAYER_VEL;s=false; break;
            case SDLK_a: VelX += PLAYER_VEL;a=false; break;
            case SDLK_d: VelX -= PLAYER_VEL;d=false; break;
        }
    }

    //really dumb but it works
    /*
    if(w && d){ currentAngle = Angle::UpRight;}
    if(w&&!d&&!s&&!a){currentAngle = Angle::Up;}
    if(!w&&d&&!s&&!a){currentAngle = Angle::Right;}

    if(s && d){ currentAngle = Angle::DownRight;}
    if(s&&!d&&!a&&!w){currentAngle = Angle::Down;}
    if(!s&&d&&!a&&!w){currentAngle = Angle::Right;}

    if(w&&a){currentAngle = Angle::UpLeft;}
    if(w&&!a&&!s&&!d){currentAngle = Angle::Up;}
    if(!w&&a&&!s&&!d){currentAngle = Angle::Left;}

    if(s&&a){currentAngle = Angle::DownLeft;}
    if(s&&!a&&!w&&!d){currentAngle = Angle::Down;}
    if(!s&&a&&!w&&!d){currentAngle = Angle::Left;}
    */
    //made it pretty
    if (w) {
        if (d) {
            currentAngle = Angle::UpRight;
        } else if (a) {
            currentAngle = Angle::UpLeft;
        } else {
            currentAngle = Angle::Up;
        }
    } else if (s) {
        if (d) {
            currentAngle = Angle::DownRight;
        } else if (a) {
            currentAngle = Angle::DownLeft;
        } else {
            currentAngle = Angle::Down;
        }
    } else if (d) {
        currentAngle = Angle::Right;
    } else if (a) {
        currentAngle = Angle::Left;
    }


    ///Diagonals are sticky when set with b But i actually kinda like it. This might become a dedicated button for vertical aim while moving now!
    /*
    if( currentKeyStates[ SDL_SCANCODE_W ]&&currentKeyStates[SDL_SCANCODE_D] )
    {
        currentAngle=Angle::UpRight;
    }
    if( currentKeyStates[ SDL_SCANCODE_S ]&&currentKeyStates[SDL_SCANCODE_D] )
    {
        currentAngle=Angle::DownRight;
    }
    if( currentKeyStates[ SDL_SCANCODE_W ]&&currentKeyStates[SDL_SCANCODE_A] )
    {
        currentAngle=Angle::UpLeft;
    }
    if( currentKeyStates[ SDL_SCANCODE_S ]&&currentKeyStates[SDL_SCANCODE_A] )
    {
        currentAngle=Angle::DownLeft;
    }
     */
    //button modifier idea
    //if(currentKeyStates[SDL_SCANCODE_E]){ }else{
    /*
    if(currentKeyStates[SDL_SCANCODE_LEFT]){ triggerSlot(HandPosition::L);}
    if(currentKeyStates[SDL_SCANCODE_UP]){ triggerSlot(HandPosition::M);}
    if(currentKeyStates[SDL_SCANCODE_RIGHT]){ triggerSlot(HandPosition::R);}
     */
}

void Player::move(const Vector<Rect>& colliderList)
{
    //Move the Player left or right

    pos.x +=VelX;
    collisionRect.x += VelX;

    //If the Player went too far to the left or right and check collision list
    for(auto a:colliderList) {
        if ((pos.x < 0) || (pos.x + PLAYER_WIDTH > SCREEN_WIDTH) || SDL_HasIntersection(&collisionRect,&a)) {
            //Move back
            pos.x -= VelX;
            collisionRect.x -= VelX;
        }
    }
    //Move the Player up or down and check collider list
    pos.y += VelY;
    collisionRect.y += VelY;

    //If the Player went too far up or down and check collision list
    for(auto a:colliderList) {
        if ((pos.y < 0) || (pos.y + PLAYER_HEIGHT > SCREEN_HEIGHT)|| SDL_HasIntersection(&collisionRect,
                                                                                       (const SDL_Rect *) &a)) {
            //Move back
            pos.y -= VelY;
            collisionRect.y -= VelY;
        }
    }


}
double Player::getFacingAngleDouble() const {
    return static_cast<double>(static_cast<int>(currentAngle));
}
Angle Player::getFacingAngle() const {return currentAngle;}


int Player::getXPos() const{return pos.x;}
int Player::getYPos() const{return pos.y;}
int Player::getWidth() const{return PLAYER_WIDTH;}
int Player::getHeight() const{return PLAYER_HEIGHT;}

Rect * Player::getCollisionRect() {return &collisionRect;}
Rect * Player::getClipRect() {return &clip;}

Point * Player::getPoint()  {return &pos;}

