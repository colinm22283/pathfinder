#pragma once

#include <color.h>

class img
{
public:
    img();
    img(int _width, int _height);
    
    ~img();

    int width;
    int height;

    void setPixel(int x, int y, color c);
    color getPixel(int x, int y);

    img resize(float sx, float sy);

    void draw();
    void draw(int x, int y);
protected:
    color** pixels;
};