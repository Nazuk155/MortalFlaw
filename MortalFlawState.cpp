//
// Created by max on 02.07.24.
//
#include <examplegame.h>



// interface on the bottom with timer filling and handcards, next card on left in small, deck next to it. Right side has player ability and discard as well as burn pile.
//ashes cards can be restored with forge. Player has overload charges or loses a card every 10 seconds from the top of the deck.
//to not have a constantly shifting deck the player only adds cards calmly to the deck and FORGE actions basically recovers lost ammo back into the deck

void MortalFlawState::Init()
{

    GameState::Init();


    //------------ Asset Paths
    std::string playerPath          =   BaseFolder "/Ressources/Assets/Player/Player_Spritesheets/Player_Sprite_Bases_Bigger.png";
    std::string playerFacingPath    =   BaseFolder "/Ressources/Assets/Player/Player_Indicators/Player_Facing_Direction_Indicator.png";
    std::string enemyPath           =   BaseFolder "/Ressources/Assets/Enemy/Enemy_Spritesheet.png";
    std::string cardDaggerPath      =   BaseFolder "/Ressources/Assets/Attacks/DAGGER/Fire_Dagger_Trimmed_Spritesheet.png";
    std::string cardSwordPath       =   BaseFolder "/Ressources/Assets/Attacks/SWORD/Player_Attack_Sword_Slash_Colors_Spritesheet.png";
    std::string cardForgeStrikePath =   BaseFolder "/Ressources/Assets/Attacks/FORGESTRIKE/Player_Attack_ForgeStrike_Spritesheet.png";
    std::string uiBackgroundPath    =   BaseFolder "/Ressources/Assets/UI/UI_Background.png";
    std::string uiCardBasePath      =   BaseFolder "/Ressources/Assets/UI/UI_Card_Base_Spritesheet.png";
    std::string uiCardWhiteSpinPath =   BaseFolder "/Ressources/Assets/UI/UI_Card_White_Spin_Spritesheet.png";
    std::string uiBarWhiteRedPath   =   BaseFolder "/Ressources/Assets/UI/UI_Bar_WHITE_RED_Spritesheet.png";
    std::string uiBarYellowBluePath =   BaseFolder "/Ressources/Assets/UI/UI_Bar_YELLOW_BLUE_Spritesheet.png";
    std::string uiPilesPath         =   BaseFolder "/Ressources/Assets/UI/UI_Piles_DECK_DISCARD_BURN_Spritesheet.png";
    std::string uiDrawReadyIconPath =   BaseFolder "/Ressources/Assets/UI/UI_DrawReady_Icon_Spritesheet.png";
    std::string uiNumbersPath       =   BaseFolder "/Ressources/Assets/UI/UI_Numbers_Spritesheet.png";


    //----------------


    //setup player
    p = new Player();
    p->setXPos(100);
    p->setYPos(100);

    //add cards to discard and leave deck empty to trigger a shuffle and give a random starting hand

    for(int i = 0;i<2;i++){
      //p->addCardToDeck(new Card_Dagger);
        p->addCardToDiscard(new Card_Sword);
        p->addCardToDiscard(new Card_ForgeStrike);
        // printf("cID = %d",p->deck.back()->cID);

    }
    for(int i = 0;i<5;i++){
        //p->addCardToDeck(new Card_Sword);
        p->addCardToDiscard(new Card_Dagger);
        // p->addCardToDeck(new Card_ForgeStrike);
        p->drawCard();
        p->drawsReady = p->maxDrawsReady;
    }


    //populate enemyVector

    for(int i= 0;i<10;i++){
       auto *temp = new Enemy();
        enemyVec.push_back(temp);
       // print("Enemy ID = %d",enemyVec.back()->getID());
    }


    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

//--------------- load textures from file
    playerTexture           = loadFromFile(playerPath);
    enemyTexture            = loadFromFile(enemyPath);
    playerFacingTexture     = loadFromFile(playerFacingPath);
    cardDaggerTexture       = loadFromFile(cardDaggerPath);
    cardSwordTexture        = loadFromFile(cardSwordPath);
    cardForgeStrikeTexture  = loadFromFile(cardForgeStrikePath);
    uiBackgroundTexture     = loadFromFile(uiBackgroundPath);
    uiCardBaseTexture       = loadFromFile(uiCardBasePath);
    uiCardWhiteSpinTexture  = loadFromFile(uiCardWhiteSpinPath);
    uiBarWhiteRedTexture    = loadFromFile(uiBarWhiteRedPath);
    uiBarYellowBlueTexture  = loadFromFile(uiBarYellowBluePath);
    uiPilesTexture          = loadFromFile(uiPilesPath);
    uiDrawReadyIconTexture  = loadFromFile(uiDrawReadyIconPath);
    uiNumbersTexture        = loadFromFile(uiNumbersPath);


//---------------


    const Point & winSize = game.GetWindowSize();
    const Point resolution = winSize ;


    ///replace this with a tileset late.
   // backgroundSurface = SDL_CreateRGBSurfaceWithFormat( 0, resolution.x, resolution.y, 32, SDL_PIXELFORMAT_RGBA32 );

   //fill the helper vector with the card Icons
    uiCard_IconVector.push_back(uiCard_IconLeftRect);
    uiCard_IconVector.push_back(uiCard_IconMiddleRect);
    uiCard_IconVector.push_back(uiCard_IconRightRect);

}

