#include "graph.hpp"
#include <string>
#include <fstream>

typedef std::pair<int, int> path;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "At least one pair of \"starting Vertex, ending Vertex\" needed\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph(true);

    while(std::getline(data, VEW[0], ',')) {
            
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]), stoi(VEW[2]));
    }

    std::string tempString;
    int commaPos = 0;

    path paths[argc - 2];


    for (int i = 2; i < argc; ++i) {

        tempString = argv[i];
        commaPos = tempString.find(',');

        paths[i - 2] = path(stoi(tempString.substr(0, commaPos)), stoi(tempString.substr(commaPos + 1, tempString.length() - 1)));
    }

    int** dist = graph.floydWarshall();


    for (int i = 0; i < argc - 2; i++) {

       std::cout << dist[paths[i].first - 1][paths[i].second - 1] <<  " ";
    }

    std::cout << '\n';
    std::cout << "Graph has negative cycle?\n";
    graph.hasNegativeCycle();
    std::cout << "Next matrix: \n\n";

    graph.printNextMatrix();

    std::cout << "\n";

    // for (int i = 0; i < argc - 2; i++) {

    //     graph.printShortestPath(paths[i].first, paths[i].second);
    // }


}