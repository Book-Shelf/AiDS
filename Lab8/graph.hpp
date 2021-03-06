#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "priorityQueue.hpp"
#include <chrono>

typedef std::pair<int, int> element;

int max(int a, int b) { 

    return a < b ? b : a; 
}


struct Destination {
    
    double time;
    int distance1;
    int distance2;

    Destination(double time, int dist1, int dist2)
    : time(time)
    , distance1(dist1)
    , distance2(dist2) {}
};


struct Node {

    int key;
    Node* next;
    int weight;
    int dist;                   // distance to the source.
    int colour;                 // 0 white, 1 gray, 2 black
    int gTime;                  // visited time
    int bTime;                  // time when all neighbours were processed
    int parent;

    Node()
        : key(1)
        , next(nullptr) 
        , weight(1) 
        , dist(-1) 
        , colour(0) 
        , gTime(0)
        , bTime(0)
        , parent(-1) {}

    Node(int key)
        : key(key)
        , next(nullptr) 
        , weight(1) 
        , dist(-1) 
        , colour(0)
        , gTime(0)
        , bTime(0)
        , parent(-1) {}

    Node(int key, int weight) 
        : key(key)
        , next(nullptr)
        , weight(weight)
        , dist(-1) 
        , colour(0)
        , gTime(0)
        , bTime(0)
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
    void setColour(int vertex, int colour);
    void setBTime(int vertex, int time);
    void setGTime(int vertex, int time);
    void setParent(int vertex, int parent);
    Node getVertex(int x);
    Destination Dijkstra(int startV, int endV1, int endV2);
    
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


void Graph::setColour(int vertex, int colour) {

    verticies[vertex - 1].colour = colour;
}


void Graph::setBTime(int vertex, int time) {

    verticies[vertex - 1].bTime = time;
}


void Graph::setGTime(int vertex, int time) {

    verticies[vertex - 1].gTime = time;
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


Destination Graph::Dijkstra(int startV, int endV1, int endV2) {

    auto start = std::chrono::high_resolution_clock::now();

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(stop - start);

    if (verticies[endV1 - 1].dist == INT32_MAX) {

        verticies[endV1 - 1].dist = -1;
    } 

    if (verticies[endV2 - 1].dist == INT32_MAX) {

        verticies[endV2 - 1].dist = -1;
    }

    return Destination(duration.count(), verticies[endV1 - 1].dist, verticies[endV2 - 1].dist);
}

#endif