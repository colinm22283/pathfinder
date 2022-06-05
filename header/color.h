#pragma once

#include <cstdint>

#define RGB(r,g,b) (color){r,g,b,255}
#define RGBA(r,g,b,a) (color){r,g,b,a}

struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};