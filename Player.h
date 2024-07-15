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

    static bool aimingMode;
    //inventory in public for ease of use
    Vector<Card*> deck;
    Vector<Card*> discard;
    Vector<Card*> burned;
    //cards in hand
    Vector<Card*> hand;
    Card *slotLeft = nullptr;
    Card *slotRight = nullptr;
    Card *slotMiddle = nullptr;
    enum class HandPosition  {L,M,R};

    //Stats
    u8 health = 5;
    float drawsReady = 100;

    //Initializes the variables
    Player();
    //Takes key presses and activates player functions like movement
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move(const Vector<Hitbox>& colliderList);



    //triggers the card in selected hand position to be used
    void triggerSlot(HandPosition id);

    //Methods that use the Card System
    //add card to Deck if not nullptr
    void addCardToDeck(Card * newCard);
    //add card to Discard if not nullptr
    void addCardToDiscard(Card * addedCard);
    //put Discard back into the Deck; if shuffle is set to false it simply flips the pile into the Deck
    void shuffleDiscardIntoDeck(bool shuffle = true);
    //triggers the castCard in Card Objects and puts the used card into the discard pile
    bool useCard(Card **selectedCard);
    //fills each hand card slot with cards from the deck while the  drawReady stat is >0
    void drawCard();

    //getter Methods
    //returns angle in 45 degree steps for rendering rotated sprites based on currentAngle
    [[nodiscard]] double getFacingAngleDouble() const;
    [[nodiscard]] eFacingAngle getFacingAngle() const;
    [[nodiscard]] int getXPos() const;
    [[nodiscard]] int getYPos() const;
    [[nodiscard]] Point * getPoint();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    Rect * getCollisionRect();
    Rect * getClipRect();
    //setter Methods
    void setXPos(int newX){ collisionRect.x = newX;pos.x = newX; }
    void setYPos(int newY){ collisionRect.y=newY;pos.y = newY; }
    void setWidth(int newW){ PLAYER_WIDTH = newW; }
    void setHeight(int newH){ PLAYER_HEIGHT = newH;}
    void setVelocity(int newVx = 0,int newVy = 0){VelX = newVx;VelY = newVy;}

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


};




#endif //PLAYER_H
