#include "graph.hpp"

int main() {

    Graph graph;
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(3, 2);
    graph.addEdge(2, 1);
    graph.addEdge(2, 1);
    graph.addEdge(2, 3);
    graph.print();

    graph.removeEdge(2, 1);
    graph.removeEdge(2, 1);
    graph.removeEdge(1, 2);
    graph.print();
}