void MortalFlawState::UnInit()
{
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(playerFacingTexture);
    SDL_DestroyTexture(cardDaggerTexture);
    SDL_DestroyTexture(cardSwordTexture);
    SDL_DestroyTexture(cardForgeStrikeTexture);
    SDL_DestroyTexture(uiBackgroundTexture);
    SDL_DestroyTexture(uiCardBaseTexture);
    SDL_DestroyTexture(uiBarYellowBlueTexture);
    SDL_DestroyTexture(uiBarWhiteRedTexture);
    SDL_DestroyTexture(uiPilesTexture);
    SDL_DestroyTexture(uiDrawReadyIconTexture);
    SDL_DestroyTexture(uiNumbersTexture);

    playerFacingTexture = nullptr;
    playerTexture = nullptr;
    enemyTexture = nullptr;
    cardDaggerTexture = nullptr;
    cardSwordTexture = nullptr;
    cardForgeStrikeTexture = nullptr;
    uiBackgroundTexture  = nullptr;
    uiCardBaseTexture    = nullptr;
    uiBarYellowBlueTexture = nullptr;
    uiBarWhiteRedTexture = nullptr;
    uiPilesTexture = nullptr;
    uiDrawReadyIconTexture = nullptr;
    uiNumbersTexture = nullptr;
}

void MortalFlawState::Events( const u32 frame, const u32 totalMSec, const float deltaT ) {
   // printf("Frame = %d", frame);
   // printf("currentDrawCooldown = %d\n", p->getCurrentDrawCooldown());

    SDL_PumpEvents();

    Event event;


    while (SDL_PollEvent(&event)) {
        if (game.HandleEvent(event))
            continue;

        //Handle input for the player
        // This is only okay because player is unique, more players would need a different approach
        p->handleEvent(event, frame);

        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            // switch( e.key.keysym.sym )
            //Adjust the velocity
            switch (event.key.keysym.sym) {
                case SDLK_r:
                    if (!respawnToggle) { respawnToggle = true; }
                    else { respawnToggle = false; }
            }

        }
    }
}




void MortalFlawState::Update( const u32 frame, const u32 totalMSec, const float deltaT ) {

    //draw cards before handling events to update the vectors before operations happen on them
    p->drawCard();

    //manage cooldown timers
    manageCooldowns(frame);

    //enemy hitboxes and movement
    int plus = 1;
    int pos = 32;

    for (Enemy *a: enemyVec) {
        a->setYPos(pos * plus);
        if(a->getRect().x > SCREEN_WIDTH-a->getRect().w*2)
        {
            a->setVelocity(-2,0);
        }
        if(a->getRect().x < 0 +a->getRect().w)
        {
            a->setVelocity(2, 0);
        }
        a->move();
        //update collision box table
        colliderVec.push_back(a->getHitbox());
        plus++;
    }


    //add the GUI background as wall for player movement collision. Also set hitbox ID to dead
   // Hitbox guiHelper = {guiRect,deadID};
    colliderVec.push_back({guiRect,notHitID});

    //----------------------------------------------------------------------------------------

    //in case i ever want multiple cards active at the same time we use this set
    //std::unordered_set<int> activeIDs;
    //activeIDs.clear();

    //handle all the active cards in each pile
    activeCardsLogic(p->discard,frame);
    activeCardsLogic(p->deck,frame);
    activeCardsLogic(p->hand,frame);
    activeCardsLogic(p->ashes,frame);

    //
    p->move(colliderVec);
    colliderVec.clear();

    if(p->deck.empty()&&p->discard.empty()&&p->hand[0] == nullptr&&p->hand[1] == nullptr && p->hand[2] == nullptr)
    {
        p->deadOrAlive = false;
    }


   // printf("Deck = %zu\n",p->deck.size());
   // printf("Discard = %zu",p->discard.size());


}

