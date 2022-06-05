#include <SDL/SDL.h>
#include <iostream>
#include <math.h>
#include <string>

#include "global.h"
#include "engine.h"
#include "render.h"
#include "console.h"
#include "font.h"

int main()
{
    if (!Engine::init())
    {
        std::cout << "Failed to initialize";
        return 1;
    }

    Engine::start();

    Engine::close();

    return 0;
}