
#include "maze.h"
#include <iostream>
#include <vector>

int MazeGenerator::random_int(int n)
{
    std::uniform_int_distribution<int> uid(0, n-1);
    return uid(generator);
}

Maze MazeGenerator::randomized_Prims(int h, int w, int y, int x)
{
    Maze m = Maze(h, w);

    int start = m.node(y, x);
    if (start == -1)
        return m;

    std::vector<bool> visited = std::vector<bool>(h*w, false);

    visited[start] = true;
    std::vector<int> wall_list = m.edges(start);

    while (!wall_list.empty()) {

        int r = random_int(wall_list.size());

        int edge = wall_list[r];

        int node = (edge < h*w - h) ? edge + edge / (w - 1) : edge + h - h*w;
        int adj = (edge < h*w - h) ? node + 1 : node + w;

        if (visited[node] != visited[adj]) {

            int new_node = visited[node] ? adj : node;

            visited[new_node] = true;
            m.connect(edge);

            for (int x : m.edges(new_node))
                if (x != edge)
                    wall_list.push_back(x);
        }

        wall_list.erase(wall_list.begin() + r);
    }

    return m;
}

bool Maze::is_connected(int i)
{
    if (i >= 0 && i < 2 * height * width - height - width)
        return connected[i];
    else
        return false;
}

bool Maze::connect(int i)
{
    if (i >= 0 && i < 2 * height * width - height - width)
        return (connected[i] = true);
    else
        return false;
}

int Maze::node(int y, int x)
{
    return (y >= 0 && y < height && x >= 0 && x < width) ? y * width + x : -1;
}

int Maze::west_edge(int i)
{
    if (i > 0 && i < height * width && i % width != 0)
        return i - 1 - i / width;
    else
        return -1;
}

int Maze::east_edge(int i)
{
    return west_edge(i + 1);
}

int Maze::north_edge(int i)
{
    if (i >= width && i < height * width)
        return i + height * width - height - width;
    else
        return -1;
}

int Maze::south_edge(int i)
{
    return north_edge(i + width);
}

std::vector<int> Maze::edges(int i)
{
    std::vector<int> v;

    int edge;
    edge = west_edge(i);
    if (edge != -1)
        v.push_back(edge);

    edge = east_edge(i);
    if (edge != -1)
        v.push_back(edge);

    edge = north_edge(i);
    if (edge != -1)
        v.push_back(edge);

    edge = south_edge(i);
    if (edge != -1)
        v.push_back(edge);

    return v;
}

void Maze::print()
{
    for (int row = 0 ; row < height ; row++) {

        std::cout << '+';
        for (int col = 0 ; col < width ; col++) {

            int i = node(row, col);

            if (is_connected(north_edge(i)))
                std::cout << "   +";
            else
                std::cout <<  "---+";
        }
        std::cout << '\n';

        std::cout << '|';
        for (int col = 0 ; col < width ; col++) {

            int i = node(row, col);

            if (is_connected(east_edge(i)))
                std::cout << "    ";
            else
                std::cout <<  "   |";
        }
        std::cout << '\n';
    }

    std::cout << '+';
    for (int i = 0 ; i < width ; i++)
        std::cout << "---+";
    std::cout << std::endl;
}




