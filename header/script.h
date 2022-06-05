#pragma once

#include "SDL/SDL.h"

namespace Script
{
    void start();
    void update();
    void keyDown(SDL_Keysym keysym);
    void mouseDown(int button);
    void mouseClick(int button);
    void exit();
    bool setVar(std::string var, std::string value);
    bool command(std::string cmd, std::string params);
}