void MortalFlawState::Render( const u32 frame, const u32 totalMSec, const float deltaT )
{

    const Point & winSize = game.GetWindowSize();
    SDL_SetRenderDrawColor( render, 0x7F, 0x00, 0x7F, 0x00 );
    if(!p->deadOrAlive)
    {
        SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF );
    }
    SDL_RenderClear( render);


     /// NOTE: UI ELEMENTS   !!!
     /*GUI needs refactoring. I slapped this together real quick.
      * All UI pieces probably need to go into their own classes just like Ui_Bar and
      * get assembled into logical units by a composer class.
      * Looks even worse in gamestate.h. But out of scope for now.*/
     ///-------------------------------------------------------------------------
    //render the background for the UI elements
    renderFromSpritesheet(guiRect,uiBackgroundTexture);
    //render the card slots
    setUICardClipOffset(0);
    renderFromSpritesheet(uiCard_SlotLeftRect, uiCardBaseTexture, &uiCard_Clip);
    renderFromSpritesheet(uiCard_SlotMiddleRect, uiCardBaseTexture, &uiCard_Clip);
    renderFromSpritesheet(uiCard_SlotRightRect, uiCardBaseTexture, &uiCard_Clip);

    //render empty slot red
    for(int i = 0;i<3;i++)
    {
        if(p->hand[i] == nullptr)
        {
            switch(i)
            {
                case 0:setUICardClipOffset(2);renderFromSpritesheet(uiCard_SlotLeftRect, uiCardBaseTexture, &uiCard_Clip);break;
                case 1:setUICardClipOffset(2);renderFromSpritesheet(uiCard_SlotMiddleRect, uiCardBaseTexture, &uiCard_Clip);break;
                case 2:setUICardClipOffset(2);renderFromSpritesheet(uiCard_SlotRightRect, uiCardBaseTexture, &uiCard_Clip);break;

            }
        }
    }
    //render white spin when "animation lock" is simulated by cardUseCooldown
    if(p->getCardUseCooldownState())
    {
        //conversion is fine here
        setUICardClipOffset(frame%4);

        renderFromSpritesheet(uiCard_SlotLeftRect, uiCardWhiteSpinTexture, &uiCard_Clip);
        renderFromSpritesheet(uiCard_SlotMiddleRect, uiCardWhiteSpinTexture, &uiCard_Clip);
        renderFromSpritesheet(uiCard_SlotRightRect, uiCardWhiteSpinTexture, &uiCard_Clip);
    }

    setUIPileClipOffset(0);
    renderFromSpritesheet(uiPile_DeckRect, uiPilesTexture, &uiPile_Clip);
    setUIPileClipOffset(1);
    renderFromSpritesheet(uiPile_DiscardRect, uiPilesTexture, &uiPile_Clip);
    setUIPileClipOffset(2);
    renderFromSpritesheet(uiPile_BurnRect, uiPilesTexture, &uiPile_Clip);


    int i = 0;
    for(auto e: p->hand)
    {
        if(e != nullptr) {
            switch (static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):renderFromSpritesheet(uiCard_IconVector[i],cardDaggerTexture,&e->clip);break;
                case static_cast<int>(eCardName::Sword):renderFromSpritesheet(uiCard_IconVector[i],cardSwordTexture,&e->clip);break;
                case static_cast<int>(eCardName::ForgeStrike):renderFromSpritesheet(uiCard_IconVector[i],cardForgeStrikeTexture,&e->clip);break;

            }

        }
        i++;
    }

    //Numbers
    if(!p->deck.empty()) {
        setUINumbersClipOffset(p->deck.size()-1);
        if(p->deck.size()>9)
        {
            setUINumbersClipOffset(9);
        }
        renderFromSpritesheet(uiNumbers_DeckCounterRect, uiNumbersTexture, &uiNumbers_Clip);
    }
    if(!p->discard.empty()) {
        setUINumbersClipOffset(p->discard.size()-1);
        if(p->discard.size()>9)
        {
            setUINumbersClipOffset(9);
        }
        renderFromSpritesheet(uiNumbers_DiscardCounterRect, uiNumbersTexture, &uiNumbers_Clip);
    }
    if(!p->ashes.empty()) {
        setUINumbersClipOffset(p->ashes.size()-1);
        if(p->ashes.size()>9)
        {
            setUINumbersClipOffset(9);
        }
        renderFromSpritesheet(uiNumbers_AshesCounterRect, uiNumbersTexture, &uiNumbers_Clip);
    }


    //UI BARS (only cooldowns for now)

    renderFromSpritesheet(uiBar_DrawBar._backgroundRect, uiBarYellowBlueTexture, &uiBar_DrawBar._backgroundClip);
    uiBar_DrawBar.setUIBarDrawFillerPercent(p->getDrawCooldownPercentage());
    renderFromSpritesheet(uiBar_DrawBar._fillerRect, uiBarYellowBlueTexture, &uiBar_DrawBar._fillerClip);

    renderFromSpritesheet(uiBar_OverheatBar._backgroundRect, uiBarWhiteRedTexture, &uiBar_OverheatBar._backgroundClip);
    uiBar_OverheatBar.setUIBarDrawFillerPercent(p->getOverheatCooldownPercentage());
    renderFromSpritesheet(uiBar_OverheatBar._fillerRect, uiBarWhiteRedTexture, &uiBar_OverheatBar._fillerClip);

    //DRAW READY ICONS

    //this is fine for now. Refactor later when player can get more than 3 maxDrawsReady
    if(p->drawsReady >= 1)
    {
        setUIIconDrawReadyClipOffset(0);
        renderFromSpritesheet(uiIcon_1DrawReadyRect, uiDrawReadyIconTexture, &uiIcon_DrawReadyClip);
    }
    if(p->drawsReady >= 2)
    {
        setUIIconDrawReadyClipOffset(1);
        renderFromSpritesheet(uiIcon_2DrawReadyRect, uiDrawReadyIconTexture, &uiIcon_DrawReadyClip);
    }
    if(p->drawsReady >= 3)
    {
        setUIIconDrawReadyClipOffset(2);
        renderFromSpritesheet(uiIcon_3DrawReadyRect, uiDrawReadyIconTexture, &uiIcon_DrawReadyClip);
    }



    ///Write Docu for these
    //render player and player facing indicator
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerTexture,&playerClipRect);
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerFacingTexture, nullptr,
                          p->getFacingAngleDouble());


    renderActiveCardsInVector(p->discard);
    renderActiveCardsInVector(p->deck);
    renderActiveCardsInVector(p->hand);
    renderActiveCardsInVector(p->ashes);


    //render the enemy vector
    for(Enemy *a:enemyVec){
        if(a->getAliveOrDead()) {
            ///TODO: probably refactor this into enemy
            //set enemy sprite visual based on HP

            //check if enemy ID is in set for hit enemies
            if (setForHitEnemyIDs.find(a->getID()) != setForHitEnemyIDs.end()) {
                a->hitReaction += frame;
            }
            if (a->hitReaction >= frame) {
                a->setClipOffset(1);

            } else {
                switch(a->getHP())
                {
                    case 6:a->setClipOffset(2);break;
                    case 5:a->setClipOffset(2);break;
                    case 4:a->setClipOffset(4);break;
                    case 3:a->setClipOffset(4);break;
                    case 2:a->setClipOffset(0);break;
                    case 1:a->setClipOffset(0);break;
                    default:a->setClipOffset(2);break;
                }
                a->hitReaction = a->originalHitReactionTime;
            }

            renderFromSpritesheet(a->getRect(), enemyTexture, a->getClip());

            if (a->vulnerable) {
                if(a->vulnerableTimer > frame) {
                    renderFromSpritesheet(a->getRect(), cardDaggerTexture, nullptr);
                }else{a->setVulnerable(false);}
            }
        }
    }
    setForHitEnemyIDs.clear();

    SDL_RenderPresent( render );

}

