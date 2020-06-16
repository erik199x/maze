
#ifndef MAZE_H
#define MAZE_H

#include <array>
#include <random>
#include <utility>
#include <vector>

class Maze {

    private:
        std::vector<bool> connected;

    public:

        enum class direction : int {
            NORTH, EAST, SOUTH, WEST
        };

        typedef int edge;
        typedef int node;
        static const node INVALID_EDGE = -1;
        static const node INVALID_NODE = -1;

        const int height;
        const int width;

        Maze(int h, int w) :
            height(h),
            width(w),
            connected(2*h*w + h + w, false)
        {}

        bool is_connected(edge e);
        bool connect(edge e);

        node get_node(int row, int column);
        std::pair<node, node> get_nodes(edge e);

        edge west_edge(node n);
        edge east_edge(node n);
        edge north_edge(node n);
        edge south_edge(node n);
        std::array<edge, 4> get_edges(node n);

        void print();
};

class MazeGenerator
{
    private:
        std::default_random_engine generator;

    public:
        MazeGenerator(unsigned seed) : generator(seed) {}
        Maze randomized_Prims(int h, int w, int row, int column);
        int random_int(int n);
};

#endif




