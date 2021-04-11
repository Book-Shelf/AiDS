CXX := g++
CXXFLAGS := -std=c++17
CXXFLAGS += -O2 -march=native
CXXFLAGS += -Wall -Wextra



.PHONY: default clean

default: graph.x 


graph.x: graph.cpp graph.hpp

%.x: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.x