void MortalFlawState::manageCooldowns(u32 frame)
{

    if(respawnToggle)
    {
        if(frame%300 == 0)
        {
            for(auto e:enemyVec)
            {
                if(!e->getAliveOrDead())
                    e->respawn(e->originalSpawn.x,e->originalSpawn.y);
            }
        }
    }
    //card use cooldown
    if(p->getCardUseCooldownState())
    {
        p->advanceCurrentCardUseCooldown();
    }
    if(p->getcurrentCardUseCooldown() == 0)
    {
        p->setCardUseCooldownState(false);
        p->resetCurrentCardUseCooldown();
    }

    // draw ressource cooldown
    p->advanceCurrentDrawCooldown();
    if(p->getCurrentDrawCooldown() == 0)
    {
        if(p->drawsReady < p->maxDrawsReady) {
            p->drawsReady++;
        }
        p->resetCurrentDrawCooldown();
    }
    //special ability cooldown
    //unused so far. not in scope for now
    if(p->abilityReady) {
        p->advanceCurrentAbilityCooldown();
    }
    if(p->getCurrentAbilityCooldown() == 0)
    {
        p->resetCurrentAbilityCooldown();
    }
    //overheat punishment cooldown
    p->advanceCurrentOverheatCooldown();
    if(p->getCurrentOverheatCooldown() == 0)
    {
        if(!p->deck.empty()) {
            p->addCardToAshes(p->deck.back());
            p->deck.pop_back();
            p->resetCurrentOverheatCooldow();
        }else
        {
                if(!p->discard.empty())
                {
                    p->addCardToAshes(p->discard.back());
                    p->discard.pop_back();
                    p->resetCurrentOverheatCooldow();
                }else
                {
                        for(int i = 0; i<3;i++)
                        {
                            if(p->hand[i]!= nullptr)
                            {
                                p->addCardToAshes(p->hand[i]);
                                p->hand[i] = nullptr;
                                p->resetCurrentOverheatCooldow();
                                break;
                            }
                        }

                }
        }
    }
}

