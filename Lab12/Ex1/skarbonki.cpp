#include "graph.hpp"
#include <fstream>

Graph readFromFile(std::string filename) {

    std::fstream data(filename);
    std::string entryData;
    int piggybank = 0;
    int rowNumber = 2;
    
    std::getline(data, entryData);
    Graph graph(std::stoi(entryData), true);


    while (std::getline(data, entryData)) {

        piggybank = std::stoi(entryData);
        graph.addEdge(piggybank, rowNumber - 1);
        rowNumber++;
    }

    data.close();

    return graph;
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "[entryData.csv]\n";
        return 1;
    }

    std::string filename = argv[1];
    Graph skarbonki = readFromFile(filename);

    skarbonki.print();
}