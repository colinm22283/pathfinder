#include <render.h>
#include <color.h>

#include <grid.h>
#include <tile.h>

unsigned int gridOffsetX = 50;
unsigned int gridOffsetY = 50;
unsigned int tileSize = 10;

unsigned int startPosX = START_POS_X;
unsigned int startPosY = START_POS_Y;

unsigned int goalPosX = GOAL_POS_X;
unsigned int goalPosY = GOAL_POS_Y;

bool pathFound = false;
unsigned int pathLength = 0;

tile grid[GRID_WIDTH][GRID_HEIGHT];

void gridInit()
{
    for (unsigned int x = 0; x < GRID_WIDTH; x++) for (unsigned int y = 0; y < GRID_HEIGHT; y++)
        {
            if (x == 0 || x == GRID_WIDTH - 1 || y == 0 || y == GRID_HEIGHT - 1)
            { grid[x][y] = { tileType::WALL, false }; }
            else
            { grid[x][y] = { tileType::EMPTY, false }; }
        }
}

void gridPrint()
{
    for (unsigned int x = 0; x < GRID_WIDTH; x++) for (unsigned int y = 0; y < GRID_HEIGHT; y++)
    {
        color c;

        if (x == startPosX && y == startPosY) c = RGB(0, 255, 0);
        else if (x == goalPosX && y == goalPosY) c = RGB(255, 0, 0);
        else if (grid[x][y].type == tileType::PATH) c = RGB(0, 0, 255);
        else if (grid[x][y].scanned) c = RGB(255, 255, 0);
        else switch (grid[x][y].type)
        {
            case EMPTY:
                c = RGB(255, 255, 255);
                break;
            case WALL:
                c = RGB(50, 50, 50);
                break;
        }

        Render::fillRect(
            gridOffsetX + x * tileSize,
            gridOffsetY + y * tileSize,
            tileSize,
            tileSize,
            c
        );
        Render::drawRect(
            gridOffsetX + x * tileSize,
            gridOffsetY + y * tileSize,
            tileSize,
            tileSize,
            RGB(0, 0, 0)
        );
    }
}