CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -march=native
CPPFLAGS += -Wall -Wextra

.PHONY: default clean
default: Prim.x Kruskal.x

Prim.x: Prim.cpp graph.hpp priorityQueue.hpp Set.hpp heap.hpp
Kruskal.x: Kruskal.cpp graph.hpp stack.h Set.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x