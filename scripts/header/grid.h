#pragma once

#include <tile.h>

#define GRID_WIDTH 50
#define GRID_HEIGHT 50

#define START_POS_X 5
#define START_POS_Y 5
#define GOAL_POS_X 15
#define GOAL_POS_Y 5

extern unsigned int gridOffsetX;
extern unsigned int gridOffsetY;
extern unsigned int tileSize;

extern unsigned int startPosX;
extern unsigned int startPosY;
extern unsigned int goalPosX;
extern unsigned int goalPosY;

extern bool pathFound;
extern unsigned int pathLength;

extern tile grid[GRID_WIDTH][GRID_HEIGHT];

void gridInit();
void gridPrint();