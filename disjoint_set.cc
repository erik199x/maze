
#include <vector>

class DisjointSet {

    private:

        class Node {
            public:
                int parent;
                int rank;
        };

        std::vector<Node> nodes;

    public:

        DisjointSet(int n) : nodes(n) {
            for (int i = 0 ; i < n ; i++) {
                nodes[i] = {i, 0};
            }
        }

        int parent(int x) {
            return nodes[x].parent;
        }

        int rank(int x) {
            return nodes[x].rank;
        }

        int find(int x) {

            int root = x;
            while (parent(root) != root)
                root = parent(root);

            while (parent(x) != root) {
                int x_parent = parent(x);
                nodes[x].parent = root;
                x = x_parent;
            }

            return root;
        }

        void merge(int x, int y) {

            int x_root = find(x);
            int y_root = find(y);

            if (x_root == y_root)
                return;

            if (rank(x_root) < rank(y_root)) {
                int tmp = x_root;
                x_root = y_root;
                y_root = tmp;
            }

            nodes[y_root].parent = x_root;
            if (rank(x_root) == rank(y_root))
                nodes[x_root].rank++;
        }

};




