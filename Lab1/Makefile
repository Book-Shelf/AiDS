CXX := g++
CXXFLAGS := -std=c++17
CXXFLAGS += -O2 -march=native
CXXFLAGS += -Wall -Wextra



.PHONY: default clean

default: setTest.x 


setTest.x: setTest.cpp Set.hpp

%.x: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.x