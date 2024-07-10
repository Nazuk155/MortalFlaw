//
// Created by max on 02.07.24.
//
#include <examplegame.h>


// implement the classes GameObject and Enemy, try collision and attacks
// add UI for the player stats, timer, and current hand as well as cooldown token
// next implement the classes deck and card

///next to implement: Enemy and collision

void MortalFlawState::Init()
{
    GameState::Init();


    //------------ Asset Paths
    std::string playerPath = BaseFolder "Ressources/dot.bmp";
    std::string enemyPath  = BaseFolder "Ressources/Assets/Enemy/Enemy_Sprite_Bases.bmp";

    //----------------

    p = new Player();

    /*
    if(!playerTexture)
    {
        playerTexture = IMG_LoadTexture(render,BaseFolder "/Ressources/dot.bmp");
        if(!playerTexture){print( stderr, "IMG_LoadTexture failed: {}\n", IMG_GetError() );}

    }
*/
    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );


    playerTexture = loadFromFile(playerPath);


    const Point & winSize = game.GetWindowSize();
    const Point resolution = winSize / 8;
    backgroundSurface = SDL_CreateRGBSurfaceWithFormat( 0, resolution.x, resolution.y, 32, SDL_PIXELFORMAT_RGBA32 );

}


void MortalFlawState::UnInit()
{
    SDL_DestroyTexture(playerTexture);
    playerTexture = nullptr;

}

void MortalFlawState::Events( const u32 frame, const u32 totalMSec, const float deltaT )
{
    SDL_PumpEvents();

    Event event;
    bool quit = false;

        while( SDL_PollEvent( &event ) )
        {
            if( game.HandleEvent( event ) )
                continue;



            if( event.type == SDL_QUIT )
                {
                    quit = true;
                }

                //Handle input for the player
                // This is only okay because player is unique, more players would need a player controller which is not in scope of this Project
                ///TODO fix player controls
                p->handleEvent( event );

        }



}
void MortalFlawState::Update( const u32 frame, const u32 totalMSec, const float deltaT )
{
    p->move();

}
void MortalFlawState::Render( const u32 frame, const u32 totalMSec, const float deltaT )
{

    const Point & winSize = game.GetWindowSize();

    {
       // const SDL_Rect *const dst_rect {0, 0, winSize.x, winSize.y };
        SDL_FillRect(backgroundSurface,nullptr, SDL_MapRGBA(backgroundSurface->format,white.r,white.g,white.b,white.a));
    }

    //Clear screen
    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_RenderClear( render );

    ///Write Docu for these
    renderFromSpritesheet(p->getXPos(),p->getYPos(),p->getWidth(),p->getHeight(),playerTexture);


    SDL_RenderPresent( render );

}

///is this correct? probably yes. Also put this in a Wrapper as a function no actually nothing is gained
//take the texture using the clip Rect and blit it onto target Rect
void MortalFlawState::renderFromSpritesheet(int targetX,int targetY,int targetW,int targetH,SDL_Texture* t,Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = { targetX,targetY,targetW,targetH};

    //Set clip rendering dimensions
    if( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( render, t,clip, &renderQuad, angle, center, flip );
}

//Version using a SDL_Rect to pull values from. Added for utility
void MortalFlawState::renderFromSpritesheet(Rect values,SDL_Texture* t, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect renderQuad = {values.x,values.y,values.w,values.h};

    //Set clip rendering dimensions
    if( clip != nullptr )
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