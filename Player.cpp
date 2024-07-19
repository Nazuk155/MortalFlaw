//
// Created by max on 01.07.24.
//

#include "Player.h"

//set aimingMode toggle to off
//bool Player::aimingMode = false;

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

    //initialize hand with 3 slots
    hand.push_back(nullptr);
    hand.push_back(nullptr);
    hand.push_back(nullptr);

    //set stats
    //true if card cooldown is active
    cardCooldownState = false;
    //cooldowns in frames
    cardUseCooldown = 30;

    currentCardCooldown = 180;
    drawCooldown = 360;
    currentDrawCooldown = 0;
    overheatCooldown = 600;
    currentOverheatCooldown = 600;
    abilityCooldown = 300;
    currentAbilityCooldown = 0;


}
void Player::addCardToDeck(Card * newCard)
{
    if(newCard != nullptr) {
        deck.push_back(newCard);
    }
    else
    {
        printf("addCard failed due to nullptr");
    }

}

void Player::addCardToDiscard(Card * addedCard)
{
    if(addedCard != nullptr) {
        discard.push_back(addedCard);
    }
    else
    {
        printf("ToDiscard failed due to nullptr");
    }
}

void Player::addCardToAshes(Card * addedCard)
{
    if(addedCard != nullptr) {
        ashes.push_back(addedCard);
    }
    else
    {
        printf("ToBurned failed due to nullptr");
    }
}

void Player::shuffleDiscardIntoDeck(bool shuffle)
{
    if(!discard.empty()) {
        if (shuffle) {
            auto rd = std::random_device{};
            auto rng = std::default_random_engine{rd()};
            std::shuffle(std::begin(discard), std::end(discard), rng);
        }
        auto size = discard.size();
        for (auto i = 0; i < size; i++) {
            addCardToDeck(discard.back());
            discard.pop_back();
        }
    }

}

void Player::triggerSlot(HandPosition id,u32 frame) {
    static u32 lastTrigger = 0;


if( frame >= lastTrigger + cardUseCooldown) {

    switch (id) {
        case HandPosition::L:
            if(hand[0] != nullptr) {
                useCard(&hand[0]);
                lastTrigger = frame;
                cardCooldownState = true;
            }
            // useCard(&slotLeft);
            break;
        case HandPosition::M:
            if(hand[1] != nullptr) {

                useCard(&hand[1]);
                lastTrigger = frame;
                cardCooldownState = true;
            }
            break;
        case HandPosition::R:
            if(hand[2] != nullptr) {

                useCard(&hand[2]);
                lastTrigger = frame;
                cardCooldownState = true;
            }
            break;
    }
}
}

//takes an actual card pointer so that cards that cast other cards are easy to implement later
bool Player::useCard(Card ** slot)
{
    if(*slot != nullptr) {
        if(!(*slot)->active) {
           // Point p = {pos.x+12,pos.y};
            (*slot)->castCard(getFacingAngle(), pos);
            if((*slot)->ammo <= 0) {
                (*slot)->ammo = (*slot)->maxUses;
                addCardToDiscard(*slot);
                *slot = nullptr;
            }
        }
        return true;
    }
    return false;

}
/// TODOburn card method
/*
void Player::burnCard(Card** slot) {
    if (*slot != nullptr) {
        if (!(*slot)->active) {
            //switch((*slot).getBurnType)
            //case multicast: for(int i = 0; i<=(*slot).multicastAmount;i++){

        }
    }
}
*/

void Player::drawCard()
{
    //ugly but no time to refactor
    //handsize never changes so this is fine


        for (int i = 0; i < 3; i++) {
            if (deck.empty() && !discard.empty()) {
                shuffleDiscardIntoDeck(true);
            }
            if(drawsReady > 0) {
            if (!deck.empty()) {
                if (hand[i] == nullptr) {
                    drawsReady -= 1;
                    hand[i] = deck.back();
                    deck.pop_back();
                }
            }
        }
    }

    /*
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
*/

}

