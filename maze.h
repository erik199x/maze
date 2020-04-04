
#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>

class Maze {
    private:
        std::vector<bool> connected;

    public:
        const int height;
        const int width;

        Maze(int h, int w) :
            height(h),
            width(w),
            connected(2*h*w - h - w, false)
        {}

        bool is_connected(int i);
        bool connect(int i);

        int node(int y, int x);

        int west_edge(int i);
        int east_edge(int i);
        int north_edge(int i);
        int south_edge(int i);
        std::vector<int> edges(int i);

        void print();
};

class MazeGenerator
{
    private:
        std::default_random_engine generator;

    public:
        MazeGenerator(unsigned seed) : generator(seed) {}
        Maze randomized_Prims(int h, int w, int y, int x);
        int random_int(int n);
};

#endif




