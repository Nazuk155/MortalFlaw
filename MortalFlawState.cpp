//
// Created by max on 02.07.24.
//
#include <examplegame.h>




void MortalFlawState::Init()
{
    GameState::Init();

    if(!playerTexture)
    {
        playerTexture = IMG_LoadTexture(render,BaseFolder "/Ressources/dot.png");
    }

    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

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
    while(!quit){
        while( SDL_PollEvent( &event ) )
        {
            if( game.HandleEvent( event ) )
                continue;



            if( event.type == SDL_QUIT )
                {
                    quit = true;
                }

                //Handle input for the player
                p->handleEvent( event );

        }

    }

}
void MortalFlawState::Update( const u32 frame, const u32 totalMSec, const float deltaT )
{
    p->move();

}
void MortalFlawState::Render( const u32 frame, const u32 totalMSec, const float deltaT )
{

    //Clear screen
    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

    SDL_RenderClear( render );

    ///Fix this weird stuff
    renderFromSpritesheet(playerTexture,p->getRect());


    SDL_RenderPresent( render );

}

///is this correct?
//take the texture using the clip Rect and blit it onto target Rect
void MortalFlawState::renderFromSpritesheet(SDL_Texture* t, SDL_Rect& target,Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){


    //Render to screen
    SDL_RenderCopyEx( render, t,clip, &target, angle, center, flip );
}