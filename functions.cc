
#include "maze.h"
#include <array>
#include <iostream>

bool Maze::is_connected(edge e)
{
    if (e >= 0 && e < connected.size())
        return connected[e];
    else
        return false;
}

bool Maze::connect(edge e)
{
    if (e >= 0 && e < connected.size()) {
        connected[e] = true;
        return false;
    }
    else
        return true;
}

Maze::node Maze::get_node(int row, int column)
{
    return (row >= 0 && row < height && column >= 0 && column < width) ?
        row * width + column : INVALID_NODE;
}

std::pair<Maze::node, Maze::node> Maze::get_nodes(edge e) {

    node n = INVALID_NODE;
    node adj = INVALID_NODE;

    if (e >= 0 && e < height * width + height) {
        n = (e % (width + 1)) ? e - 1 - e / (width + 1) : INVALID_NODE;
        adj = ((n+1) % width) ? n + 1 : INVALID_NODE;
    }
    else if (e >= height * width + height && e < connected.size()) {
        n = (e < height * width + height + width) ? INVALID_NODE : e - height * width - height - width;
        adj = (n < height * width - width) ? n + width : INVALID_NODE;
    }

    return std::pair<node, node>{n, adj};
}

int Maze::west_edge(int node)
{
    if (node >= 0 && node < height * width)
        return node + node / width;
    else
        return INVALID_EDGE;
}

int Maze::east_edge(node n)
{
    if (n >= 0 && n < height * width)
        return n + 1 + n / width;
    else
        return INVALID_EDGE;
}

int Maze::north_edge(node n)
{
    if (n >= 0 && n < height * width)
        return n + height * width + height;
    else
        return INVALID_EDGE;
}

int Maze::south_edge(node n)
{
    if (n >= 0 && n < height * width)
        return n + height * width + height + width;
    else
        return INVALID_EDGE;
}

std::array<Maze::edge, 4> Maze::get_edges(node n)
{
    std::array<edge, 4> edges;

    edges[(int) direction::NORTH] = north_edge(n);
    edges[(int) direction::EAST] = east_edge(n);
    edges[(int) direction::SOUTH] = south_edge(n);
    edges[(int) direction::WEST] = west_edge(n);

    return edges;
}

void Maze::print()
{
    for (int row = 0 ; row < height ; row++) {

        std::cout << '+';
        for (int col = 0 ; col < width ; col++) {

            node n = get_node(row, col);

            if (is_connected(north_edge(n)))
                std::cout << "   +";
            else
                std::cout <<  "---+";
        }
        std::cout << '\n';

        std::cout << '|';
        for (int col = 0 ; col < width ; col++) {

            node n = get_node(row, col);

            if (is_connected(east_edge(n)))
                std::cout << "    ";
            else
                std::cout <<  "   |";
        }
        std::cout << '\n';
    }

    std::cout << '+';
    for (int col = 0 ; col < width ; col++)
        std::cout << "---+";
    std::cout << std::endl;
}

int MazeGenerator::random_int(int n)
{
    std::uniform_int_distribution<int> uid(0, n-1);
    return uid(generator);
}

Maze MazeGenerator::randomized_Prims(int h, int w, int row, int column)
{
    Maze m = Maze(h, w);

    Maze::node start = m.get_node(row, column);
    if (start == Maze::INVALID_NODE)
        return m;

    std::vector<bool> visited = std::vector<bool>(h*w, false);

    visited[start] = true;
    std::array<Maze::edge, 4> edges = m.get_edges(start);
    std::vector<Maze::edge> wall_list = std::vector<Maze::edge>(
        edges.begin(), edges.end()
    );

    while (!wall_list.empty()) {

        int r = random_int(wall_list.size());

        Maze::edge e = wall_list[r];

        std::pair<Maze::node, Maze::node> np = m.get_nodes(e);

        Maze::node n = np.first;
        Maze::node adj = np.second;

        if (n != Maze::INVALID_NODE &&
            adj != Maze::INVALID_NODE &&
            visited[n] != visited[adj]) {

            Maze::node new_node = visited[n] ? adj : n;

            visited[new_node] = true;
            m.connect(e);

            for (Maze::node x : m.get_edges(new_node))
                if (x != e)
                    wall_list.push_back(x);
        }

        wall_list.erase(wall_list.begin() + r);
    }

    return m;
}
