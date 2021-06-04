#include <iostream>
#include <fstream>
#include "graph.hpp"

int* readFromFile(std::string filename, Graph& transmutationGraph) {

    enum Entry {METAL_TYPE = 0, METAL_PRICE, KNOWN_PROCESSES, TRANSMUTATION_PRICES} entryType; 

    entryType = METAL_TYPE;
    std::ifstream data(filename);
    std::string entryData;

    int rowNumber = 0;
    int* metalsPrices = new int[0];
    int numberOfMetals = -100000;
    int numberOfKnownProcesses = -100000;
    int fromMetal = 0, toMetal = 0, price = 0;


    while(1) {

        rowNumber++;

        if (rowNumber == (3 + numberOfMetals + numberOfKnownProcesses)) break;

        switch (entryType) {

            case METAL_TYPE:

                std::getline(data, entryData, '\n');
                numberOfMetals = std::stoi(entryData);
                // std::cout << "NumberOfMetals: " << numberOfMetals << "\nTheir prices: {";
                metalsPrices = new int[numberOfMetals];

                entryType = METAL_PRICE;
                break;
            
            case METAL_PRICE:

                std::getline(data, entryData, '\n');
                metalsPrices[rowNumber - 2] = std::stoi(entryData);
                // std::cout << metalsPrices[rowNumber - 2] << ", ";
                if (rowNumber == (numberOfMetals + 1)) entryType = KNOWN_PROCESSES;
                break;

            case KNOWN_PROCESSES:

                std::getline(data, entryData, '\n');
                numberOfKnownProcesses = std::stoi(entryData);
                // std::cout << "\b\b}\nKnown number of transmutations: " << numberOfKnownProcesses << "\n";
                entryType = TRANSMUTATION_PRICES;
                break;

            case TRANSMUTATION_PRICES:

                std::getline(data, entryData, ' ');
                fromMetal = std::stoi(entryData);
                std::getline(data, entryData, ' ');
                toMetal = std::stoi(entryData);
                std::getline(data, entryData, '\n');
                price = std::stoi(entryData);
                // std::cout << "Transmutation from metal: (" << fromMetal << ") To metal: (" << toMetal << ") Costs: " << price << "\n";
                transmutationGraph.addEdge(fromMetal, toMetal, price);
                break;
        }
    }

    data.close();

    return metalsPrices;
}


int checkIfTransmutationCycleIsCheaper(int smallestPrice ,int transmutation, int goingBack, int cDuty) {

    int cyclePrice = transmutation + goingBack + cDuty;

    return smallestPrice > cyclePrice ? cyclePrice : smallestPrice;
}


int calculateMinimumCost(Graph& entryGraph, int* prices) {

    entryGraph.Dijkstra(1);
    Graph transposedGraph = entryGraph.transpose();
    transposedGraph.Dijkstra(1);
    int smallestPrice = prices[0] / 2;

    for (int i = 1; i < entryGraph.size(); i++) {

        smallestPrice = checkIfTransmutationCycleIsCheaper(smallestPrice, 
                        entryGraph.getVertex(i).dist, 
                        transposedGraph.getVertex(i).dist, 
                        prices[i] / 2);
    }

    return smallestPrice;
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "[entryData.csv]\n";
        return 1;
    }

    std::string filename = argv[1];
    Graph transmutationGraph(true); 
    int* metalsPrices = readFromFile(filename, transmutationGraph);
    int price = calculateMinimumCost(transmutationGraph, metalsPrices);

    std::cout << price << "\n";
}