void Player::handleEvent( SDL_Event& e,u32 frame )
{

//using enum eFacingAngle; too much time was wasted trying to get this to work.
//can not get this enum namespace to work in any way. I tried updating compilers and more. Alas my directions come with eFacingAngle:: for now

    //If a key was pressed
    static bool w=false,a=false,s=false,d=false;

    //const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr );

    //aimingMode standstill toggle
    if(aimingMode){ playerVel = 0;VelX = 0; VelY = 0;}else{ playerVel = 5;}
    //lock controls if dead
if(deadOrAlive) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            // switch( e.key.keysym.sym )
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                ///maybe display a aiming line on press and fire on release?
                case SDLK_SPACE:
                    if (!aimingMode) { aimingMode = true; }
                    else { aimingMode = false; }
                    break; // cant do it like this for obvious reasons. better modify the move() with an additional toggle
                case SDLK_LEFT:
                    triggerSlot(HandPosition::L, frame);
                    break;
                case SDLK_UP:
                    triggerSlot(HandPosition::M, frame);
                    break;
                case SDLK_RIGHT:
                    triggerSlot(HandPosition::R, frame);
                    break;
                case SDLK_w:
                    VelY -= playerVel;
                    currentAngle = eFacingAngle::Up;
                    w = true;
                    break;
                case SDLK_s:
                    VelY += playerVel;
                    currentAngle = eFacingAngle::Down;
                    s = true;
                    break;
                case SDLK_a:
                    VelX -= playerVel;
                    currentAngle = eFacingAngle::Left;
                    a = true;
                    break;
                case SDLK_d:
                    VelX += playerVel;
                    currentAngle = eFacingAngle::Right;
                    d = true;
                    break;
            }
        }
            //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                //  case SDLK_SPACE:playerVel = playerVel*2;break;
                case SDLK_w:
                    VelY += playerVel;
                    w = false;
                    break;
                case SDLK_s:
                    VelY -= playerVel;
                    s = false;
                    break;
                case SDLK_a:
                    VelX += playerVel;
                    a = false;
                    break;
                case SDLK_d:
                    VelX -= playerVel;
                    d = false;
                    break;
            }
        }
        //set Velocities to 0 if not moving for internal consistency
        if (!w && !a && !s && !d) {
            VelX = 0;
            VelY = 0;
        }


        //really dumb but it works
        /*
        if(w && d){ currentAngle = eFacingAngle::UpRight;}
        if(w&&!d&&!s&&!a){currentAngle = eFacingAngle::Up;}
        if(!w&&d&&!s&&!a){currentAngle = eFacingAngle::Right;}

        if(s && d){ currentAngle = eFacingAngle::DownRight;}
        if(s&&!d&&!a&&!w){currentAngle = eFacingAngle::Down;}
        if(!s&&d&&!a&&!w){currentAngle = eFacingAngle::Right;}

        if(w&&a){currentAngle = eFacingAngle::UpLeft;}
        if(w&&!a&&!s&&!d){currentAngle = eFacingAngle::Up;}
        if(!w&&a&&!s&&!d){currentAngle = eFacingAngle::Left;}

        if(s&&a){currentAngle = eFacingAngle::DownLeft;}
        if(s&&!a&&!w&&!d){currentAngle = eFacingAngle::Down;}
        if(!s&&a&&!w&&!d){currentAngle = eFacingAngle::Left;}
        */
        //made it pretty
        if (w) {
            if (d) {
                currentAngle = eFacingAngle::UpRight;
            } else if (a) {
                currentAngle = eFacingAngle::UpLeft;
            } else {
                currentAngle = eFacingAngle::Up;
            }
        } else if (s) {
            if (d) {
                currentAngle = eFacingAngle::DownRight;
            } else if (a) {
                currentAngle = eFacingAngle::DownLeft;
            } else {
                currentAngle = eFacingAngle::Down;
            }
        } else if (d) {
            currentAngle = eFacingAngle::Right;
        } else if (a) {
            currentAngle = eFacingAngle::Left;
        }
    }

}

void Player::move(const Vector<Hitbox>& colliderList)
{
    //Move the Player left or right

    pos.x +=VelX;
    collisionRect.x += VelX;

    //If the Player went too far to the left or right and check collision list

        for (auto a: colliderList) {
            if (a.hitboxID != deadID) {
            if ((pos.x < 0) || (pos.x + PLAYER_WIDTH > SCREEN_WIDTH) ||
                SDL_HasIntersection(&collisionRect, &a.collisionRect)) {
                //Move back
                pos.x -= VelX;
                collisionRect.x -= VelX;
            }
        }
    }
    //Move the Player up or down and check collider list
    pos.y += VelY;
    collisionRect.y += VelY;

    //If the Player went too far up or down and check collision list

        for (auto a: colliderList) {
            if (a.hitboxID != deadID) {
            if ((pos.y < 0) || (pos.y + PLAYER_HEIGHT > SCREEN_HEIGHT) || SDL_HasIntersection(&collisionRect,
                                                                                              &a.collisionRect)) {
                //Move back
                pos.y -= VelY;
                collisionRect.y -= VelY;
            }
        }
    }


}