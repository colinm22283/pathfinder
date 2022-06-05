#pragma once

#include <SDL/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

namespace Engine
{
    extern bool quit;
    extern long currentTime;
    extern long deltaTime;

    bool init(); //                                        Initialize the engine
    void close(); //                                       Stop the engine

    void start();
    void update();

    void timerUpdate();
}