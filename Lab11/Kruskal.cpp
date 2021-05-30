#include "graph.hpp"
#include <fstream>

void writeMSTToFile(std::string filename, Graph& graph) {

    std::ofstream output(filename);

    for (int i = 0; i < graph.size(); i++) {

        Node* temp = graph.getVertex(i).next;

        while (temp != nullptr) {

            if (temp->key >= (i + 1)) {

                output << i + 1 << ", " << temp->key << ", " << temp->weight * 1.0 << "\n";
            }

            temp = temp->next;
        }
    }

    output.close();
}


int main(int argc, char* argv[]) {

     if (argc != 3) {
        std::cerr << "Path to files needed [graph.csv] [output.csv] \n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream data(filename);
    filename = argv[2];
    std::string VEW[3]; // start Vertes, end Vertex, weigth
    Graph graph(false);


    while(std::getline(data, VEW[0], ',')) {
            
        std::getline(data, VEW[1], ',');
        std::getline(data, VEW[2]);
        graph.addEdge(stoi(VEW[0]), stoi(VEW[1]), stoi(VEW[2]));
    }

    data.close();

    Graph mstGraph = graph.MST_Kruskal();

    writeMSTToFile(filename, mstGraph);
}