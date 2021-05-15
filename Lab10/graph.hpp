#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <queue>

#define INFINITY 10000000


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
    int** distance;     // 2D matrix represent distance between 2 nodes
    int** next;         // 2D matrix that is used to recreate shortest paths 

    void createBiggerMatrix(int size);
    void initMatrixes();
    void printPathText(int startV, int endV);

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
    void printShortestPath(int startV, int endV);
    void printNextMatrix();
    void hasNegativeCycle();
    bool** getTransitiveClosure();
};


Graph::Graph()
    : matrix(new int*[1])
    , directed(false)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = INFINITY;
    }


Graph::Graph(bool directed)
    : matrix(new int*[1])
    , directed(directed)
    , numOfVertices(1) {

        matrix[0] = new int[1];
        matrix[0][0] = INFINITY;
    }


Graph::Graph(int initMatrixSize, bool directed) {

    matrix = new int*[initMatrixSize];
    numOfVertices = initMatrixSize;

    for (int i = 0; i < initMatrixSize; ++i) {

        matrix[i] = new int[initMatrixSize];
    }

    for (int i = 0; i < initMatrixSize; ++i) {
        for (int j = 0; j < initMatrixSize; ++j) {

            matrix[i][j] = INFINITY;
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

                newMatrix[i][j] = numOfVertices > i && numOfVertices > j ? matrix[i][j] : INFINITY;
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

            matrix[v - 1][u - 1] = INFINITY;
        }
        
        matrix[u - 1][v - 1] = INFINITY;
    }
}

bool Graph::isEdge(int u, int v) {

    return max(u, v) <= numOfVertices && matrix[u - 1][v - 1] != INFINITY;
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


void Graph::initMatrixes() {

    distance = new int*[numOfVertices];
    next = new int*[numOfVertices];

    for (int i = 0; i < numOfVertices; ++i) {

        distance[i] = new int[numOfVertices];
        next[i] = new int[numOfVertices];
    }


    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; j++) {

            distance[i][j] = matrix[i][j];
            next[i][j] = matrix[i][j] != INFINITY ? j : -8;
        }

        distance[i][i] = 0; 
    }

}


int** Graph::floydWarshall() {

    initMatrixes();

    for (int k = 0; k < numOfVertices; k++) {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {

                if (distance[i][j] > distance[i][k] + distance[k][j]) {

                    distance[i][j] = distance[i][k] + distance[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    return distance;
}


void Graph::printPathText(int startV, int endV) {

    std::cout << "Path ( " << startV << "-> " << endV << " ) " << "is affected by negative cycle.\n";
}


void Graph::printShortestPath(int startV, int endV)  {

    std::queue<int> path;

    if(distance[startV - 1][endV - 1] == INFINITY) {

        std::cout << "There is no path between vertex " << startV << " and vertex " << endV << "\n";
        return;
    }

    int at = startV - 1;
    

    for(; at != (endV - 1); at = next[at][endV - 1]) {

        if (at == -1) {

            printPathText(startV, endV);
            return;
        }
        
        path.push(at);
    }

    if (next[at][endV - 1] == -1) {

        printPathText(startV, endV);
        return;
    }

    path.push(endV - 1);

    std::cout << "Path ( " << startV << "-> " << endV << " ):\n";

    while (!path.empty()) {

        std::cout << (path.front() + 1) << "->";
        path.pop();
    }

    std::cout << "\b\b  \n";

}


void Graph::printNextMatrix() {

    for (int i = 0; i < numOfVertices; ++i) {
        for (int j = 0; j < numOfVertices; ++j) {
            
            std::cout << next[i][j] << " ";
        }

        std::cout << "\n";
    }
}


void Graph::hasNegativeCycle() {

    bool hasNegativeCycle = 0;

    for (int k = 0; k < numOfVertices; k++) {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {

                if (distance[i][j] > (distance[i][k] + distance[k][j])) {

                    next[i][j] = -1;
                    hasNegativeCycle = 1;
                }
            }
        }
    }



    std::cout << (hasNegativeCycle ? "Yes" : "No") << "\n\n";
}


bool** Graph::getTransitiveClosure() {

    bool** TCmatrix = new bool*[numOfVertices];
    
    for (int i = 0; i < numOfVertices; i++) {

        TCmatrix[i] = new bool[numOfVertices];
    }

    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {

            TCmatrix[i][j] = ((matrix[i][j] != INFINITY) || (i == j)) ? 1 : 0;
        }
    }

    for (int k = 0; k < numOfVertices; k++) {
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {

                if (TCmatrix[i][j] != (TCmatrix[i][k] && TCmatrix[k][j])) {

                    TCmatrix[i][j] = 1;
                }
            }
        }
    }

    return TCmatrix;
}

#endif