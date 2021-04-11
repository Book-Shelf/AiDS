#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

int max(int a, int b) { 

    return a < b ? b : a; 
}

struct Node {

    int key;
    Node* next;
    int weigth;

    Node()
        : key(0)
        , next(nullptr) 
        , weigth(1) {}

    Node(int key)
        : key(key)
        , next(nullptr) 
        , weigth(1) {}

    Node(int key, Node* next) 
        : key(key)
        , next(next) 
        , weigth(1) {}
    
    Node(int key, int weigth) 
        : key(key)
        , next(nullptr)
        , weigth(weigth) {}
        
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

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        Node* newList = new Node[maxValue];

        for (int i = 0; i < maxValue; i++) {

            newList[i] = verticies[i];
        }

        delete [] verticies;
        
        verticies = newList; 
        numOfVertices = maxValue;
    }

    Node* vertex = new Node(v, weigth);
    Node tempNode = verticies[u - 1];
    
    while (tempNode.next != nullptr) {

        tempNode = *tempNode.next;
    }

    tempNode.next = vertex;
}


void Graph::addEdge(int u, int v) {

   int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        Node* newList = new Node[maxValue];

        for (int i = 0; i < maxValue; i++) {

            newList[i] = verticies[i];
        }

        delete [] verticies;
        
        verticies = newList; 
        numOfVertices = maxValue;
    }

    Node* vertex = new Node(v);
    Node tempNode = verticies[u - 1];
    
    while (tempNode.next != nullptr) {

        tempNode = *tempNode.next;
    }

    tempNode.next = vertex;
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
    for (int i = 0; i < numOfVertices; i++) {
        Node* head = &verticies[i];

        while(head->next != nullptr) {

            std::cout << "(" << head->key << ") -- ";
        }

        std::cout << "\bX\n";
   }
}

#endif