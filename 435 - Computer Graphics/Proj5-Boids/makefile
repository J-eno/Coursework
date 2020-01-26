CXX = g++
CXXFLAGS = -O3 -I/usr/include/eigen3/ -g

proj4: entities.o 
	$(CXX) $(CXXFLAGS) entities.o proj5.cpp -o proj5

entities.o: entities.cpp entities.h
	$(CXX) $(CXXFLAGS) -c entities.cpp

clean:
	rm *.o
	rm *~
run:
	./proj5
