//
// Created by max on 02.07.24.
//
#include <examplegame.h>


///TODO cards in discard or burn that are active will be rendered until their whenActive sets active to false
// interface on the bottom with timer filling and handcards, next card on left in small, deck next to it. Right side has player ability and discard as well as burn.
//ashes cards can be restored with forge. Player has overload charges or loses a card every 10 seconds from the top of the deck.
//to not have a constantly shifting deck the player only adds cards calmly to the deck and FORGE actions basically recovers lost ammo back into the deck.

// implement the classes GameObject and Enemy, try collision and attacks
// add UI for the player stats, timer, and current hand as well as cooldown token

///TODO next to implement: hitIDSet um den selben Enemy nicht nochmal zu treffen wenn eine Karte AoE/Piercing kann. danach clip Koordinaten definieren für player und enemy spritesheet dann UI und Timer.
///Card Library mit o(1) Suchfunktion durch IDs als enums implementieren / bad idea: Karten sind Objekte die modifikationen erhalten können, besser einzelne objekte in decks als IDs mit mods.
/// random engine researchen
void MortalFlawState::Init()
{

    GameState::Init();


    //------------ Asset Paths
    std::string playerPath       =   BaseFolder "Ressources/Assets/Player/Player_Spritesheets/Player_Sprite_Bases_Bigger.png";
    std::string playerFacingPath =   BaseFolder "Ressources/Assets/Player/Player_Indicators/Player_Facing_Direction_Indicator.png";
    std::string enemyPath        =   BaseFolder "Ressources/Assets/Enemy/Enemy_Spritesheet.png";
    std::string cardDaggerPath   =   BaseFolder "/Ressources/Assets/Attacks/DAGGER/Fire_Dagger_Trimmed_Spritesheet.png";
    std::string cardSwordPath    =   BaseFolder "/Ressources/Assets/Attacks/SWORD/Player_Attack_Sword_Slash_Colors_Spritesheet.png";
    std::string uiBackgroundPath =   BaseFolder "/Ressources/Assets/UI/UI_Background.png";
    std::string uiCardBasePath   =   BaseFolder "Ressources/Assets/UI/UI_Card_Base_Spritesheet.png";
    std::string uiCardWhiteSpinPath = BaseFolder "/Ressources/Assets/UI/UI_Card_White_Spin_Spritesheet.png";

    //----------------


    //setup player
    p = new Player();
    p->setXPos(100);
    p->setYPos(100);

    //add cards to deck
    for(int i = 0;i<3;i++){
        p->addCardToDeck(new Card_Sword);
       // printf("cID = %d",p->deck.back()->cID);
        p->drawCard();
    }
    for(int i = 0;i<3;i++){
        p->addCardToDeck(new Card_Dagger);
        // printf("cID = %d",p->deck.back()->cID);
        p->drawCard();
    }


    //populate enemyVector

    for(int i= 0;i<10;i++){
       auto *temp = new Enemy();
        enemyVec.push_back(temp);
       // print("Enemy ID = %d",enemyVec.back()->getID());
    }

    /*
    if(!playerTexture)
    {
        playerTexture = IMG_LoadTexture(render,BaseFolder "/Ressources/dot.bmp");
        if(!playerTexture){print( stderr, "IMG_LoadTexture failed: {}\n", IMG_GetError() );}

    }
*/
    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

//--------------- load textures from file
    playerTexture        = loadFromFile(playerPath);
    enemyTexture         = loadFromFile(enemyPath);
    playerFacingTexture  = loadFromFile(playerFacingPath);
    cardDaggerTexture    = loadFromFile(cardDaggerPath);
    cardSwordTexture     = loadFromFile(cardSwordPath);
    uiBackgroundTexture  = loadFromFile(uiBackgroundPath);
    uiCardBaseTexture    = loadFromFile(uiCardBasePath);
    uiCardWhiteSpinTexture = loadFromFile(uiCardWhiteSpinPath);
//---------------


    const Point & winSize = game.GetWindowSize();
    const Point resolution = winSize ;


    ///TODO fix this add tiles
    backgroundSurface = SDL_CreateRGBSurfaceWithFormat( 0, resolution.x, resolution.y, 32, SDL_PIXELFORMAT_RGBA32 );

}


void MortalFlawState::UnInit()
{
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyTexture(playerFacingTexture);
    SDL_DestroyTexture(cardDaggerTexture);
    SDL_DestroyTexture(cardSwordTexture);
    SDL_DestroyTexture(uiBackgroundTexture);
    SDL_DestroyTexture(uiCardBaseTexture);


    playerFacingTexture = nullptr;
    playerTexture = nullptr;
    enemyTexture = nullptr;
    cardDaggerTexture = nullptr;
    cardSwordTexture = nullptr;
    uiBackgroundTexture  = nullptr;
    uiCardBaseTexture    = nullptr;
}

