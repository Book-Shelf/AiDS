#include <iostream>
#include <fstream>
#include "graph.hpp"

void toDot(Graph &graph, bool directed) {

    std::ofstream image("graph.dot");

    std::string graphType = directed ? "digraph" : "graph";
    std::string graphConnection = directed ? "->" : "--";

    image << graphType << "{\n";
    for (int i = 1; i <= graph.size(); ++i) {
        for (int j = 1; j <= graph.size(); ++j) {
            
            if (graph.isEdge(i, j)) {
                image << "\t" << i << " " << graphConnection << " " << j << ";\n";
            }

        }
    }
    image << "}";

    image.close();
}

int main(int argc, char* argv[]) {

    if (argc != 2) {

        std::cerr << "Type path to file";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph;

    while(std::getline(data, VEW[0], ',')) {
        
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]), stoi(VEW[2]));
    }

    data.close();
    toDot(graph, 1);
}