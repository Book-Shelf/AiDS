#include <iostream>
#include <fstream>
#include "graph.hpp"

// Function to convert graph into dot format
// directed := 1(directed)/ 2(undirected)
void toDot(Graph &graph, bool directed, std::string outFile) {

    std::ofstream image(outFile);

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

    if (argc < 3) {

        std::cerr << "[path to file] [start vertex] [end vertex01] [end vertex02] ...\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph;

    while(std::getline(data, VEW[0], ',')) {
        
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]));
    }

    data.close();
    toDot(graph, 1, "graph.dot");
    Graph tree = Graph::BFS(graph, atoi(argv[2]));
    toDot(tree, 1, "tree.dot");

    if (argc > 3) {
        
        for (int i = 3; i < argc; ++i) {

            std::cout << tree.get_hops(atoi(argv[i])) << " ";
        }
        
        std::cout << '\n';
    }
}