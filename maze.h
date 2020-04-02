
#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>

class Maze {
    public:
        const int height;
        const int width;

        std::default_random_engine generator;

        Maze(int h, int w, unsigned seed) : height(h), width(w), generator(seed)
        {}

        void print_maze(std::vector<bool> &connected);

        int west_edge(int i);
        int east_edge(int i);
        int north_edge(int i);
        int south_edge(int i);

        int node(int y, int x);
        int random_int(int n);

        std::vector<int> edges(int i);
        bool randomized_Prims(int y, int x);
};

#endif




