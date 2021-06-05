#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "priorityQueue.hpp"
#include <list>
#include <stack>

typedef std::pair<int, int> element;

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
    int DFS_Visit(Graph& graph, int vertex, int time, std::stack<int>& stack);

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
    void Dijkstra(int startV);
    Graph transpose();
    std::list<int> DFSVisitTranspose(Graph& graph, int vertex, std::list<int>& list);
    static std::stack<int> DFS(Graph& graph);
    static std::list<std::list<int>> SCC(Graph& graph);
    static void printCycles(Graph& graph);
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

    std::list<int> verticies;
    std::list<std::list<int>> subgraphs;

    while (!stack.empty()) {
        
        if (transposedGraph.getVertex(stack.top() - 1).colour == 0) {

            subgraphs.push_back(transposedGraph.DFSVisitTranspose(transposedGraph, stack.top(), verticies));
            verticies.clear();
        }

        stack.pop();
    }

    return subgraphs;

}


void Graph::printCycles(Graph& graph) {

    std::list<std::list<int>> sccs = Graph::SCC(graph);
    // std::cout << sccs.size() << "\n";
    int i = 0;

    // std::cout << "CYKLE: \n";


    for (std::list<int> subgraph : sccs) {

        if (subgraph.size() >= 2) {

            i++;
            // std::cout << "[" << i << "]\t";

            // for(int element : subgraph) {

            //     // std::cout << "(" << element << ")" << "-->";
            // }

            // std::cout << "\b\b\b   \n";
        } else {

            int vertex = *subgraph.begin();
            Node* next = graph.getVertex(vertex - 1).next;
            
            while (next != nullptr) {

                if (next != nullptr && next->key == vertex){

                    i++;
                    // std::cout << "[" << i << "]\t";
                    // std::cout << "(" << vertex << ")" << "-->" << "(" << vertex  << ")\n";
                    break;
                }

                next = next->next;
            }
        }
    }

    // std::cout << "Ilość cykli: " << i << "\n";
    std::cout << i << '\n';
}

#endif