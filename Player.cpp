//
// Created by max on 01.07.24.
//

#include "Player.h"

//set aimingMode toggle to off
//bool Player::aimingMode = false;

Player::Player()
{

    pos.x = 0;
    pos.y = 0;

    VelX = 0;
    VelY = 0;

    collisionRect  = {pos.x, pos.y, playerWidth, playerHeight};

    //initialize hand with 3 slots
    hand.push_back(nullptr);
    hand.push_back(nullptr);
    hand.push_back(nullptr);
    //I should limit the Vector to a max size of 3. Refactor later

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
//also returns a bool in case i wanna do something when the player tries to use empty slots
bool Player::useCard(Card ** slot)
{


    if(*slot != nullptr) {
        if(!(*slot)->active) {
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
/// burn card method idea. Not ins scope for now
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
    //handsize never changes so this is fine
        for (int i = 0; i < 3; i++) {
            if (deck.empty() && !discard.empty()) {
                shuffleDiscardIntoDeck(true);
            }
            if(drawsReady > 0) {
            if (!deck.empty()) {
                //additional logic to handle cards like Sword that have changing amount of uses
                if(hand[i] != nullptr) {
                    if (hand[i]->ammo <= 0) {
                        if (hand[i]->ammo <= 0) {
                            hand[i]->ammo = hand[i]->maxUses;
                            addCardToDiscard(hand[i]);
                            hand[i] = nullptr;
                        }
                    }
                }
                if (hand[i] == nullptr) {
                    drawsReady -= 1;
                    hand[i] = deck.back();
                    deck.pop_back();
                }
            }
        }
    }
}

void Player::handleEvent( SDL_Event& e,u32 frame )
{

//using enum eFacingAngle;
//too much time was wasted trying to get this to work.
//can not get this enum namespace to work in any way. I tried updating compilers and more. Alas my directions come with eFacingAngle:: for now

    static bool w=false,a=false,s=false,d=false;


    //aimingMode standstill toggle
    if(aimingMode){ playerVel = 0;VelX = 0; VelY = 0;}else{ playerVel = 5;}

    //lock controls if dead
if(deadOrAlive) {
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
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
    pos.x +=VelX;
    collisionRect.x += VelX;

    //reset player if they get pushed out of screen bounds for some reason
    if(pos.x > SCREEN_WIDTH||pos.x< 0){ pos.x = SCREEN_WIDTH/2;}
    if(pos.y > SCREEN_HEIGHT||pos.y< 0){ pos.y = SCREEN_HEIGHT/2;}


        for (auto a: colliderList) {
            if (a.hitboxID != deadID) {
            if ((pos.x < 0) || (pos.x + playerWidth > SCREEN_WIDTH) ||
                SDL_HasIntersection(&collisionRect, &a.collisionRect)) {
                //Move back
                pos.x -= VelX;
                collisionRect.x -= VelX;
            }
        }
    }
    pos.y += VelY;
    collisionRect.y += VelY;

        for (auto a: colliderList) {
            if (a.hitboxID != deadID) {
            if ((pos.y < 0) || (pos.y + playerHeight > SCREEN_HEIGHT) || SDL_HasIntersection(&collisionRect,
                                                                                             &a.collisionRect)) {
                //Move back
                pos.y -= VelY;
                collisionRect.y -= VelY;
            }
        }
    }
}