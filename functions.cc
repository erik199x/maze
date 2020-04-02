
#include "maze.h"
#include <iostream>
#include <vector>

void Maze::print_maze(std::vector<bool> &connected)
{
    for (int row = 0 ; row < height ; row++) {

        std::cout << '+';
        for (int col = 0 ; col < width ; col++) {

            int i = node(row, col);

            if (north_edge(i) != -1 && connected[north_edge(i)])
                std::cout << "   +";
            else
                std::cout <<  "---+";
        }
        std::cout << '\n';

        std::cout << '|';
        for (int col = 0 ; col < width ; col++) {

            int i = node(row, col);

            if (east_edge(i) != -1 && connected[east_edge(i)])
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

int Maze::west_edge(int i)
{
    if (i > 0 && i < height * width && i % width != 0)
        return i - 1 - i / width;

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

    return -1;
}

int Maze::south_edge(int i)
{
    return north_edge(i + width);
}

int Maze::random_int(int n)
{
    std::uniform_int_distribution<int> uid(0, n-1);
    return uid(generator);
}

int Maze::node(int y, int x)
{
    return (y >= 0 && y < height && x >= 0 && x < width) ? y * width + x : -1;
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

bool Maze::randomized_Prims(int y, int x)
{
    int h = height;
    int w = width;

    int start = node(y, x);
    if (start == -1)
        return true;

    std::vector<bool> visited = std::vector<bool>(height * width, false);
    std::vector<bool> connected = std::vector<bool>(2 * height * width - height - width, false);

    visited[start] = true;
    std::vector<int> wall_list = edges(start);

    while (!wall_list.empty()) {

        int r = random_int(wall_list.size());

        int edge = wall_list[r];

        int node = (edge < height * width - height) ? edge + edge / (width - 1) : edge + height - height * width;
        int adj = (edge < height * width - height) ? node + 1 : node + width;

        if (visited[node] != visited[adj]) {

            int new_node = visited[node] ? adj : node;

            visited[new_node] = true;
            connected[edge] = true;

            for (int x : edges(new_node))
                if (x != edge)
                    wall_list.push_back(x);
        }

        wall_list.erase(wall_list.begin() + r);
    }

    print_maze(connected);
    return false;
}