void MortalFlawState::Events( const u32 frame, const u32 totalMSec, const float deltaT ) {
    printf("Frame = %d", frame);
    printf("currentDrawCooldown = %d\n", p->getCurrentDrawCooldown());

    SDL_PumpEvents();

    Event event;


    while (SDL_PollEvent(&event)) {
        if (game.HandleEvent(event))
            continue;

        //Handle input for the player
        // This is only okay because player is unique, more players would need a player controller which is not in scope of this Project
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
    //---------------------------------------------------------------

    //respawn cooldown

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
    if(p->getCardCooldownState())
    {
            p->advanceCurrentCardCooldown();
    }
    if(p->getcurrentCardCooldown() == 0)
    {
        p->setCardCooldownState(false);
        p->resetCurrentCardCooldown();
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
        }
    }
//-----------------------------------------------------------------------------------

//enemy hitboxes and movement
    //testing multiple enemy movement and update collider list
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


    //add the GUI background as wall for player movement collision
    Hitbox guiHelper = {guiRect,notHitID};
    colliderVec.push_back(guiHelper);

    //----------------------------------------------------------------------------------------

    std::unordered_set<int> activeIDs;
    activeIDs.clear();

    activeCardsLogic(p->discard);
    activeCardsLogic(p->deck);
    activeCardsLogic(p->hand);
    activeCardsLogic(p->ashes);

   //printf(" _");
    p->move(colliderVec);
    colliderVec.clear();

    int size = enemyVec.size();
    for(int i = 0; i<size;i++)
    {
        if(!enemyVec[i]->getAliveOrDead())
        {
            //enemyDeadVec.push_back(enemyVec[i]);

        }
    }


   // printf("Deck = %zu\n",p->deck.size());
   // printf("Discard = %zu",p->discard.size());


}

void MortalFlawState::Render( const u32 frame, const u32 totalMSec, const float deltaT )
{

    const Point & winSize = game.GetWindowSize();
    SDL_SetRenderDrawColor( render, 0xFF, 0x00, 0xFF, 0xFF );
    SDL_RenderClear( render);

    //render background

       // const SDL_Rect *const dst_rect {0, 0, winSize.x, winSize.y };
       //Rect half = {0,0,winSize.x,winSize.y/2};
     //   SDL_FillRect(backgroundSurface,nullptr, SDL_MapRGBA(backgroundSurface->format,white.r,white.g,white.b,white.a));

    //render the background for the UI elements
    renderFromSpritesheet(guiRect,uiBackgroundTexture);
    //render the card slots
    setUICardClipOffset(0);
    renderFromSpritesheet(uiCardSlotLeftRect,uiCardBaseTexture,&uiCardClip);
    renderFromSpritesheet(uiCardSlotMiddleRect,uiCardBaseTexture,&uiCardClip);
    renderFromSpritesheet(uiCardSlotRightRect,uiCardBaseTexture,&uiCardClip);
    if(p->getCardCooldownState())
    {

        setUICardClipOffset(frame%4);
        renderFromSpritesheet(uiCardSlotLeftRect,uiCardWhiteSpinTexture,&uiCardClip);
    }



    ///Write Docu for these
    //render game Objects
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerTexture,&playerClipRect);
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerFacingTexture, nullptr,
                          p->getFacingAngleDouble());
   // renderFromSpritesheet(enemyInstance->getRect(), enemyTexture);


    //we render cards from discard or burn until their usage ends and they set active back to false
    for(Card*e:p->discard) {
        if (e->active) {
            switch(static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):
                    renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::Sword):
                    renderFromSpritesheet(e->cardRect,cardSwordTexture,&e->clip,e->getAttackDirectionDouble());break;

            }


        }
    }
    for(Card*e:p->deck) {
        if (e->active) {
            switch(static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):
                    renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::Sword):
                    renderFromSpritesheet(e->cardRect,cardSwordTexture,&e->clip,e->getAttackDirectionDouble());break;

            }
        }
    }
    for(Card*e:p->hand) {
        if (e != nullptr &&e->active) {
            switch(static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::Sword):renderFromSpritesheet(e->cardRect,cardSwordTexture,&e->clip,e->getAttackDirectionDouble());break;

            }
        }
    }
    for(Card*e:p->ashes) {
        if (e != nullptr &&e->active) {
            switch(static_cast<int>(e->cardName))
            {
                case static_cast<int>(eCardName::Dagger):renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());break;
                case static_cast<int>(eCardName::Sword):renderFromSpritesheet(e->cardRect,cardSwordTexture,&e->clip,e->getAttackDirectionDouble());break;

            }
        }
    }


    //render the enemy vector
    for(Enemy *a:enemyVec){
        if(a->getAliveOrDead()) {
            //check if enemy ID is in set for hit enemies
            if (setForHitEnemyIDs.find(a->getID()) != setForHitEnemyIDs.end()) {
                a->hitReaction += frame;
            }
            if (a->hitReaction >= frame) {
                a->setClipOffset(1);

            } else {
                a->setClipOffset(0);
                a->hitReaction = a->originalHitReactionTime;
            }

            renderFromSpritesheet(a->getRect(), enemyTexture, a->getClip());


            if (a->burn) {
                renderFromSpritesheet(a->getRect(), cardDaggerTexture, nullptr);
            }
        }
    }
    setForHitEnemyIDs.clear();

    SDL_RenderPresent( render );

}

void MortalFlawState::activeCardsLogic(const Vector<Card*>& cardVector)
{
    for(Card*e:cardVector)
    {
        if(e != nullptr&& e->active)
        {

            int hit = e->doWhileActive(colliderVec);
            //save the position of the hit enemys for hit reactions in setForHitEnemyIDs set for rendering hit reaction on the enemies later
            if(hit != deadID&& hit != notHitID)
            {
                setForHitEnemyIDs.insert(enemyVec[hit]->getID());
                enemyVec[hit]->takeDamage(e->dmg);
                enemyVec[hit]->killEnemyIfHP0();

            }


            if (hit <= enemyVec.size()) {
                if(e->applyDebuff)
                {
                    enemyVec[hit]->setDebuff(1);
                }
                printf("enemy vec X pos %d", enemyVec[hit]->getID());
            }

        }
    }
}

///is this correct? probably yes. No Wrapper required
//take the texture using the clip Rect and blit it onto target Rect
void MortalFlawState::renderFromSpritesheet(int targetX,int targetY,int targetW,int targetH,SDL_Texture* t,const Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip,bool useClipsize){
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

//Version using a SDL_Rect to pull values from. Added for utility
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