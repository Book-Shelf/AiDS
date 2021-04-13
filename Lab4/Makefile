CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -g -march=native
CPPFLAGS += -Wall -Wextra


.PHONY: default clean

default: graph.x BFS.x DFS.

graph.x: graph.cpp graph.hpp
BFS.x: BFS.cpp graph.hpp
DFS.x: DFS.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x
