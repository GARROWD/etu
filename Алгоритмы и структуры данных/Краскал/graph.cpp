#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "unique_array.cpp"

using namespace std;

class graph {
private:
    bool is_letter(char a) {
        return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || a == '-';
    }

    bool is_tabulation(char a) {
        return a == '\t' || a == '\n';
    }

public:
    dynamic_array<edge> edges;
    unique_array<int, string> vertexes;

    graph(string path) {
        parsing_from_file(path);
    }

    void parsing_from_file(string path) {
        ifstream file(path);
        string line;
        getline(file, line);
        line += "\n";

        int cur_column = 0;
        int i = 0;
        while (i < line.size()) {
            string tmp;
            while (!is_tabulation(line[i])) {
                if (is_letter(line[i])) {
                    tmp += line[i];
                }
                i++;
            }
            i++;

            vertexes.put(cur_column, tmp);
            cur_column++;

            if (cur_column > 49) {
                throw new exception;
            }
        }

        for (int cur_line = 0; cur_line < vertexes.get_size(); cur_line++) {
            cur_column = 0;
            getline(file, line);
            line += "\n";

            i = 0;
            while (i < line.size()) {
                string tmp;
                while (!is_tabulation(line[i])) {
                    if (is_letter(line[i])) {
                        tmp += line[i];
                    }
                    i++;
                }
                i++;

                int weight = stoi(tmp);


                if (cur_line != cur_column && weight != 0) {
                    edge tmp(cur_line, cur_column, abs(weight));
                    edges.add(tmp);
                }
                cur_column++;
            }

            if (cur_column < vertexes.get_size() || cur_column > vertexes.get_size()) {
                throw new exception;
                break;
            }
        }
    }
};
