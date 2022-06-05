#include <string>
#include <fstream>
#include <iostream>

#include <color.h>
#include <render.h>

#include <img/bmp.h>
#include <img/img.h>

bmp::bmp()
{
    width = 0;
    height = 0;
    pixels = NULL;
}
bmp::bmp(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
    {
        width = 0;
        height = 0;
        pixels = NULL;
        return;
    }

    uint8_t header[2];
    file.read((char*)header, sizeof(uint8_t) * 2);
    if (header[0] != 66 || header[1] != 77)
    {
        width = 0;
        height = 0;
        pixels = NULL;
        return;
    }

    uint32_t size;
    file.read((char*)&size, sizeof(uint32_t));

    file.seekg(10);
    uint32_t pixOffset;
    file.read((char*)&pixOffset, sizeof(uint32_t));

    file.seekg(18);
    file.read((char*)&width, sizeof(uint32_t));

    file.seekg(22);
    file.read((char*)&height, sizeof(uint32_t));

    pixels = (color**)malloc(sizeof(color*) * width);
    for (int i = 0; i < (int)width; i++) pixels[i] = (color*)malloc(sizeof(color) * height);

    file.seekg(pixOffset);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < (int)width; x++)
        {
            file.read((char*)&pixels[x][y].b, sizeof(uint8_t));
            file.read((char*)&pixels[x][y].g, sizeof(uint8_t));
            file.read((char*)&pixels[x][y].r, sizeof(uint8_t));
        }
    }

    file.close();
}