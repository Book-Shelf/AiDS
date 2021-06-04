#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "priorityQueue.hpp"

typedef std::pair<int, int> element;

int max(int a, int b) { 

    return a < b ? b : a; 
}


struct Node {

    int key;
    Node* next;
    int weight;
    int dist;                   // distance to the source.
    int parent;

    Node()
        : key(1)
        , next(nullptr) 
        , weight(1) 
        , dist(-1) 
        , parent(-1) {}

    Node(int key)
        : key(key)
        , next(nullptr) 
        , weight(1) 
        , dist(-1) 
        , parent(-1) {}

    Node(int key, int weight) 
        : key(key)
        , next(nullptr)
        , weight(weight)
        , dist(-1) 
        , parent(-1) {}
        
};

// Adjacency List representation
class Graph  {
    private:
    Node* verticies;
    int numOfVertices;
    bool directed;
    
    void removeE(int u, int v);
    void addE(int u, int v, int weight);
    void initDistance(int source);
    void relax(PQueue<int>& queue, int vertex, int adjacentVertex, int Weight);

    public:

    Graph();
    Graph(int initVerticiesNum, bool dir);
    Graph(bool directed);
    ~Graph();

    void addEdge(int u, int v, int weight);          // u - start vertex, v - end vertex
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int size();
    void print();
    void setDistance(int vertex, int distance);
    void setParent(int vertex, int parent);
    Node getVertex(int x);
    void Dijkstra(int startV);
    Graph transpose();
    
};

Graph::Graph()
    : verticies(new Node[1])
    , numOfVertices(1) 
    , directed(0) {}

Graph::Graph(int initVerticiesNum, bool dir) {

    verticies = new Node[initVerticiesNum];
    numOfVertices = initVerticiesNum;
    directed = dir;
}

Graph::Graph(bool directed) 
    : verticies(new Node[1])
    , numOfVertices(1)
    , directed(directed) {}

Graph::~Graph () {

    for (int i = 0; i < numOfVertices; ++i) {
        
        Node* temp = nullptr;
        Node* delNode = verticies[i].next;

        while (delNode != nullptr) {

             temp = delNode->next;
            delete delNode;
            delNode = temp;
        }
    }

    delete [] verticies;
}

void Graph::removeE(int u, int v)  {

    Node* temp = verticies[u - 1].next;
    Node* previous = &verticies[u - 1];

    while (temp != nullptr) {

        if (temp->key == v) {

            previous->next = temp->next;

            delete temp;

            return ;
        } else {

            previous = temp;
            temp = temp->next;
        }
    }
}


void Graph::addE(int u, int v, int weight) {

    Node* tempNode = &verticies[u - 1];
        
    while (tempNode->next != nullptr) {

        tempNode = tempNode->next;
    }

    tempNode->next = new Node(v, weight);
}


void Graph::addEdge(int u, int v, int weight) {

    int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        Node* newList = new Node[maxValue];

        for (int i = 0; i < numOfVertices; ++i) {

            newList[i].next = verticies[i].next;
        }

        delete [] verticies;
        verticies = newList; 
        numOfVertices = maxValue;
    }

    addE(u, v, weight);

    if (!directed) {

        addE(v, u, weight);
    }
}


void Graph::addEdge(int u, int v) {

   int maxValue = max(u, v);

    if (numOfVertices < maxValue) {

        Node* newList = new Node[maxValue];

        for (int i = 0; i < numOfVertices; ++i) {

            newList[i].next = verticies[i].next;
        }

        delete [] verticies;
        verticies = newList; 
        numOfVertices = maxValue;
    }

    addE(u, v, 1);

    if (!directed) {

        addE(v, u, 1);
    }
}

void Graph::removeEdge(int u, int v) {

    if (max(u, v) <= numOfVertices) {

        removeE(u, v);

        if(!directed) removeE(v, u);
    }
}

bool Graph::isEdge(int u, int v) {

    if (max(u, v) <= numOfVertices) {

        Node* temp = verticies[u - 1].next;

        while (temp != nullptr) {

            if (temp->key == v) return true;

            temp = temp->next;
        }
    }

    return false;
}

int Graph::size() {

    return numOfVertices;
}

void Graph::print()
{
    for (int i = 0; i < numOfVertices; i++) {
        Node head = verticies[i];

        std::cout << "(" << i + 1 << ")--";

        while(head.next != nullptr) {

            head = *head.next;
            std::cout << "(" << head.key << ")--";
        }

        std::cout << "X\n";
   }
}

void Graph::setDistance(int vertex, int distance) {

    verticies[vertex].dist = distance;
}


void Graph::setParent(int vertex, int parent) {

    verticies[vertex - 1].parent = parent;
}


Node Graph::getVertex(int x) {

    return verticies[x];
}


void Graph::initDistance(int source) {

    for (int i = 0; i < numOfVertices; i++) {

        verticies[i].dist = INT32_MAX;
    }

    verticies[source - 1].dist = 0;
}


void Graph::relax(PQueue<int>& queue, int vertex, int adjacentVertex, int Weight) {

    int distance = verticies[vertex].dist + Weight;

    if (verticies[adjacentVertex].dist > distance) {

        verticies[adjacentVertex].dist = distance;
        queue.InsertElement(element(adjacentVertex + 1, verticies[adjacentVertex].dist));
    }
}


void Graph::Dijkstra(int startV) {

    initDistance(startV);
    PQueue<int> queue(size());                  // pairs of elements (vertex, weight)
    int vertex = 0;

    queue.InsertElement(element(startV, 0));


    while (!queue.empty()) {
        
        vertex = queue.Pop().first;
        Node* temp = verticies[vertex - 1].next;
        

        while (temp != nullptr) {

            relax(queue, vertex - 1, temp->key - 1, temp->weight);
            temp = temp->next;
        }
    }
}


Graph Graph::transpose() {

    Graph newGraph(numOfVertices);
    Node* node = nullptr;

    for (int i = 0; i < numOfVertices; i++) {

        node = verticies[i].next;

        while (node != nullptr) {

            newGraph.addEdge(node->key, i + 1, node->weight);
            node = node->next;
        }
    }

    return newGraph;
}


int* writeShortestPathToSource(Graph& graph) {

    int* pathsFromSource = new int[graph.size()];

    for (int i = 0; i < graph.size(); i++) {

        pathsFromSource[i] = graph.getVertex(i).dist;
    }

    return pathsFromSource;
}

#endif