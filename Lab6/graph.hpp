#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <vector>
#include <stack>

int max(int a, int b) { 

    return a < b ? b : a; 
}

struct Node {

    int key;
    Node* next;
    int weight;
    int dist;                   // distance to the root. Only positive numbers when root is set.
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

    Node(int key, Node* next) 
        : key(key)
        , next(next) 
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
    
    int DFS_Visit(Graph& graph, int vertex, int time, std::stack<int>& stack);

    public:

    Graph();
    Graph(int initMatrixSize);
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
    std::list<int> DFSVisitTranspose(Graph& graph, int vertex, std::list<int>& list);
    static std::stack<int> DFS(Graph& graph);
    Graph transpose();
    static std::list<std::list<int>> SCC(Graph& graph);

};

Graph::Graph()
    : verticies(new Node[1])
    , numOfVertices(1) {}

Graph::Graph(int initVerticiesNum) {

    verticies = new Node[initVerticiesNum];
    numOfVertices = initVerticiesNum;
}

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

    Node* tempNode = &verticies[u - 1];
    
    while (tempNode->next != nullptr) {

        tempNode = tempNode->next;
    }

    tempNode->next = new Node(v, weight);
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

    Node* tempNode = &verticies[u - 1];
    
    while (tempNode->next != nullptr) {

        tempNode = tempNode->next;
    }

    tempNode->next = new Node(v);
}

void Graph::removeEdge(int u, int v) {

    if (max(u, v) <= numOfVertices) {

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

std::list<int> Graph::DFSVisitTranspose(Graph& graph, int vertex, std::list<int>& list) {

    graph.setColour(vertex, 1);
    Node* temp = graph.getVertex(vertex - 1).next;

    while (temp != nullptr) {

        if (graph.getVertex(temp->key - 1).colour == 0) {

            graph.setParent(temp->key, vertex);
            DFSVisitTranspose(graph, temp->key, list);
        }

        temp = temp->next;
    }

    graph.setColour(vertex, 2);
    list.push_back(vertex);

    return list;
}


int Graph::DFS_Visit(Graph& graph, int vertex, int time, std::stack<int>& stack) {

    time += 1;
    graph.setColour(vertex, 1);
    graph.setGTime(vertex, time);
    Node* temp = graph.getVertex(vertex - 1).next;

    while (temp != nullptr) {

        if (graph.getVertex(temp->key - 1).colour == 0) {

            graph.setParent(temp->key, vertex);
            time = DFS_Visit(graph, temp->key, time, stack);
        }

        temp = temp->next;
    }

    graph.setColour(vertex, 2);
    time += 1;
    graph.setBTime(vertex, time);
    stack.push(vertex);

    return time;
}


std::stack<int> Graph::DFS(Graph& graph) {

    for (int i = 1; i <= graph.size(); ++i) {
        graph.setColour(i, 0);
    }

    int time = 0;
    std::stack<int> stack;

    for (int i = 1; i <= graph.size(); ++i) {

        if (graph.getVertex(i - 1).colour == 0) {

            time = graph.DFS_Visit(graph, i, time, stack);
        }
    }

    return stack;
}

Graph Graph::transpose() {

    Graph newGraph(numOfVertices);
    Node* node = nullptr;

    for (int i = 0; i < numOfVertices; i++) {

        node = verticies[i].next;

        while (node != nullptr) {

            newGraph.addEdge(node->key, i + 1);
            node = node->next;
        }
    }

    return newGraph;
}

std::list<std::list<int>> Graph::SCC(Graph& graph) {

    std::stack<int> stack = Graph::DFS(graph);
    Graph transposedGraph = graph.transpose();

    for (int i = 0; i < graph.size(); ++i) {

        transposedGraph.setColour(i, 0);
    }

    int sssCount = 0;
    std::list<int> verticies;
    std::list<std::list<int>> subgraphs;

    while (!stack.empty()) {
        
        if (transposedGraph.getVertex(stack.top() - 1).colour == 0) {

            subgraphs.push_back(transposedGraph.DFSVisitTranspose(transposedGraph, stack.top(), verticies));
            sssCount++;
            verticies.clear();
        }
        stack.pop();
    }

    return subgraphs;

}

#endif