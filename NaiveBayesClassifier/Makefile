CXX=g++
CXXFLAGS=-g -Wall -std=c++11
OBJS=bayes.o
all: bayes
bayes: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)
bayes.o: bayess.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c bayess.cpp
clean:
	rm -f *.o bayes