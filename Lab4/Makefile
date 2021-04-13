CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -g -march=native
CPPFLAGS += -Wall -Wextra


.PHONY: default clean

default: BFS.x DFS.x

BFS.x: BFS.cpp graph.hpp
DFS.x: DFS.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x
