#pragma once

#include "SDL/SDL_ttf.h"
#include <string>

#include "global.h"
#include "color.h"

namespace Render
{
    extern color c;

    void setColor(color c); //                                         Set the color of the renderer
    void present(); //                                                 Present new pixels to the screen

    void clearScreen(); //                                             Clear the screen
    void clearScreen(color c);
    void drawPixel(int x, int y); //                                   Draw a pixel on screen
    void drawPixel(int x, int y, color c);
    void drawLine(int x1, int y1, int x2, int y2); //                  Draw a line on screen
    void drawLine(int x1, int y1, int x2, int y2, color c);
    void drawRect(int x, int y, int w, int h); //                      Draw a rectangle on screen
    void drawRect(int x, int y, int w, int h, color c);
    void fillRect(int x, int y, int w, int h); //                      Draw a filled rectangle on screen
    void fillRect(int x, int y, int w, int h, color c);
    void drawText(int x, int y, TTF_Font* font, std::string str); //    Draw a text string
    void drawText(int x, int y, TTF_Font* font, std::string str, float scale);
}