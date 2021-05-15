#include "graph.hpp"
#include <string>
#include <fstream>

typedef std::pair<int, int> path;

template<class T>
void print2DMatrix(T** matrix, size_t size) {

    for (size_t i = 0; i < size; i++) 
        for (size_t j = 0; j < size; j++)
            std::cout << matrix[i][j] << " \n"[j == (j - 1)];
}


int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Path to graph file needed [graph.csv] \"possible starting vertex, possible ending vertex\" \n";
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


    bool** TCmatrix = graph.getTransitiveClosure();
    
    std::cout << "Matrix: ";
    print2DMatrix<bool>(TCmatrix, graph.size());


    for (int i = 0; i < argc - 2; i++) {

        std::cout << "From " << paths[i].first << "To " << paths[i].second << ":  " << TCmatrix[paths[i].first - 1][paths[i].second - 1] <<  "\n";
    }
}