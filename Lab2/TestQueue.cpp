#include "priorityQueue.hpp"

typedef std::pair<std::string, int> element;

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "At least one pair needed\n";
        return 1;
    }
    
    std::vector<element> listOfElements;
    std::string tempString;
    int commaPos = 0;
    for (int i = 1; i < argc; ++i) {

        tempString = argv[i];
        commaPos = tempString.find(',');
        listOfElements.push_back(element(tempString.substr(1, commaPos - 1), stoi(tempString.substr(commaPos + 1, tempString.length() - 2))));
    }

    PRIORITYQUEUE_HXX::PQueue<std::string> queue(listOfElements);
    int beginingSize = queue.size();

    for (int i = 0; i < beginingSize; ++i) {
        std::cout << queue.Pop().first << " ";
    }

    std::cout << "\n";

    return 0;
}