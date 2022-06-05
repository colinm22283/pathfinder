#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <iostream>

#include "global.h"
#include "render.h"
#include "engine.h"
#include "color.h"
#include "font.h"

color Render::c = { 255, 255, 255, 255 };

void Render::setColor(color c)
{
    Render::c = c;
}

void Render::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderClear(renderer);
}
void Render::clearScreen(color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderClear(renderer);
}
void Render::drawPixel(int x, int y)
{
    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderDrawPoint(renderer, x, y);
}
void Render::drawPixel(int x, int y, color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, x, y);
}
void Render::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Render::drawLine(int x1, int y1, int x2, int y2, color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Render::drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Render::drawRect(int x, int y, int w, int h, color c)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Render::fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, Render::c.r, Render::c.g, Render::c.b, Render::c.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Render::fillRect(int x, int y, int w, int h, color c)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Render::drawText(int x, int y, TTF_Font* font, std::string str)
{
    if (str.length() == 0) return;

    const char* temp = str.c_str();
    SDL_Surface* textSurface;
    SDL_Color col = { Render::c.r, Render::c.g, Render::c.b, Render::c.a };

    textSurface = TTF_RenderText_Solid(Font::consolas, temp, col);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w = textSurface->w;
    int h = textSurface->h;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, tex, NULL, &rect);
}
void Render::drawText(int x, int y, TTF_Font* font, std::string str, float scale)
{
    if (str.length() == 0) return;

    const char* temp = str.c_str();
    SDL_Surface* textSurface;
    SDL_Color col = { Render::c.r, Render::c.g, Render::c.b, Render::c.a };

    textSurface = TTF_RenderText_Solid(Font::consolas, temp, col);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    int w = textSurface->w * scale;
    int h = textSurface->h * scale;

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(tex);
}

void Render::present()
{
    SDL_RenderPresent(renderer);
}