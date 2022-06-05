#include <cstdlib>
#include <math.h>
#include <iostream>

#include <color.h>
#include <render.h>

#include <img/img.h>

img::img()
{
    width = 0;
    height = 0;
}
img::img(int _width, int _height)
{
    width = _width;
    height = _height;

    pixels = (color**)malloc(sizeof(color*) * width);
    for (int x = 0; x < width; x++) pixels[x] = (color*)malloc(sizeof(color) * height);
}

img::~img()
{
    for (int x = 0; x < width; x++) free(pixels[x]);
    free(pixels);
}

void img::setPixel(int x, int y, color c)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    pixels[x][y] = c;
}
color img::getPixel(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height) return { 0, 0, 0, 0 };
    return pixels[x][y];
}

img img::resize(float sx, float sy)
{
    std::cout << (int)(width * sx) << "\n";

    img proto((int)(width * sx), (int)(height * sy));

    std::cout << "test\n";

    float nx = 0;
    float ny = 0;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::cout << nx << ", " << ny << "\n";
            proto.setPixel((int)nx, (int)ny, pixels[x][y]);

            ny += sy;
        }
        nx += sx;
    }

    std::cout << "test\n";

    return proto;
}

void img::draw() { draw(0, 0); }
void img::draw(int x, int y)
{
    for (int _x = 0; _x < width; _x++)
    {
        for (int _y = 0; _y < height; _y++)
        {
            Render::drawPixel(_x + x, _y + y, pixels[_x][_y]);
        }
    }
}