CXX = g++
CXXFLAGS = -Wall

driver: Graph.o
	$(CXX) $(CXXFLAGS) Graph.o Driver.cpp -o driver

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp

clean:
	rm *.o
	rm *~
run:
	./driver