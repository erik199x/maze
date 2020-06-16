
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

    int row = mg.random_int(height);
    int column = mg.random_int(width);
    Maze m = mg.randomized_Prims(height, width, row, column);

    m.print();

    return EXIT_FAILURE;
}




