
#include "maze.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>

int main()
{
    const int height = 8;
    const int width = 16;

    const unsigned seed =
        std::chrono::steady_clock::now().time_since_epoch().count();

    MazeGenerator mg = MazeGenerator{seed};

    int row = mg.random_int(height);
    int column = mg.random_int(width);

    Maze m1 = mg.Prim(height, width, row, column);
    Maze m2 = mg.Kruskal(height, width);

    std::cout << "\n Prim's algorithm:\n";
    m1.print();

    std::cout << "\n Kruskal's algorithm:\n";
    m2.print();

    return EXIT_FAILURE;
}
