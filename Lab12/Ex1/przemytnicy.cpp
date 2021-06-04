#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "[dane.csv]\n";
        return 1;
    }

    enum Entry {METAL_TYPE = 0, METAL_PRICE, KNOWN_PROCESSES, TRANSMUTATION_PRICES} entryType; 

    std::string filename = argv[1];
    std::ifstream data(filename);
    std::string dane;
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

                std::getline(data, dane, '\n');
                numberOfMetals = std::stoi(dane);
                std::cout << "NumberOfMetals: " << numberOfMetals << "\nTheir prices: {";
                metalsPrices = new int[numberOfMetals];

                entryType = METAL_PRICE;
                break;
            
            case METAL_PRICE:

                std::getline(data, dane, '\n');
                metalsPrices[rowNumber - 2] = std::stoi(dane);
                std::cout << metalsPrices[rowNumber - 2] << ", ";
                if (rowNumber == (numberOfMetals + 1)) entryType = KNOWN_PROCESSES;
                break;

            case KNOWN_PROCESSES:

                std::getline(data, dane, '\n');
                numberOfKnownProcesses = std::stoi(dane);
                std::cout << "\b\b}\nKnown number of transmutations: " << numberOfKnownProcesses << "\n";
                entryType = TRANSMUTATION_PRICES;
                break;

            case TRANSMUTATION_PRICES:

                std::getline(data, dane, ' ');
                fromMetal = std::stoi(dane);
                std::getline(data, dane, ' ');
                toMetal = std::stoi(dane);
                std::getline(data, dane, '\n');
                price = std::stoi(dane);
                std::cout << "Transmutation from metal: (" << fromMetal << ") To metal: (" << toMetal << ") Costs: " << price << "\n";
                break;

        }
    }

    data.close();
}