#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

namespace Font
{
    extern TTF_Font* consolas;

    bool init();
}