#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

int max(int a, int b) { 

    return a < b ? b : a; 
}

struct Node {

    int key;
    Node* next;
};

// Adjacency List representation
class Graph  {
    private:
    Node* verticies;
    int numOfVertices;

    public:

    Graph();
    Graph(int initMatrixSize);
    ~Graph();

    void addEdge(int u, int v, int weigth);          // u - start vertex, v - end vertex
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int size();
    void print();

};

Graph::Graph()
    : verticies(new Node[1])
    , numOfVertices(1) {}

Graph::Graph(int initVerticiesNum) {

    verticies = new Node[initVerticiesNum];
    numOfVertices = initVerticiesNum;
}

Graph::~Graph () {

}

void Graph::addEdge(int u, int v, int weigth) {

    // int maxValue = max(u, v);

    // if (numOfVertices < maxValue) {

    //     int** newMatrix = new int*[maxValue];

    //     for (int i = 0; i < maxValue; i++) {

    //         newMatrix[i] = new int[maxValue];
    //     }

    //     for (int i = 0; i < maxValue; i++) {
    //         for (int j = 0; j < maxValue; j++) {

    //             newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : 0;
    //         }

    //     }

    //     for (int i = 0; i < numOfVertices; i++) {

    //         delete [] matrix[i];
    //     }

    //     delete [] matrix;
        
    //     matrix = newMatrix; 
    //     numOfVertices = maxValue;
    // }

    // matrix[u - 1][v - 1] = weigth;
}


void Graph::addEdge(int u, int v) {

    // int maxValue = max(u, v);

    // if (numOfVertices < maxValue) {

    //     int** newMatrix = new int*[maxValue];

    //     for (int i = 0; i < maxValue; i++) {

    //         newMatrix[i] = new int[maxValue];
    //     }

    //     for (int i = 0; i < maxValue; i++) {
    //         for (int j = 0; j < maxValue; j++) {

    //             newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : 0;
    //         }

    //     }

    //     for (int i = 0; i < numOfVertices; i++) {

    //         delete [] matrix[i];
    //     }

    //     delete [] matrix;
        
    //     matrix = newMatrix; 
    //     numOfVertices = maxValue;
    // }

    // matrix[u - 1][v - 1] = 1;
}

void Graph::removeEdge(int u, int v) {

    // if (max(u, v) < numOfVertices) {

    //     matrix[u - 1][v - 1] = 0;
    // }
}

bool Graph::isEdge(int u, int v) {

    // return max(u, v) <= numOfVertices && matrix[u - 1][v - 1] != 0;
}

int Graph::size() {

    return numOfVertices;
}

void Graph::print()
{
//    for (int i = 0; i < numOfVertices; i++)
//    {
//       for (int j = 0; j < numOfVertices; j++)
//          std::cout << matrix[i][j] << " ";
//       std::cout << std::endl;
//    }
}

#endif