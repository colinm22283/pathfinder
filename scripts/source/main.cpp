#include <math.h>
#include <iostream>

#include <global.h>
#include <script.h>
#include <engine.h>
#include <console.h>
#include <render.h>
#include <input.h>
#include <consoleParser.h>
#include <font.h>

#include <grid.h>
#include <pathfinder.h>

void Script::exit()
{
    Engine::quit();
}

void Script::start()
{
    Global::fpsLimit = 0;
    Global::fpsOutput = true;

    gridInit();
}

bool pathfinderUpdate = false;
void Script::update()
{
    Render::clearScreen();

    Render::setColor(RGB(255, 255, 255));
    Render::drawText(20, 20, Font::consolas, "Press <space> to start");

    gridPrint();

    if (Input::mouseLeft)
    {
        grid[(int)((Input::mouseX - gridOffsetX) / tileSize)][(int)((Input::mouseY - gridOffsetY) / tileSize)].type = tileType::WALL;
    }

    if (pathfinderUpdate) PATHFINDER_UPDATE();
}

void Script::keyDown(SDL_Keysym keysym)
{
    if (keysym.sym == SDLK_SPACE && !Console::visibible)
    {
        PATHFINDER_INIT();
        pathfinderUpdate = true;
    }
}

void Script::mouseDown(int button) { }
void Script::mouseClick(int button) { }

bool Script::setVar(std::string var, std::string value) { return false; }
bool Script::command(std::string cmd, std::string params) { return false; }