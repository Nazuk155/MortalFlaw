//
// Created by max on 01.07.24.
//
#pragma once
#include <global.h>
#include "AngleHelper.h"
#include "Card.h"

class Card;

class Player
{
public:

    bool deadOrAlive = true;

    int playerWidth = 32;
    int playerHeight = 32;

    //Maximum axis velocity of the player maybe use this later
    [[maybe_unused]] constexpr static const int PLAYER_BASESPEED = 5;
    int playerVel = 5;


    //inventory in public for ease of use
    Vector<Card*> deck;
    Vector<Card*> discard;
    Vector<Card*> ashes;

    Vector<Card*> hand;
    Card *slotLeft = nullptr;
    Card *slotRight = nullptr;
    Card *slotMiddle = nullptr;
    enum class HandPosition  {L,M,R};


    u8 health = 5;
    int drawsReady = 3;
    int maxDrawsReady = 3;
    bool aimingMode = false;
    bool abilityReady = true;

    Player();

    void handleEvent( SDL_Event& e,u32 frame );
    void move(const Vector<Hitbox>& colliderList);
    //triggers the card in selected hand position to be used
    void triggerSlot(HandPosition id,u32 frame);


    //add card to Deck pile if not nullptr
    void addCardToDeck(Card * newCard);
    //add card to Discard pile if not nullptr
    void addCardToDiscard(Card * addedCard);
    //add card to Ashes pile if not nullptr
    void addCardToAshes(Card *addedCard);
    //put Discard back into the Deck; if shuffle is set to false it simply flips the pile into the Deck
    void shuffleDiscardIntoDeck(bool shuffle = true);
    //triggers the castCard in Card Objects and puts the used card into the discard pile
    bool useCard(Card **selectedCard);
    //fills each hand card slot with cards from the deck while the  drawReady stat is >0. Additionally removes cards with 0 ammo left.
    void drawCard();

    //returns angle in 45 degree steps for rendering rotated sprites based on currentAngle
    [[nodiscard]] double getFacingAngleDouble() const {
        return static_cast<double>(static_cast<int>(currentAngle));
    }
    [[nodiscard]] eFacingAngle getFacingAngle() const {return currentAngle;}
    [[nodiscard]] int getXPos() const{return pos.x;}
    [[nodiscard]] int getYPos() const{return pos.y;}
    [[nodiscard]] int getWidth() const{return playerWidth;}
    [[nodiscard]] int getHeight() const{return playerHeight;}
    [[nodiscard]] u8 getcurrentCardUseCooldown() const{return currentCardCooldown;}
    [[nodiscard]] Rect * getCollisionRect() {return &collisionRect;}
    [[nodiscard]] Rect * getClipRect() {return &clip;}
    [[nodiscard]] Point * getPoint()  {return &pos;}
    [[nodiscard]] bool getCardUseCooldownState() const{return cardCooldownState;}
    [[nodiscard]] u32 getCurrentDrawCooldown() const{return currentDrawCooldown;}
    [[nodiscard]] u32 getCurrentOverheatCooldown() const {return currentOverheatCooldown;}
    [[nodiscard]] u32 getCurrentAbilityCooldown() const {return currentAbilityCooldown;}
    [[nodiscard]] u32 getDrawCooldown() const{return drawCooldown;}
    [[nodiscard]] u32 getOverheatCooldown() const {return overheatCooldown;}
    [[nodiscard]] u32 getAbilityCooldown() const {return abilityCooldown;}
    [[nodiscard]] u32 getDrawCooldownPercentage() const{return currentDrawCooldown/(drawCooldown/10);}
    [[nodiscard]] u32 getOverheatCooldownPercentage() const{return currentOverheatCooldown/(overheatCooldown/10);}

    //currently unused as special ability is not in scope for now
    [[maybe_unused]] [[nodiscard]] u32 getAbilityCooldownPercentage() const{return currentAbilityCooldown/(abilityCooldown/10);}


    void setXPos(int newX)noexcept{ collisionRect.x = newX;pos.x = newX; }
    void setYPos(int newY)noexcept{ collisionRect.y=newY;pos.y = newY; }
    void setWidth(int newW)noexcept{ playerWidth = newW; }
    void setHeight(int newH)noexcept{ playerHeight = newH;}
    void setVelocity(int newVx = 0,int newVy = 0)noexcept{VelX = newVx;VelY = newVy;}


    void setCardUseCooldownState(bool toggle){ cardCooldownState = toggle;}

    void advanceCurrentCardUseCooldown()noexcept{if(currentCardCooldown != 0){currentCardCooldown--;}}
    void resetCurrentCardUseCooldown()noexcept{ currentCardCooldown = cardUseCooldown;}

    void advanceCurrentDrawCooldown()noexcept{if(currentDrawCooldown > 0){currentDrawCooldown--;}}
    void resetCurrentDrawCooldown()noexcept{currentDrawCooldown = drawCooldown;}

    void advanceCurrentOverheatCooldown()noexcept{if(currentOverheatCooldown > 0){currentOverheatCooldown--;}}
    void resetCurrentOverheatCooldow()noexcept{currentOverheatCooldown = overheatCooldown;}

    void advanceCurrentAbilityCooldown()noexcept{if(currentAbilityCooldown > 0){currentAbilityCooldown--;}}
    void resetCurrentAbilityCooldown()noexcept{currentAbilityCooldown = abilityCooldown;}


private:
    Point pos;
    int VelX, VelY;
    Rect collisionRect;
    Rect clip;
    eFacingAngle currentAngle;
    bool cardCooldownState;

    // cooldowns in frames
    u8 cardUseCooldown = 30;
    u8 currentCardCooldown = 0;
    u32 drawCooldown = 180;
    u32 currentDrawCooldown = 180;
    u32 overheatCooldown = 600;
    u32 currentOverheatCooldown = 600;
    u32 abilityCooldown = 300;
    u32 currentAbilityCooldown = 300;



};