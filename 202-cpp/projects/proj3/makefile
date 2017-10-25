CXX = g++
CXXFLAGS = -g

proj3: LinkedList.o
	$(CXX) $(CXXFLAGS) LinkedList.o proj3.cpp -o proj3

LinkedList.o: LinkedList.cpp LinkedList.h
	$(CXX) $(CXXFLAGS) -c LinkedList.cpp

clean:
	rm *.o
	rm *~
run:
	./proj3