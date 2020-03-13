
#ifndef MAZE_H
#define MAZE_H

class Node {
    int id;
    bool visited;
    Edge* edges;
};

class Edge {
    public:
        Node* a;
        Node* b;
        bool connected;
};

#endif




