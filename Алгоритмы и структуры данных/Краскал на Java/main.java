package org.example;

import java.io.IOException;
import java.util.*;

public class main {
    public static void main(String[] args) {
        try {
            Graph test = new Graph("tst1.txt");

            DynamicArray<Edge> edges = Kruskal.algorithm(test.edges, test.vertexes.size());

            List<String> output = new ArrayList<>();

            int totalWeight = 0;
            for(Edge e : edges) {
                output.add(test.vertexes.get(Math.min(e.from, e.to)) + " " + test.vertexes.get(Math.max(e.from, e.to)));
                totalWeight += e.weight;
            }

            output = output.stream().sorted().toList(); // Сортировка в алфавитном порядке, ее мы не реализовывали

            for(String s : output) {
                System.out.println(s);
            }

            System.out.println(totalWeight );

        } catch(IOException e) {
            System.out.println("File not found");
        } catch(IndexOutOfBoundsException e) {
            System.out.println("Incorrect input");
        }
    }
}