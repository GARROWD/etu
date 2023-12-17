#include <iostream>
#include "kruskal.cpp"

using namespace std;

void alph_sort(dynamic_array<string> &array) {
    for (int i = 0; i < array.get_size(); i++) {
        for (int j = 0; j < array.get_size() - 1; j++) {
            if (array.get(j)[0] > array.get(j + 1)[0]) {
                string tmp = array.get(j);
                array.set(array.get(j + 1), j);
                array.set(tmp, j + 1);
            }
        }
    }
}

int main() {
    try {
        graph graph("C:\\Users\\garro\\CLionProjects\\etu\\tst1.txt"); // Путь

        kruskal func;
        dynamic_array<edge> mst = func.algorithm(graph.edges, graph.vertexes.get_size());

        dynamic_array<string> out;
        int total_weight = 0;

        for (int i = 0; i < mst.get_size(); ++i) {
            edge tmp = mst.get(i);
            out.add(graph.vertexes.get(min(tmp.from, tmp.to)) + " " + graph.vertexes.get(max(tmp.from, tmp.to)) + "\n");
            total_weight += tmp.weight;
        }

        alph_sort(out);

        for (int i = 0; i < out.get_size(); ++i) {
            cout << out.get(i);
        }

        cout << total_weight << "\n";
    }
    catch (exception) {
        cout << " [i] Error catch";
    }

    system("pause");
}
