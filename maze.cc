
#include "maze.h"
#include <stdlib.h>
#include <chrono>

int main()
{
    const int height = 8;
    const int width = 16;
    const unsigned seed =
        std::chrono::steady_clock::now().time_since_epoch().count();

    Maze m {height, width, seed};

    int y = m.random_int(height);
    int x = m.random_int(width);

    m.randomized_Prims(y, x);

    return EXIT_FAILURE;
}




