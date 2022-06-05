#include "SDL/SDL.h"
#include <iostream>

#include "script.h"
#include "event.h"
#include "console.h"
#include "consoleParser.h"
#include "engine.h"
#include "input.h"
#include "global.h"

SDL_Event Event::event;

void Event::init()
{
    while (!Engine::quit)
    {
        Event::update();
    }
}
void Event::update()
{
    if (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Script::exit();
            break;
        case SDL_KEYDOWN:
            ConsoleParser::keyDown(event.key.keysym);
            Console::keyDown(event.key.keysym);
            Script::keyDown(event.key.keysym);
            if (Global::printKeys) Console::print("Key: " + std::to_string(event.key.keysym.sym));
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&Input::mouseX, &Input::mouseY);
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                Input::mouseLeft = true;
                break;
            case SDL_BUTTON_MIDDLE:
                Input::mouseMiddle = true;
                break;
            case SDL_BUTTON_RIGHT:
                Input::mouseRight = true;
                break;
            break;
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            Script::mouseClick(event.button.button);

            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                Input::mouseLeft = false;
                break;
            case SDL_BUTTON_MIDDLE:
                Input::mouseMiddle = false;
                break;
            case SDL_BUTTON_RIGHT:
                Input::mouseRight = false;
                break;
            break;
            }
        }
        break;
        }
    }

    if (Input::mouseLeft) Script::mouseDown(SDL_BUTTON_LEFT);
    if (Input::mouseMiddle) Script::mouseDown(SDL_BUTTON_MIDDLE);
    if (Input::mouseRight) Script::mouseDown(SDL_BUTTON_RIGHT);
}