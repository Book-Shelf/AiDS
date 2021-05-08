#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

int max(int a, int b) { 

    return a < b ? b : a; 
}

class Graph  {
    private:

    int** matrix;
    bool directed;
    int numOfVertices;

    void createBiggerMatrix(int size);

    public:

    Graph();
    Graph(bool directed);
    Graph(int initMatrixSize, bool directed);
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
    , directed(false)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = 0;
    }


Graph::Graph(bool directed)
    : matrix(new int*[1])
    , directed(directed)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = 0;
    }


Graph::Graph(int initMatrixSize, bool directed) {

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

    this->directed = directed;
}

Graph::~Graph () {

    for (int i = 0; i < numOfVertices; i++) {

        delete [] matrix[i];
    }

    delete [] matrix;
}


void Graph::createBiggerMatrix(int size) {

    int** newMatrix = new int*[size];

        for (int i = 0; i < size; i++) {

            newMatrix[i] = new int[size];
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : 0;
            }

        }

        for (int i = 0; i < numOfVertices; i++) {

            delete [] matrix[i];
        }

        delete [] matrix;
        
        matrix = newMatrix; 
        numOfVertices = size;
}


void Graph::addEdge(int u, int v, int weigth) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        createBiggerMatrix(maxValue);
    }

    if (!directed) {

        matrix[v - 1][u - 1] = weigth;
    }

    matrix[u - 1][v - 1] = weigth;
}


void Graph::addEdge(int u, int v) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        createBiggerMatrix(maxValue);
    }

    if (!directed) {

        matrix[v - 1][u - 1] = 1;
    }

    matrix[u - 1][v - 1] = 1;
}

void Graph::removeEdge(int u, int v) {

    if (max(u, v) < numOfVertices) {

        if (!directed) {

            matrix[v - 1][u - 1] = 0;
        }

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