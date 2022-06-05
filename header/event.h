#pragma once

#include <SDL.h>

namespace Event
{
    extern SDL_Event event;

    void init();
    void update();
}