#include <iostream>
#include <thread>

#include <SDL.h>

#include "global.h"
#include "engine.h"
#include "event.h"
#include "script.h"
#include "font.h"
#include "console.h"
#include "render.h"

void engineUpdateStart();
void quitThreadFunction();

long prevTime = 0;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

std::thread* updateThread = nullptr;
std::thread* eventThread = nullptr;
std::thread* timerThread = nullptr;
std::thread* quitThread = nullptr;

bool Engine::running = false;
long Engine::currentTime = 0;
long Engine::deltaTime = 0;

bool Engine::init()
{
    Engine::running = true;
    awaitingEngineQuit = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Could not initialize SDL, Error: " << SDL_GetError() << '\n';
        return false;
    }
    else
    {
        SDL_CreateWindowAndRenderer(
            Global::windowWidth, Global::windowHeight, 0,
            &window, &renderer
        );
        if (window == nullptr)
        {
            std::cout << "Window could not be created, Error: " << SDL_GetError() << '\n';
            return false;
        }
        else
        {
            if (!Font::init())
            {
                std::cout << "Failed to initialize fonts\n";
                return false;
            }
        }
    }
    return true;
}
void Engine::quit()
{
    Engine::running = false;

    quitThread = new std::thread(quitThreadFunction);
}
void quitThreadFunction()
{
    if (updateThread->joinable()) updateThread->join();
    if (eventThread->joinable()) eventThread->join();
    if (timerThread->joinable()) timerThread->join();

    delete updateThread;
    delete eventThread;
    delete timerThread;

    Font::cleanup();

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();

    awaitingEngineQuit = false;
}
void Engine::start()
{
    Script::start();

    eventThread = new std::thread(Event::init);
    timerThread = new std::thread(timerUpdate);
    updateThread = new std::thread(engineUpdateStart);
}

void engineUpdateStart()
{
    while (Engine::running)
    {
        if (Global::fpsLimit != 0)
        {
            long temp = (long)(1000.0 / Global::fpsLimit) - Engine::currentTime + prevTime;
            std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)(
                temp < 0 ? 0 : temp
            )));
        }
        Engine::deltaTime = Engine::currentTime - prevTime;
        prevTime = Engine::currentTime;
        Engine::update();
    }
}

unsigned int fpsTimer = 500;
float fpsRead = 0;
void Engine::update()
{
    Script::update();
    Console::update();

    if (Global::fpsOutput)
    {
        if (fpsTimer > 500)
        {
            fpsRead = 1000.0f / (float)Engine::deltaTime;
            fpsTimer -= 500;
        }

        Render::setColor({ 0, 0, 0, 255 });
        Render::fillRect(0, Global::windowHeight - 25, 150, 25, { 255, 255, 255, 255 });
        Render::drawText(10, Global::windowHeight - 20, // draw fps output
            Font::consolas,
            std::to_string(fpsRead) + " fps",
            0.7
        );

        fpsTimer += Engine::deltaTime;
    }

    Render::present();
}
void Engine::timerUpdate()
{
    while (Engine::running)
    {
        currentTime++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Engine::awaitQuit()
{
    while (Engine::running) std::this_thread::sleep_for(std::chrono::seconds(1));

    quitThread->join();
}