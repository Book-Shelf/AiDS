#include "graph.hpp"

int main() {

    Graph graph;
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 5);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 6);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);
    graph.print();

    Graph g1 = graph.BFS(graph, 1);
}