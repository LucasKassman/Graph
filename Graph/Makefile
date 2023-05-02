# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=GraphTest

all: $(OUTFILES)

GraphTest: GraphTest.cpp Graph.cpp Graph.h DisjointSet.h DisjointSet.cpp
	$(CXX) $(CXXFLAGS) -o GraphTest GraphTest.cpp Graph.cpp DisjointSet.cpp

clean:
	$(RM) $(OUTFILES) *.o
