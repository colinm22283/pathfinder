#pragma once

#include "SDL/SDL.h"
#include <string>
#include <vector>

namespace Console
{
    extern bool visibible;
    extern std::string output;
    extern std::string input;
    extern std::vector<std::string> history;

    void print(std::string message);
    void update();
    void keyDown(SDL_Keysym keysym);
}