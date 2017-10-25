CXX = g++
CXXFLAGS = -Wall

lab8: Animals.o
	$(CXX) $(CXXFLAGS) Animals.o lab8.cpp -o lab8

Animals.o: Animals.cpp Animals.h
	$(CXX) $(CXXFLAGS) -c Animals.cpp

clean:
	rm *.o
	rm *~

run:
	./lab8