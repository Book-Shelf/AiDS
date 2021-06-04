CPP := g++
CPPFLAGS := -std=c++17
CPPFLAGS += -O2 -march=native
CPPFLAGS += -Wall -Wextra

.PHONY: default clean
default: przemytnicy.x

przemytnicy.x: przemytnicy.cpp

%.x: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm *.x