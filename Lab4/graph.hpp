#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <queue>

int max(int a, int b) { 

    return a < b ? b : a; 
}

struct Node {

    int key;
    Node* next;
    int weight;

    Node()
        : key(1)
        , next(nullptr) 
        , weight(1) {}

    Node(int key)
        : key(key)
        , next(nullptr) 
        , weight(1) {}

    Node(int key, Node* next) 
        : key(key)
        , next(next) 
        , weight(1) {}
    
    Node(int key, int weight) 
        : key(key)
        , next(nullptr)
        , weight(weight) {}
        
};

// Adjacency List representation
class Graph  {
    private:
    Node* verticies;
    int numOfVertices;
    int root;                           // when transformed into a tree using BFS

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
    Node getVertex(int x);
    void setRoot(int root);
    static Graph BFS(Graph& graph, int start);    
    std::list<int> get_Path(int end);           // path from the root to the end vertex
    int get_hops(int end);                // distance between root and end vertex
};

Graph::Graph()
    : verticies(new Node[1])
    , numOfVertices(1) 
    , root(-1) {}

Graph::Graph(int initVerticiesNum) {

    verticies = new Node[initVerticiesNum];
    numOfVertices = initVerticiesNum;
    root = -1;
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

Node Graph::getVertex(int x) {

    return verticies[x];
}

void Graph::setRoot(int roo) {

    root = roo;
}

//Breadth First Search
Graph Graph::BFS(Graph& graph, int start) {
    
    std::queue<int> queue;  
    Graph tree(graph.size());
    bool visited[graph.size()] = {0};         // array of visited vertecies
    int poped = 0;                      // vertex that was removed from the queue
    visited[start - 1] = 1;
    queue.push(start);
    Node* temp = nullptr;

    while (!queue.empty()) {
        
        poped = queue.front();
        queue.pop();

        temp = graph.getVertex(poped - 1).next;

        while(temp != nullptr) {

            int nodeKey = temp->key;
            
            if(visited[nodeKey - 1] == 0){      // Check if it was visited

                queue.push(nodeKey);
                visited[nodeKey - 1] = 1;
                tree.addEdge(poped, nodeKey);
            }        

            temp = temp->next;
        }
    }

    tree.setRoot(start);

    return tree;
}

std::list<int> Graph::get_Path(int end) {

    std::queue<int> queue;  
    bool visited[numOfVertices] = {0};         // array of visited vertecies
    int poped = 0;                      // vertex that was removed from the queue
    Node* temp = nullptr;               // pointer to next verticies
    std::list<int> path;
    int pred[numOfVertices] = {0};      // argument in given index is a parent vertex

    visited[root - 1] = 1;
    queue.push(root);

    while (!queue.empty()) {
        
        poped = queue.front();
        queue.pop();

        temp = verticies[poped - 1].next;

        while (temp != nullptr) {

            int nodeKey = temp->key;
            
            if (visited[nodeKey - 1] == 0){      // Check if it was visited


                visited[nodeKey - 1] = 1;
                pred[nodeKey - 1] = poped;
                queue.push(nodeKey);
            }        

            if (nodeKey == end) {

                path.push_front(nodeKey);

                while(nodeKey != root) {

                    path.push_front(pred[nodeKey - 1]);
                    nodeKey = pred[nodeKey - 1];
                }


                return path;
            }

            temp = temp->next;
        }
    }

    return path;
} 


int Graph::get_hops(int end) {

    std::queue<int> queue;  
    bool visited[numOfVertices] = {0};         // array of visited vertecies
    int poped = 0;                      // vertex that was removed from the queue
    Node* temp = nullptr;               // pointer to next verticies
    int dist[numOfVertices] = {0};      // argument in given index is a parent vertex

    visited[root - 1] = 1;
    queue.push(root);

    while (!queue.empty()) {
        
        poped = queue.front();
        queue.pop();

        temp = verticies[poped - 1].next;

        while (temp != nullptr) {

            int nodeKey = temp->key;
            
            if (visited[nodeKey - 1] == 0){      // Check if it was visited


                visited[nodeKey - 1] = true;
                dist[nodeKey - 1] = dist[poped - 1] + 1;
                queue.push(nodeKey);
            }        

            if (nodeKey == end) {

                return dist[nodeKey - 1];
            }

            temp = temp->next;
        }
    }

    return -1;
} 

#endif