void MortalFlawState::activeCardsLogic(const Vector<Card*>& cardVector, u32 frame)
{
    for(Card*e:cardVector)
    {
        if(e != nullptr&& e->active)
        {

            int hit = e->doWhileActive(colliderVec, frame, p);
            //save the position of the hit enemys for hit reactions in setForHitEnemyIDs set for rendering hit reaction on the enemies later
            if(hit != deadID&& hit != notHitID)
            {
                //double check to make sure we dont try to hit things that have collision but are not in enemyVec
                if(colliderVec[hit].hitboxID != notHitID&&colliderVec[hit].hitboxID != deadID) {
                    setForHitEnemyIDs.insert(enemyVec[hit]->getID());
                    enemyVec[hit]->takeDamage(e->dmg);
                    enemyVec[hit]->killEnemyIfHP0();
                    // if(!enemyVec[hit]->aliveOrDead){}
                }

            }
            if (hit <= enemyVec.size()) {
                if(e->applyDebuff)
                {
                    enemyVec[hit]->setVulnerable(true);
                    enemyVec[hit]->vulnerableTimer = frame+ enemyVec[hit]->vulnerableDuration;
                }
               // printf("enemy vec X pos %d", enemyVec[hit]->getID());
            }

        }
    }
}

//add each new card here
void MortalFlawState::renderActiveCardsInVector(const Vector<Card*>& cardVector)
{
    for(Card*e:cardVector) {
        if (e != nullptr &&e->active) {
            switch(static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::Sword):renderFromSpritesheet(e->cardRect,cardSwordTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::ForgeStrike):renderFromSpritesheet(e->cardRect,cardForgeStrikeTexture,&e->clip,e->getAttackDirectionDouble());break;

            }
        }
    }

}
///is this correct? probably yes. No Wrapper required
//take the texture using the clip Rect and blit it onto target Rect
void MortalFlawState::renderFromSpritesheet(int targetX,int targetY,int targetW,int targetH,SDL_Texture* t,const Rect* clip, double angle,
                                            SDL_Point* center, SDL_RendererFlip flip,bool useClipsize)
{
    SDL_Rect renderQuad = { targetX,targetY,targetW,targetH};

    //Set clip rendering dimensions
    if( clip != nullptr && useClipsize)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( render, t,clip, &renderQuad, angle, center, flip );
}

//Version using a SDL_Rect to pull values from. Added for utility and because everything should have a Rect
void MortalFlawState::renderFromSpritesheet(Rect values,SDL_Texture* t, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,bool useClipSize){
    SDL_Rect renderQuad = {values.x,values.y,values.w,values.h};

    //Set clip rendering dimensions
    if( clip != nullptr && useClipSize)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( render, t,clip, &renderQuad, angle, center, flip );
}

//result should be saved in a texture related to a object within MortalFlawState. Surface Width/Height should match player width/height otherwise texture needs to be scaled.
Texture* MortalFlawState::loadFromFile(const std::string& path){

    Texture * newTexture = nullptr;
    Surface * loadedSurface =  IMG_Load(path.c_str());

    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( render, loadedSurface );
        if( !newTexture  )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}