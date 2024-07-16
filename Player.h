//
// Created by max on 01.07.24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <global.h>
#include "AngleHelper.h"
#include "Card.h"

class Player
{
public:

    //The dimensions of the player
      int PLAYER_WIDTH = 32;
      int PLAYER_HEIGHT = 32;
    //Maximum axis velocity of the player
    constexpr static const int PLAYER_BASESPEED = 5;
    int playerVel = 5;


    //inventory in public for ease of use
    Vector<Card*> deck;
    Vector<Card*> discard;
    Vector<Card*> ashes;
    //cards in hand
    Vector<Card*> hand;
    Card *slotLeft = nullptr;
    Card *slotRight = nullptr;
    Card *slotMiddle = nullptr;
    enum class HandPosition  {L,M,R};

    //Stats
    u8 health = 5;
    int drawsReady = 3;
    int maxDrawsReady = 2;

    //state bools
    bool aimingMode = false;
    bool abilityReady = true;


    //Initializes the variables
    Player();
    //Takes key presses and activates player functions like movement
    void handleEvent( SDL_Event& e,u32 frame );

    //Moves the dot
    void move(const Vector<Hitbox>& colliderList);



    //triggers the card in selected hand position to be used
    void triggerSlot(HandPosition id,u32 frame);

    //Methods that use the Card System
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
    //fills each hand card slot with cards from the deck while the  drawReady stat is >0
    void drawCard();

    //getter Methods
    //returns angle in 45 degree steps for rendering rotated sprites based on currentAngle



    //getter methods
    [[nodiscard]] double getFacingAngleDouble() const {
        return static_cast<double>(static_cast<int>(currentAngle));
    }
    [[nodiscard]] eFacingAngle getFacingAngle() const {return currentAngle;}
    [[nodiscard]] int getXPos() const{return pos.x;}
    [[nodiscard]] int getYPos() const{return pos.y;}
    [[nodiscard]] int getWidth() const{return PLAYER_WIDTH;}
    [[nodiscard]] int getHeight() const{return PLAYER_HEIGHT;}
    [[nodiscard]] u8 getcurrentCardCooldown() const{return currentCardCooldown;}
    Rect * getCollisionRect() {return &collisionRect;}
    Rect * getClipRect() {return &clip;}
    Point * getPoint()  {return &pos;}
    [[nodiscard]] bool getCardCooldownState() const{return cardCooldownState;}
    [[nodiscard]] u32 getCurrentDrawCooldown() const{return currentDrawCooldown;}
    [[nodiscard]] u32 getCurrentOverheatCooldown() const {return currentOverheatCooldown;}
    [[nodiscard]] u32 getCurrentAbilityCooldown() const {return currentAbilityCooldown;}

    //setter Methods
    void setXPos(int newX){ collisionRect.x = newX;pos.x = newX; }
    void setYPos(int newY){ collisionRect.y=newY;pos.y = newY; }
    void setWidth(int newW){ PLAYER_WIDTH = newW; }
    void setHeight(int newH){ PLAYER_HEIGHT = newH;}
    void setVelocity(int newVx = 0,int newVy = 0){VelX = newVx;VelY = newVy;}
    void setCardCooldownState(bool toggle){cardCooldownState = toggle;}

    //special setter methods
    void advanceCurrentCardCooldown(){if(currentCardCooldown != 0){currentCardCooldown--;}}
    void resetCurrentCardCooldown(){currentCardCooldown = cardCooldown;}

    void advanceCurrentDrawCooldown(){if(currentDrawCooldown > 0){currentDrawCooldown--;}}
    void resetCurrentDrawCooldown(){currentDrawCooldown = drawCooldown;}

    void advanceCurrentOverheatCooldown(){if(currentOverheatCooldown > 0){currentOverheatCooldown--;}}
    void resetCurrentOverheatCooldow(){currentOverheatCooldown = overheatCooldown;}

    void advanceCurrentAbilityCooldown(){if(currentAbilityCooldown > 0){currentAbilityCooldown--;}}
    void resetCurrentAbilityCooldown(){currentAbilityCooldown = abilityCooldown;}


private:
    //The X and Y offsets of the player

    Point pos;
    //The velocity of the player
    int VelX, VelY;

    //Collision Box
    Rect collisionRect;
    //Spritesheet clipper box
    Rect clip;
    // enum of facing direction of player
    eFacingAngle currentAngle;

    bool cardCooldownState;

    // cooldowns in frames
    u8 cardCooldown = 30;
    u8 currentCardCooldown = 0;
    u32 drawCooldown = 180;
    u32 currentDrawCooldown = 180;
    u32 overheatCooldown = 600;
    u32 currentOverheatCooldown = 600;
    u32 abilityCooldown = 300;
    u32 currentAbilityCooldown = 300;



};




#endif //PLAYER_H
