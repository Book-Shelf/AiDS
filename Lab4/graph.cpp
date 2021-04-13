#include "graph.hpp"

int main() {

    Graph graph;
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 1);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 1);
    graph.addEdge(3, 2);
    graph.addEdge(4, 2);
    graph.addEdge(4, 3);
    graph.print();
    std::cout << "\n\n";

    Graph tree = Graph::BFS(graph, 3);
    tree.print();
    std::list<int> list = tree.get_Path(2);
    std::cout << list.empty() << "\n";
    std::cout << tree.get_hops(2) << "\n";
    // graph.print();
}