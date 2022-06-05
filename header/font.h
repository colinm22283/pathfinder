#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

namespace Font
{
    extern TTF_Font* consolas;

    bool init();
}