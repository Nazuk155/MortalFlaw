//
// Created by max on 02.07.24.
//
#include <examplegame.h>


///TODO cards in discard or burn that are active will be rendered until their whenActive sets active to false
// interface on the bottom with timer filling and handcards, next card on left in small, deck next to it. Right side has player ability and discard as well as burn.
//burned cards can be restored with forge. Player has overload charges or loses a card every 10 seconds from the top of the deck.
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
    std::string playerPath = BaseFolder "Ressources/Assets/Player/Player_Spritesheets/Player_Sprite_Bases_Bigger.png";
    std::string playerFacingPath = BaseFolder "Ressources/Assets/Player/Player_Indicators/Player_Facing_Direction_Indicator.png";
    std::string enemyPath  = BaseFolder "Ressources/Assets/Enemy/Enemy_Sprite_Bases.bmp";
    std::string cardDaggerPath = BaseFolder "/Ressources/Assets/Attacks/DAGGER/Fire_Dagger_Trimmed_Spritesheet.png";

    //----------------


    //setup player
    p = new Player();
    p->setXPos(100);
    p->setYPos(100);

    //add cards to deck
    for(int i = 0;i<10;i++){
        p->addCardToDeck(new Card_Dagger);
       // printf("cID = %d",p->deck.back()->cID);
       // p->deck.push_back(new Card_Dagger);
        p->drawCard();
    }
    //set initial card render position
    /*
    for(Card*a:p->deck){
        a->cardRect.x = p->getXPos();
        a->cardRect.y = p->getYPos();
    }
*/

    //populate enemyVector
    enemyInstance = new Enemy();
    for(int i= 0;i<10;i++){
       auto *temp = new Enemy();
        enemyVec.push_back(temp);
    }

    /*
    if(!playerTexture)
    {
        playerTexture = IMG_LoadTexture(render,BaseFolder "/Ressources/dot.bmp");
        if(!playerTexture){print( stderr, "IMG_LoadTexture failed: {}\n", IMG_GetError() );}

    }
*/
    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );


    playerTexture = loadFromFile(playerPath);
    enemyTexture = loadFromFile(enemyPath);
    playerFacingTexture = loadFromFile(playerFacingPath);
    cardDaggerTexture = loadFromFile(cardDaggerPath);

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
    playerFacingTexture = nullptr;
    playerTexture = nullptr;
    enemyTexture = nullptr;
    cardDaggerTexture = nullptr;
}

void MortalFlawState::Events( const u32 frame, const u32 totalMSec, const float deltaT )
{
    SDL_PumpEvents();

    Event event;


        while( SDL_PollEvent( &event ) )
        {
            if( game.HandleEvent( event ) )
                continue;

            //Handle input for the player
            // This is only okay because player is unique, more players would need a player controller which is not in scope of this Project
            p->handleEvent( event );

        }



}
void MortalFlawState::Update( const u32 frame, const u32 totalMSec, const float deltaT ) {


    p->drawCard();
    //testing velocity
    //enemyInstance->setVelocity(2, 2);
    enemyInstance->setXPos(100);
    enemyInstance->move();

    //testing multiple enemy movement and update collider list
    int plus = 1;
    int pos = 32;

    for (Enemy *a: enemyVec) {
        a->setYPos(pos * plus);
        a->setVelocity(0, plus);
        a->move();
        //update collision box table
        colliderVec.push_back(a->getRect());
        plus++;

    }
    colliderVec.push_back(enemyInstance->getRect());
    ///TODO add the discard and burn for loop to iterate through the instances of that are active and start their doWhileActive
    //Vector activeCards collects all cards with active = true and triggers their doWhileActive

    std::unordered_set<int> activeIDs;
    activeIDs.clear();

    for(Card*e:p->discard)
    {
        if(e->active)
        {
            if (activeIDs.find(e->cID) == activeIDs.end()) {
                activeIDs.insert(e->cID);
            }

            int hits = e->doWhileActive(colliderVec);

            if (hits <= enemyVec.size()) {
                ///TODO do this next
                /* card is active until all possible hits have been dealt or max rand/wall is hit
                 * on hit the hitIDSet adds the enemy to its list so it can not be hit again
                 * hitIDSet resets when active time of card ends
                 * */


                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
                enemyVec[hits]->setXPos(enemyVec[hits]->getRect().x + 100);
                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
            }

        }
    }
    for(Card*e:p->deck)
    {
        if(e->active) {

            if (activeIDs.find(e->cID) != activeIDs.end()) {
                activeIDs.insert(e->cID);
            }
            int hits = e->doWhileActive(colliderVec);

            if (hits <= enemyVec.size()) {
                ///TODO do this next
                /* card is active until all possible hits have been dealt or max rand/wall is hit
                 * on hit the hitIDSet adds the enemy to its list so it can not be hit again
                 * hitIDSet resets when active time of card ends
                 * */


                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
                enemyVec[hits]->setXPos(enemyVec[hits]->getRect().x + 100);
                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
            }

        }
    }
    for(Card*e:p->hand)
    {
        if(e != nullptr &&e->active)
        {
            if (activeIDs.find(e->cID) != activeIDs.end()) {
                activeIDs.insert(e->cID);
            }
            int hits = e->doWhileActive(colliderVec);

            if (hits <= enemyVec.size()) {
                ///TODO do this next
                /* card is active until all possible hits have been dealt or max rand/wall is hit
                 * on hit the hitIDSet adds the enemy to its list so it can not be hit again
                 * hitIDSet resets when active time of card ends
                 * */


                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
                enemyVec[hits]->setXPos(enemyVec[hits]->getRect().x + 100);
                printf("enemy vec X pos %d", enemyVec[hits]->getRect().x);
            }
        }
    }

            //printf("cID = %d",e->cID);
            //fix magic number here
            //  e->cardRect.x = p->getCollisionRect()->x;
            // e->cardRect.y = p->getCollisionRect()->y;
            //add the doWhenActive here





    printf(" _");
    p->move(colliderVec);
    colliderVec.clear();


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






    ///Write Docu for these
    //render game Objects
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerTexture,&playerClipRect);
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerFacingTexture, nullptr,
                          p->getFacingAngleDouble());
    renderFromSpritesheet(enemyInstance->getRect(), enemyTexture);


    //we render cards from discard or burn until their usage ends and they set active back to false
    for(Card*e:p->discard) {
        if (e->active) {
            renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());
        }
    }


    for(Card*e:p->deck) {
        if (e->active) {
            renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());
        }
    }
    for(Card*e:p->hand) {
        if (e != nullptr &&e->active) {
            renderFromSpritesheet(e->cardRect,cardDaggerTexture,&e->clip,e->getAttackDirectionDouble());
        }
    }

    //render the enemy vector
    for(Enemy *a:enemyVec){
        renderFromSpritesheet(a->getRect(),enemyTexture);
    }

    SDL_RenderPresent( render );

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
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}