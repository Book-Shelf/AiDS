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

    int getMaxPriority(){
        return heap.rootElement().second;
    }

    element Pop() {
        return heap.pop();
    }

    void IncreasePriority(element e, int priority) {

        heap.checkAndIncrease(e, priority);
    }

    // prints priorities from top priority to the lowest
    void printHeap() {

        heap.printHeap();
    }

    int size() {

        return heap.size();
    }

    void check() {

        std::cout << heap.check() << "\n";
    }
};


#endif