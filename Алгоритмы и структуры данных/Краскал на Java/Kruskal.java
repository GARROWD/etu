package org.example;

import org.example.UniqueArray;

class Kruskal
{
    UniqueArray<Integer, Integer> parent = new UniqueArray<>();

    Kruskal(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.put(i, i);
        }
    }
    private int find(int v)
    {
        if (parent.get(v) == v)
        {
            return v;
        }

        return find(parent.get(v));
    }

    private void union(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        parent.put(root_a, root_b);
    }

    public static DynamicArray<Edge> algorithm(DynamicArray<Edge> edges, int n)
    {
        DynamicArray<Edge> mst = new DynamicArray<>();
        Kruskal set = new Kruskal(n);

        TimSortForEdges sort = new TimSortForEdges();

        edges = sort.algorithm(edges);

        int index = 0;
        while (mst.size() != n - 1)
        {
            Edge next_edge = edges.get(index);
            index++;

            int x = set.find(next_edge.from);
            int y = set.find(next_edge.to);

            if (x != y)
            {
                mst.add(next_edge);
                set.union(x, y);
            }
        }

        return mst;
    }
}
