CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -march=native
CPPFLAGS += -Wall -Wextra


.PHONY: default clean

default: TestQueue.x

TestQueue.x: TestQueue.cpp priorityQueue.hpp heap.hpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x