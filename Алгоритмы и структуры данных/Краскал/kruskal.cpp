#include "graph.cpp"

class kruskal {
private:
    unique_array<int, int> parent;

    void merge_sort(dynamic_array<edge> &array) {
        for (int i = 0; i < array.get_size(); i++) {
            for (int j = 0; j < array.get_size() - 1; j++) {
                if (array.get(j).weight > array.get(j + 1).weight) {
                    edge tmp = array.get(j);
                    array.set(array.get(j + 1), j);
                    array.set(tmp, j + 1);
                }
            }
        }
    }

public:
    int find(int v) {
        if (parent.get(v) == v) {
            return v;
        }

        return find(parent.get(v));
    }

    void union_v(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        parent.put(root_a, root_b);
    }

    dynamic_array<edge> algorithm(dynamic_array<edge> edges, int n) {
        for (int i = 0; i < n; i++) {
            parent.put(i, i);
        }

        dynamic_array<edge> mst;

        merge_sort(edges);

        int index = 0;
        while (mst.get_size() != n - 1) {
            edge next_edge = edges.get(index);
            index++;

            int x = find(next_edge.from);
            int y = find(next_edge.to);

            if (x != y) {
                mst.add(next_edge);
                union_v(x, y);
            }
        }

        return mst;
    }
};