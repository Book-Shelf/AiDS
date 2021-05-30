#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Set.hpp"
#include "stack.h"


int max(int a, int b) { 

    return a < b ? b : a; 
}




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


struct Edge {

    int source;
    int destination;
    int weight;

    Edge() 
    : source(-1)
    , destination(-1)
    , weight(-1) {}

    Edge(int source, int destination, int weight)
    : source(source)
    , destination(destination)
    , weight(weight) {}
};


void swap(Edge& a, Edge& b) {

    Edge temp = a;
    a = b;
    b = temp;
}


void quicksort(std::vector<Edge>& arr){
    Stack<size_t> leftStack(arr.size());
    Stack<size_t> rightStack(arr.size());
    leftStack.push(0);
    rightStack.push(arr.size() - 1);
    while (!leftStack.empty()) {
        int left = leftStack.pop();
        int right = rightStack.pop();
        int pivot = arr[(left + right) / 2].weight;
        int i = left;
        int j = right;
        do
        {
            while (arr[i].weight < pivot)
                i++;

            while (arr[j].weight > pivot)
                j--;

            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (left < j) {
            leftStack.push(left);
            rightStack.push(j);
        }
        if (right > i) {
            leftStack.push(i);
            rightStack.push(right);
        }
    }
}


// Adjacency List representation
class Graph  {
    private:
    Node* verticies;
    int numOfVertices;
    bool directed;
    int numOfEdges;
    
    void removeE(int u, int v);
    void addE(int u, int v, int weight);
    void initDistance(int source);
    Set<int> makeSet(int vertex);
    Set<int>& findSet(int vertex, std::vector<Set<int>>& sets);
    void UNION(Set<int>& set1, Set<int>& set2, std::vector<Set<int>>& sets);
    std::vector<Edge> sortEdges();

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
    void MST_Kruskal();
    
};

Graph::Graph()
    : verticies(new Node[1])
    , numOfVertices(1) 
    , directed(0) 
    , numOfEdges(0) {}

Graph::Graph(int initVerticiesNum, bool dir) {

    verticies = new Node[initVerticiesNum];
    numOfVertices = initVerticiesNum;
    directed = dir;
    numOfEdges = 0;
}

Graph::Graph(bool directed) 
    : verticies(new Node[1])
    , numOfVertices(1)
    , directed(directed)
    , numOfEdges(0) {}

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

Set<int> Graph::makeSet(int vertex) {

    Set<int> set;
    set.Insert(vertex);

    return set;
}

Set<int>& Graph::findSet(int vertex, std::vector<Set<int>>& sets) {

    for (std::vector<Set<int>>::iterator it = sets.begin(); it != sets.end(); ++it) {

        if (it->IsMember(vertex)) 
            return *it;
    }

    return *new Set<int>;
}

void Graph::UNION(Set<int>& set1, Set<int>& set2, std::vector<Set<int>>& sets) {

    set1 = Set<int>::Union(set1, set2);
    set2 = sets.back();
    sets.pop_back();
}


std::vector<Edge> Graph::sortEdges() {

    std::vector<Edge> sortedEdges(numOfEdges);
    int edgeCount = 0;
    Node* temp = nullptr;

    for (int i = 0; i < numOfVertices; i++) {

        temp = verticies[i].next;

        while (temp != nullptr) {

            if (temp->key >= (i + 1)) {

                sortedEdges.at(edgeCount) = Edge(i + 1, temp->key, temp->weight);
                edgeCount++;
            }

            temp = temp->next;
        }
    }

    quicksort(sortedEdges);

    return sortedEdges;
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

    numOfEdges++;
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

    numOfEdges++;
}

void Graph::removeEdge(int u, int v) {

    if (max(u, v) <= numOfVertices) {

        removeE(u, v);

        if(!directed) removeE(v, u);
    }

    numOfEdges--;
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

void Graph::MST_Kruskal() {

    std::vector<Set<int>> sets;

    for (int i = 0; i < numOfVertices; i++) 
        sets.push_back(makeSet(i));
    
    Set<int>& fSet = findSet(2,sets);
    fSet.Insert(1);
    // std::cout << fSet.size() << "\n";
    // fSet.print();
    UNION(findSet(2, sets), findSet(3, sets), sets);

    for (Set<int> set : sets) {
        set.print();
    }

    std::vector<Edge> sortedEdges = sortEdges();

    for (int i = 0; i < numOfEdges; i++) {

        std::cout << sortedEdges[i].source << " -> ";
        std::cout << sortedEdges[i].destination << " = ";
        std::cout << sortedEdges[i].weight << "\n";
    }

    std::cout << "\n";
}

#endif