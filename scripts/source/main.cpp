#include <iostream>

#include <global.h>
#include <script.h>
#include <engine.h>
#include <console.h>
#include <render.h>
#include <input.h>
#include <font.h>

#include <grid.h>
#include <pathfinder.h>

enum gridTool { DRAW, ERASE, START, GOAL };

gridTool currentTool = gridTool::DRAW;

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
    Render::drawText(20, 20, Font::consolas, "Press <space> to start, <tab> to swap tools");
    Render::drawText(
        650, 20, Font::consolas,
        "(" +
        std::to_string((int)((Input::mouseX - gridOffsetX) / tileSize)) +
        ", " +
        std::to_string((int)((Input::mouseY - gridOffsetY) / tileSize)) +
        ")"
    );
    switch (currentTool)
    {
    case DRAW: Render::drawText(650, 50, Font::consolas, "Draw"); break;
    case ERASE: Render::drawText(650, 50, Font::consolas, "Erase"); break;
    case START: Render::drawText(650, 50, Font::consolas, "Start"); break;
    case GOAL: Render::drawText(650, 50, Font::consolas, "Goal"); break;
    }

    gridPrint();

    if (Input::mouseLeft)
    {
        if (
            Input::mouseX >= gridOffsetX && Input::mouseX <= gridOffsetX + GRID_WIDTH * tileSize &&
            Input::mouseY >= gridOffsetY && Input::mouseY <= gridOffsetY + GRID_HEIGHT * tileSize
        ) switch (currentTool)
        {
        case DRAW: grid[(int)((Input::mouseX - gridOffsetX) / tileSize)][(int)((Input::mouseY - gridOffsetY) / tileSize)].type = tileType::WALL; break;
        case ERASE: grid[(int)((Input::mouseX - gridOffsetX) / tileSize)][(int)((Input::mouseY - gridOffsetY) / tileSize)].type = tileType::EMPTY; break;
        case START: startPosX = (Input::mouseX - gridOffsetX) / tileSize; startPosY = (Input::mouseY - gridOffsetY) / tileSize; break;
        case GOAL: goalPosX = (Input::mouseX - gridOffsetX) / tileSize; goalPosY = (Input::mouseY - gridOffsetY) / tileSize; break;
        }
    }

    if (pathfinderUpdate) PATHFINDER_UPDATE();
}

void Script::keyDown(SDL_Keysym keysym)
{
    if (!Console::visibible) {
        switch (keysym.sym)
        {
        case SDLK_SPACE:
            PATHFINDER_INIT();
            pathfinderUpdate = true;
            break;
        case SDLK_TAB:
            switch (currentTool)
            {
            case DRAW: currentTool = gridTool::ERASE; break;
            case ERASE: currentTool = gridTool::START; break;
            case START: currentTool = gridTool::GOAL; break;
            case GOAL: currentTool = gridTool::DRAW; break;
            }
        }
    }
}

void Script::mouseDown(int button) { }
void Script::mouseClick(int button) { }

bool Script::setVar(std::string var, std::string value) { return false; }
bool Script::command(std::string cmd, std::string params) { return false; }