#include "graph.hpp"
#include <fstream>


// Function to convert graph into dot format
// directed := 1(directed)/ 2(undirected)
void toDot(Graph &graph, bool directed, std::string outFile) {

    std::ofstream image(outFile);

    std::string graphType = directed ? "digraph" : "graph";
    std::string graphConnection = directed ? "->" : "--";

    image << graphType << "{\n";
    for (int i = 1; i <= graph.size(); ++i) {
        for (int j = 1; j <= graph.size(); ++j) {
            
            if (graph.isEdge(i, j)) {
                image << "\t" << i << " " << graphConnection << " " << j << ";\n";
            }

        }
    }
    image << "}";

    image.close();
}


int main() {

}