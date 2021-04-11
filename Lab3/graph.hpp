#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

int max(int a, int b) { 

    return a < b ? b : a; 
}

class Graph  {
    private:
    int** matrix;
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
    : matrix(new int*[1])
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = 0;
    }

Graph::Graph(int initMatrixSize) {

    matrix = new int*[initMatrixSize];
    numOfVertices = initMatrixSize;

    for (int i = 0; i < initMatrixSize; ++i) {

        matrix[i] = new int[initMatrixSize];
    }

    for (int i = 0; i < initMatrixSize; ++i) {
        for (int j = 0; j < initMatrixSize; ++j) {

            matrix[i][j] = 0;
        }
    }

}

Graph::~Graph () {

    for (int i = 0; i < numOfVertices; i++) {

        delete [] matrix[i];
    }

    delete [] matrix;
}

void Graph::addEdge(int u, int v, int weigth) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        int** newMatrix = new int*[maxValue];

        for (int i = 0; i < maxValue; i++) {

            newMatrix[i] = new int[maxValue];
        }

        for (int i = 0; i < maxValue; i++) {
            for (int j = 0; j < maxValue; j++) {

                newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : 0;
            }

        }

        for (int i = 0; i < numOfVertices; i++) {

            delete [] matrix[i];
        }

        delete [] matrix;
        
        matrix = newMatrix; 
        numOfVertices = maxValue;
    }

    matrix[u - 1][v - 1] = weigth;
}


void Graph::addEdge(int u, int v) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        int** newMatrix = new int*[maxValue];

        for (int i = 0; i < maxValue; i++) {

            newMatrix[i] = new int[maxValue];
        }

        for (int i = 0; i < maxValue; i++) {
            for (int j = 0; j < maxValue; j++) {

                newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : 0;
            }

        }

        for (int i = 0; i < numOfVertices; i++) {

            delete [] matrix[i];
        }

        delete [] matrix;
        
        matrix = newMatrix; 
        numOfVertices = maxValue;
    }

    matrix[u - 1][v - 1] = 1;
}

void Graph::removeEdge(int u, int v) {

    if (max(u, v) < numOfVertices) {

        matrix[u - 1][v - 1] = 0;
    }
}

bool Graph::isEdge(int u, int v) {

    return max(u, v) <= numOfVertices && matrix[u - 1][v - 1] != 0;
}

int Graph::size() {

    return numOfVertices;
}

void Graph::print()
{
   for (int i = 0; i < numOfVertices; i++)
   {
      for (int j = 0; j < numOfVertices; j++)
         std::cout << matrix[i][j] << " ";
      std::cout << std::endl;
   }
}

#endif