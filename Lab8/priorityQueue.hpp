#ifndef PRIORITYQUEUE_HXX
#define PRIORITYQUEUE_HXX
#include "heap.hpp"

template<class T>
class PQueue {

    typedef std::pair<T, int> element;
    
    private:
        Heap<T> heap;
    
    public:

    PQueue() : heap(*new Heap<T>) {}

    // Constructor: build heap based on list of elements
    PQueue(std::vector<element> elements) {

        heap.build(elements);
    }

    void InsertElement(element e) {
        heap.push(e);
    }

    int getMinPriority(){
        return heap.rootElement().second;
    }

    // returns first element in pair associated with min priority
    T getMinNodePriority(){
        return heap.rootElement().first;
    }

    element Pop() {
        return heap.pop();
    }

    void IncreasePriority(element e, int priority) {

        heap.checkAndIncrease(e, priority);
    }

    // prints priorities from the lowest priority to the top
    void printHeap() {

        heap.printHeap();
    }

    int size() {

        return heap.size();
    }

    void check() {

        std::cout << heap.check() << "\n";
    }

    bool empty() {

        return heap.empty();
    }
};


#endif