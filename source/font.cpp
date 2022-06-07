#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

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
    if (Font::consolas == nullptr)
    {
        std::cout << "Font ttf file not found \"./fonts/consolas.ttf\"\n";
        return false;
    }
    
    return true;
}

void Font::cleanup()
{
    TTF_CloseFont(Font::consolas);
}