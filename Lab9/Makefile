CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -march=native
CPPFLAGS += -Wall -Wextra

.PHONY: default clean
default: floydWarshall.x

floydWarshall.x: floydWarshall.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x