#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "[entryData.csv]\n";
        return 1;
    }

    enum Entry {METAL_TYPE = 0, METAL_PRICE, KNOWN_PROCESSES, TRANSMUTATION_PRICES} entryType; 

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string entryData;
    static int rowNumber = 0;
    static int numberOfMetals = -100000;
    static int* metalsPrices;
    static int numberOfKnownProcesses = -100000;
    entryType = METAL_TYPE;
    static int fromMetal = 0, toMetal = 0, price = 0;


    while(1) {

        rowNumber++;

        if (rowNumber == (3 + numberOfMetals + numberOfKnownProcesses)) break;

        switch (entryType) {

            case METAL_TYPE:

                std::getline(data, entryData, '\n');
                numberOfMetals = std::stoi(entryData);
                std::cout << "NumberOfMetals: " << numberOfMetals << "\nTheir prices: {";
                metalsPrices = new int[numberOfMetals];

                entryType = METAL_PRICE;
                break;
            
            case METAL_PRICE:

                std::getline(data, entryData, '\n');
                metalsPrices[rowNumber - 2] = std::stoi(entryData);
                std::cout << metalsPrices[rowNumber - 2] << ", ";
                if (rowNumber == (numberOfMetals + 1)) entryType = KNOWN_PROCESSES;
                break;

            case KNOWN_PROCESSES:

                std::getline(data, entryData, '\n');
                numberOfKnownProcesses = std::stoi(entryData);
                std::cout << "\b\b}\nKnown number of transmutations: " << numberOfKnownProcesses << "\n";
                entryType = TRANSMUTATION_PRICES;
                break;

            case TRANSMUTATION_PRICES:

                std::getline(data, entryData, ' ');
                fromMetal = std::stoi(entryData);
                std::getline(data, entryData, ' ');
                toMetal = std::stoi(entryData);
                std::getline(data, entryData, '\n');
                price = std::stoi(entryData);
                std::cout << "Transmutation from metal: (" << fromMetal << ") To metal: (" << toMetal << ") Costs: " << price << "\n";
                break;

        }
    }

    data.close();
}