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
            useCard(&slotLeft);
        case HandPosition::M:
            useCard(&slotMiddle);
        case HandPosition::R:
            useCard(&slotRight);
    }
}

//takes an actual card pointer so that cards that cast other cards are easy to implement later
bool Player::useCard(Card ** slot)
{
    if(*slot != nullptr) {
        (*slot)->castCard();

        discard.push_back(*slot);
        *slot = nullptr;
        return true;
    }
    return false;

}
///TODO cards in discard or burn that are active will be rendered until their whenActive sets active to false
// interface on the bottom with timer filling and handcards, next card on left in small, deck next to it. Right side has player ability and discard as well as burn.
//burned cards can be restored with forge. Player has overload charges or loses a card every 10 seconds from the top of the deck.
//to not have a constantly shifting deck the player only adds cards calmly to the deck and FORGE actions basically recovers lost ammo back into the deck.

void Player::drawCard()
{
    //ugly but no time to refactor
    //handsize never changes so this is fine
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

    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr );


    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
       // switch( e.key.keysym.sym )
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_w: VelY -= PLAYER_VEL;currentAngle =Angle::Up; break;
            case SDLK_s: VelY += PLAYER_VEL;currentAngle =Angle::Down; break;
            case SDLK_a: VelX -= PLAYER_VEL;currentAngle =Angle::Left; break;
            case SDLK_d: VelX += PLAYER_VEL;currentAngle =Angle::Right; break;
        }
    }
        //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: VelY += PLAYER_VEL; break;
            case SDLK_s: VelY -= PLAYER_VEL; break;
            case SDLK_a: VelX += PLAYER_VEL; break;
            case SDLK_d: VelX -= PLAYER_VEL; break;
        }
    }
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
    //button modifier idea
    //if(currentKeyStates[SDL_SCANCODE_E]){ }else{
    if(currentKeyStates[SDL_SCANCODE_LEFT]){ triggerSlot(HandPosition::L);}
    if(currentKeyStates[SDL_SCANCODE_UP]){ triggerSlot(HandPosition::M);}
    if(currentKeyStates[SDL_SCANCODE_RIGHT]){ triggerSlot(HandPosition::R);}
}

/*
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: VelY -= PLAYER_VEL;activeFacingDirection +=Up;lastFacingDirection = activeFacingDirection;currentAngle +=Up; break;
        case SDLK_DOWN: VelY += PLAYER_VEL;activeFacingDirection +=Down;lastFacingDirection=activeFacingDirection; break;
        case SDLK_LEFT: VelX -= PLAYER_VEL;activeFacingDirection += Left;lastFacingDirection=activeFacingDirection; break;
        case SDLK_RIGHT: VelX += PLAYER_VEL;activeFacingDirection += Right;lastFacingDirection =activeFacingDirection; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_UP: VelY += PLAYER_VEL;activeFacingDirection -=Up; break;
        case SDLK_DOWN: VelY -= PLAYER_VEL;activeFacingDirection -=Down; break;
        case SDLK_LEFT: VelX += PLAYER_VEL;activeFacingDirection -=Right; break;
        case SDLK_RIGHT: VelX -= PLAYER_VEL;activeFacingDirection -=Left; break;
        }
    }
}
*/
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
double Player::getFacingAngle() const {
    return static_cast<double>(static_cast<int>(currentAngle));
}


int Player::getXPos() const{return pos.x;}
int Player::getYPos() const{return pos.y;}
int Player::getWidth() const{return PLAYER_WIDTH;}
int Player::getHeight() const{return PLAYER_HEIGHT;}

Rect * Player::getCollisionRect() {return &collisionRect;}
Rect * Player::getClipRect() {return &clip;}

Point * Player::getPoint()  {return &pos;}

