//
// Created by max on 01.07.24.
//

#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <global.h>


//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( std::string path,Renderer* gRenderer );

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor,Renderer* gRenderer );
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE,Renderer* = nullptr );

    //Gets image dimensions
    int getWidth();
    int getHeight();





private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};




#endif //LTEXTURE_H
