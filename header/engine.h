#pragma once

#include <SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

namespace Engine
{
    extern bool running;
    extern long currentTime;
    extern long deltaTime;

    bool init(); //                                        Initialize the engine
    void quit(); //                                        Quit the engine
    void awaitQuit();

    void start();
    void update();

    void timerUpdate();
}