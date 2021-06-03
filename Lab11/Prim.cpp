#include "graph.hpp"
#include <fstream>

int main(int argc, char* argv[]) {

     if (argc != 3) {
        std::cerr << "[graph.csv] [starting_vertex] \n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph(false);


    while(std::getline(data, VEW[0], ',')) {
            
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]), stoi(VEW[2]));
    }

    data.close();

    int mstWeight = graph.MST_Prim(atoi(argv[2]));

    std::cout << "Weight of MST: " << mstWeight << "\n";
}