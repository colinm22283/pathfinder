#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <iostream>

#include "font.h"

TTF_Font* Font::consolas = NULL;

bool Font::init()
{
    if (TTF_Init() == -1)
    {
        std::cout << "Couldn't initialize fonts, Error: " << SDL_GetError() << "\n";
        return false;
    }

    Font::consolas = TTF_OpenFont("./fonts/consolas.ttf", 24);
    
    return true;
}