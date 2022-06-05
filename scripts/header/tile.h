#pragma once

enum tileType { EMPTY, WALL, PATH };

struct tile
{
    tileType type;
    bool scanned;
};