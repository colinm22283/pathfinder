#include <string>
#include <map>
#include <iostream>
#include <SDL.h>

#include "consoleParser.h"
#include "script.h"
#include "console.h"
#include "engine.h"
#include "global.h"
#include <misc.h>

#include <help.h>

#define MAX_BIND 1024

std::string bindMap[MAX_BIND];

bool ConsoleParser::parse(std::string code)
{
    try
    {
        std::string first = code.substr(0, code.find(' '));
        std::string nstr = code.substr(code.find(' ') + 1);

        if (first == "exit")
        {
            Script::exit();
        }
        else if (first == "help")
        {
            std::string second = nstr.substr(0, nstr.find(' '));

            if (nstr != "help" && !Misc::isInt(second)) { Console::print("Invalid page."); return false; }

            int page;
            if (nstr == "help") page = 0;
            else page = (stoi(second) - 1) * 10;
            if (page < 0) { Console::print("Invalid page."); return false; }

            int first;

            int i = 0;
            while (HELP_TEXT[i] != EOF)
            {
                if (HELP_TEXT[i] == '\n')
                {
                    if (page <= 0)
                    {
                        first = i;

                        int j = i;
                        int lines = 0;
                        while (HELP_TEXT[j] != EOF)
                        {
                            if (HELP_TEXT[j] == '\n') lines++;
                            if (lines >= 10)
                            {
                                Console::print(std::string(HELP_TEXT).substr(first, j));
                                return true;
                            }
                            j++;
                        }
                        break;
                    }
                    page--;
                }
                i++;
            }
            
            Console::print("Invalid page.");
            return false;
        }
        else if (first == "set")
        {
            std::string second = nstr.substr(0, nstr.find(' '));
            std::string nstr2 = nstr.substr(nstr.find(' ') + 1);
            std::string third = nstr2.substr(0, nstr2.find(' '));
            if (second == "resx")
            {
                int w = std::stoi(third);
                int h;
                SDL_GetWindowSize(window, NULL, &h);
                SDL_SetWindowSize(window, w, h);
                Global::windowWidth = w;
            }
            else if (second == "resy")
            {
                int w;
                int h = std::stoi(third);
                SDL_GetWindowSize(window, &w, NULL);
                SDL_SetWindowSize(window, w, h);
                Global::windowHeight = h;
            }
            else if (second == "fpslimit") Global::fpsLimit = std::stoi(third);
            else if (second == "fpsoutput") Global::fpsOutput = third == "true";
            else if (second == "printkeys") Global::printKeys = third == "true";
            else if (!Script::setVar(second, nstr2)) Console::print("Variable \"" + second + "\" does not exist.");
        }
        else if (first == "bind")
        {
            std::string second = nstr.substr(0, nstr.find(' '));
            std::string third = nstr.substr(nstr.find(' ') + 1);

            if (second.length() == 1) bindMap[(int)second[0]] = third;
            else bindMap[stoi(second)] = third;
        }
        else if (first == "unbind")
        {
            std::string second = nstr.substr(0, nstr.find(' '));

            if (second.length() == 1) bindMap[(int)second[0]] = "";
            else bindMap[stoi(second)] = "";
        }
        else if (first == "time")
        {
            Console::print(Misc::timeString(Engine::currentTime));
        }
        else if (!Script::command(first, nstr))
        {
            Console::print("Command not found \"" + first + "\"");
            return false;
        }
        return true;
    }
    catch (const std::invalid_argument&) { Console::print("Invalid arguments"); return false; }
}

void ConsoleParser::keyDown(SDL_Keysym keysym)
{
    if ((int)keysym.sym >= MAX_BIND) return;
    std::string temp = bindMap[(int)keysym.sym];
    if (temp != "") ConsoleParser::parse(temp);
}