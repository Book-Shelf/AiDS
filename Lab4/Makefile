CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -g -march=native
CPPFLAGS += -Wall -Wextra


.PHONY: default clean

default: graph.x

graph.x: graph.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x
