CXX = g++
CXXFLAGS = -Wall

driver: LazyBST.o
	$(CXX) $(CXXFLAGS) LazyBST.o test1.cpp -o driver

Graph.o: LazyBST.cpp LazyBST.h
	$(CXX) $(CXXFLAGS) -c LazyBST.cpp

clean:
	rm *.o
	rm *~
run:
	./driver