#include <vector>

#include <console.h>

#include <dijkstra.h>
#include <grid.h>

struct point { unsigned int x; unsigned int y; point* from; };

bool** scanned = nullptr;
std::vector<point*> next;

std::vector<point> path;
std::vector<point*> all;

void dijkstraInit()
{
    next.push_back(new point { startPosX, startPosY, nullptr });

    scanned = new bool*[GRID_WIDTH];
    for (unsigned int i = 0; i < GRID_WIDTH; i++)
    {
        scanned[i] = new bool[GRID_HEIGHT];
        for (unsigned int j = 0; j < GRID_HEIGHT; j++) scanned[i][j] = false;
    }
}
bool dijkstraUpdate()
{
    if (next[0]->x == goalPosX && next[0]->y == goalPosY)
    {
        Console::print("Found Path");

        point* current = next[0];
        while (true)
        {
            grid[current->x][current->y].type = tileType::PATH;
            current = current->from;

            if (current == nullptr) break;

            pathLength++;
        }

        for (unsigned int i = 0; i < (unsigned int)all.size(); i++) delete all[i];

        for (unsigned int i = 0; i < GRID_WIDTH; i++) delete scanned[i];
        delete scanned;

        pathFound = true;

        return true;
    }

    all.push_back(next[0]);

    if (!scanned[next[0]->x][next[0]->y] && grid[next[0]->x][next[0]->y].type != tileType::WALL)
    {
        scanned[next[0]->x][next[0]->y] = true;
        grid[next[0]->x][next[0]->y].scanned = true;

        next.push_back(new point { next[0]->x - 1, next[0]->y, next[0] });
        next.push_back(new point { next[0]->x + 1, next[0]->y, next[0] });
        next.push_back(new point { next[0]->x, next[0]->y - 1, next[0] });
        next.push_back(new point { next[0]->x, next[0]->y + 1, next[0] });
    }

    next.erase(next.begin());

    return false;
}