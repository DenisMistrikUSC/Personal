CXX=g++
CXXFLAGS=-g -Wall -std=c++11
OBJS=coloring.o
all: coloring
coloring: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)
coloring.o: coloring.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c coloring.cpp