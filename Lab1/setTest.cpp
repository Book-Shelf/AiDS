#include "Set.hpp"
#include <string>
#include <cstdlib>

int main(int argc, char** argv) {

    // test whether user typed enough arguments
    if (argc < 2) {

        std::cerr << "Not enough arguments\n";
        return 1;
    }

    std::string type = argv[1];

    if (type.compare("integer") == 0) {

        Set<int> set;

        for (int i = 2; i < argc; i++) {

            set.Insert(std::atoi(argv[i]));
        }

        set.print(); 
    } else if (type.compare("string") == 0) {

        Set<std::string> set;

        for (int i = 2; i < argc; i++) {

            set.Insert(argv[i]);
        }

        set.print(); 
    } else {

        std::cerr << "Wrong type.\nOnly \"string\" and \"integer\" available\n";
        return 1;
    }
    
    
}