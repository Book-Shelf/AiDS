CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -march=native
CPPFLAGS += -Wall -Wextra

.PHONY: default clean
default: przemytnicy.x skarbonki.x

przemytnicy.x: przemytnicy.cpp graph.hpp priorityQueue.hpp heap.hpp
skarbonki.x: skarbonki.cpp graph.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x