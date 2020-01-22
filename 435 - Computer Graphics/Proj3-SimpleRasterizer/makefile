CXX = g++
CXXFLAGS = -O3 -I/usr/include/eigen3/ -g

proj3: camera.o geometry.o
	$(CXX) $(CXXFLAGS) camera.o geometry.o proj3.cpp -o proj3

camera.o: camera.cpp camera.h
	$(CXX) $(CXXFLAGS) -c camera.cpp

geometry.o: geometry.cpp geometry.h
	$(CXX) $(CXXFLAGS) -c geometry.cpp

clean:
	rm *.o
	rm *~
run:
	./proj3
