#include "graph.hpp"
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc != 5) {

        std::cerr << "[path to data file] [start vertex] [end vertex 1] [end vertex 2]\n";
        return 1;
    }

    std::string filename = argv[1];
    int startV = atoi(argv[2]);
    int endV1 = atoi(argv[3]);
    int endV2 = atoi(argv[4]);
    std::ifstream data(filename);
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph(true);

    while(std::getline(data, VEW[0], ',')) {
            
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]), stoi(VEW[2]));
    }

    data.close();

    Destination dest = graph.Dijkstra(startV, endV1, endV2);

    std::cout << dest.distance1 << " " << dest.distance2 << "\n" << dest.time << " ms\n";
}