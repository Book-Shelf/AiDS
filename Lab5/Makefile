CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -g -march=native
CPPFLAGS += -Wall -Wextra


.PHONY: default clean

default: sort.x

DFS.x: sort.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x
