#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

#define INFINTY 10000000


int min(int a, int b) {

    return a < b ? a : b;
}


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

    void addEdge(int u, int v, int weight);          // u - start vertex, v - end vertex
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int size();
    void print();
    int** floydWarshall();

};


Graph::Graph()
    : matrix(new int*[1])
    , directed(false)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = INFINTY;
    }


Graph::Graph(bool directed)
    : matrix(new int*[1])
    , directed(directed)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = INFINTY;
    }


Graph::Graph(int initMatrixSize, bool directed) {

    matrix = new int*[initMatrixSize];
    numOfVertices = initMatrixSize;

    for (int i = 0; i < initMatrixSize; ++i) {

        matrix[i] = new int[initMatrixSize];
    }

    for (int i = 0; i < initMatrixSize; ++i) {
        for (int j = 0; j < initMatrixSize; ++j) {

            matrix[i][j] = INFINTY;
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

                newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : INFINTY;
            }

        }

        for (int i = 0; i < numOfVertices; i++) {

            delete [] matrix[i];
        }

        delete [] matrix;
        
        matrix = newMatrix; 
        numOfVertices = size;
}


void Graph::addEdge(int u, int v, int weight) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        createBiggerMatrix(maxValue);
    }

    if (!directed) {

        matrix[v - 1][u - 1] = weight;
    }

    matrix[u - 1][v - 1] = weight;
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

            matrix[v - 1][u - 1] = INFINTY;
        }
        
        matrix[u - 1][v - 1] = INFINTY;
    }
}

bool Graph::isEdge(int u, int v) {

    return max(u, v) <= numOfVertices && matrix[u - 1][v - 1] != INFINTY;
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


int** Graph::floydWarshall() {

    int** distance = new int*[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {

        distance[i] = new int[numOfVertices];
    }


    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; j++) {

            distance[i][j] = matrix[i][j];
        }

        distance[i][i] = 0; 
    }


    for (int k = 0; k < numOfVertices; k++) {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {

                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    return distance;
}

#endif