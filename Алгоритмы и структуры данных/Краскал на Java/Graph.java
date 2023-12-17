package org.example;

import java.io.*;
import java.util.regex.*;

public class Graph
{
    public DynamicArray<Edge> edges = new DynamicArray<>();
    public UniqueArray<Integer, String> vertexes = new UniqueArray<>();

    public Graph(String path) throws IOException
    {
        parsingFromFile(path);
    }

    public void parsingFromFile(String path) throws IOException
    {
        BufferedReader graph = new BufferedReader(new FileReader(path));
        String line = graph.readLine() + '\n';

        Pattern pattern = Pattern.compile("[a-zA-Z0-9-]{1,5}[\t\n]");
        Matcher matcher = pattern.matcher(line);

        int curColumn = 0;
        while (matcher.find())
        {
            vertexes.put(curColumn, line.substring(matcher.start(), matcher.end() - 1));
            curColumn++;

            if (curColumn > 49)
            {
                throw new IndexOutOfBoundsException();
            }
        }

        for (int curLine = 0; curLine < vertexes.size(); curLine++)
        {
            curColumn = 0;
            line = graph.readLine() + "\n";

            matcher = pattern.matcher(line);

            while (matcher.find())
            {
                int weight = Integer.parseInt(line.substring(matcher.start(), matcher.end() - 1));
                if (curLine != curColumn && weight != 0)
                {
                    edges.add(new Edge(curLine, curColumn, Math.abs(weight)));
                }
                curColumn++;
            }

            if (curColumn < vertexes.size() || curColumn > vertexes.size())
            {
                throw new IndexOutOfBoundsException();
            }
        }
    }
}
