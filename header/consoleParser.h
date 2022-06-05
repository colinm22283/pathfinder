#pragma once

#include <string>
#include <SDL.h>

namespace ConsoleParser
{
    bool parse(std::string code);
    void keyDown(SDL_Keysym keysym);
}