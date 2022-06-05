#include <iostream>
#include <string>
#include <vector>

#include "console.h"
#include "render.h"
#include "global.h"
#include "font.h"
#include "consoleParser.h"
#include "engine.h"

bool Console::visibible = false;
std::string Console::output = "\nConsole initialized";
std::string Console::input = "";
std::vector<std::string> Console::history;

long cursorTimer = 0;
int historyPos = -1;

void Console::print(std::string message)
{
    std::cout << "\n" << message;
    Console::output += "\n" + message;
}
void Console::update()
{
    if (Console::visibible)
    {
        Render::fillRect(0, 0, Global::windowWidth, 200, { 0, 0, 0, 255 });
        Render::fillRect(0, 200, Global::windowWidth, 3, { 255, 255, 255, 255 });

        Render::setColor({ 255, 255, 255, 255 });

        std::string temp = "";
        int line = 0;
        for (int i = (int)Console::output.length() - 1; i >= 0; i--)
        {
            if (Console::output[i] == '\n')
            {
                Render::drawText(10, 165 - line * 15, Font::consolas, temp, 0.7);
                temp = "";
                line++;
            }
            else temp = Console::output[i] + temp;
            if (line >= 12) break;
        }

        if (cursorTimer < 1000) Render::drawText(10, 180, Font::consolas, "> " + Console::input + "_", 0.7);
        else Render::drawText(10, 180, Font::consolas, "> " + Console::input, 0.7);

        if (cursorTimer >= 2000) cursorTimer -= 2000;
        cursorTimer += Engine::deltaTime;
    }
}
void Console::keyDown(SDL_Keysym keysym)
{
    if (keysym.sym == 96) Console::visibible = !Console::visibible;

    if (Console::visibible)
    {
        switch (keysym.sym)
        {
        case 13: //                                        Enter
            Console::print("> " + Console::input + "\n");
            ConsoleParser::parse(Console::input);
            Console::history.push_back(Console::input);
            Console::input = "";
            historyPos = -1;
            break;
        case 8: //                                         Backspace
            if (Console::input.length() == 0) break;
            Console::input = Console::input.substr(0, Console::input.length() - 1);
            break;
        case 1073741906: //                                Up Arrow
            if (historyPos < (int)Console::history.size() - 1)
            {
                historyPos++;
                Console::input = Console::history[Console::history.size() - historyPos - 1];
            }
            break;
        case 1073741905: //                                Down Arrow
            if (historyPos > 0)
            {
                historyPos--;
                Console::input = Console::history[Console::history.size() - historyPos - 1];
            }
            else if (historyPos == 0)
            {
                historyPos--;
                Console::input = "";
            }
            break;
        default: //                                        Other
            if (keysym.sym >= 32 && keysym.sym <= 122 && keysym.sym != 96)
            {
                Console::input += (char)keysym.sym;
            }
            break;
        }
    }
}