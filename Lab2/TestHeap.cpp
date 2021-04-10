#include "heap.hpp"
#include <string>

typedef std::pair<std::string, int> element;

int main() {

    element p("Ola", 3);
    HEAP_HXX::Heap<std::string> heap;
    std::vector<element>  vec;

    vec.push_back(p);
    vec.push_back(element("kota", 13));
    vec.push_back(element("ma", 5));

    heap.build(vec);
    heap.printHeap();

    element pop = heap.pop();
    std::cout << pop.first << "\n";
    heap.push(element("Mizia", 18));
    heap.push(element("Mizia", 6));
    heap.printHeap();
    return 0;
}