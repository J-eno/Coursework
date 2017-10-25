CXX = g++
CXXFLAGS = -Wall

lab5: Point23.o
	$(CXX) $(CXXFLAGS) Point23.o lab5.cpp -o lab5

Point23.o: Point23.cpp Point23.h
	$(CXX) $(CXXFLAGS) -c Point23.cpp

clean:
	rm *.o
	rm *~

run: 
	./lab5