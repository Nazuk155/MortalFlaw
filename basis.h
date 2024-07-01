//
// Created by max on 01.07.24.
//
#include <global.h>
#ifndef BASIS_H
#define BASIS_H

class Game;

class Game {


    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;


    Point windowSize;

    explicit Game(
        const char * windowTitle = "SDL Game",
        const Point  windowSize  = Point { 1024, 720 });
        //const bool   vSync       = true );

    bool init();
    void close();
    bool loadMedia();
    int Run();
};



#endif //BASIS_H
