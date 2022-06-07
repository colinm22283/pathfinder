#include <vector>

#include <console.h>

#include <dijkstra.h>
#include <grid.h>

struct point { unsigned int x; unsigned int y; point* from; };

std::vector<point> scanned;
std::vector<point*> next;

std::vector<point> path;
std::vector<point*> all;

bool found = false;

void dijkstraInit()
{
    next.push_back(new point { startPosX, startPosY, nullptr });
}
bool dijkstraUpdate()
{
    if (found) return true;

    if (next[0]->x == goalPosX && next[0]->y == goalPosY)
    {
        found = true;

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

        pathFound = true;
    }

    all.push_back(next[0]);

    bool isScanned = false;
    for (unsigned int i = 0; i < (unsigned int)scanned.size(); i++)
    {
        if (next[0]->x == scanned[i].x && next[0]->y == scanned[i].y)
        {
            isScanned = true;
            break;
        }
    }

    if (!isScanned && grid[next[0]->x][next[0]->y].type != tileType::WALL)
    {
        scanned.push_back({ next[0]->x, next[0]->y });
        grid[next[0]->x][next[0]->y].scanned = true;

        next.push_back(new point { next[0]->x - 1, next[0]->y, next[0] });
        next.push_back(new point { next[0]->x + 1, next[0]->y, next[0] });
        next.push_back(new point { next[0]->x, next[0]->y - 1, next[0] });
        next.push_back(new point { next[0]->x, next[0]->y + 1, next[0] });
    }

    next.erase(next.begin());

    return false;
}