
#include "maze.h"
#include <stdlib.h>
#include <chrono>

int main()
{
    const int height = 8;
    const int width = 16;
    const unsigned seed =
        std::chrono::steady_clock::now().time_since_epoch().count();

    MazeGenerator mg = MazeGenerator{seed};

    int y = mg.random_int(height);
    int x = mg.random_int(width);
    Maze m = mg.randomized_Prims(height, width, y, x);

    m.print();

    return EXIT_FAILURE;
}




