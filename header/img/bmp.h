#pragma once

#include <string>

#include <color.h>

#include <img/img.h>

class bmp: public img
{
public:
    bmp();
    bmp(img);
    bmp(const char* path);
};