CXX = g++
CXXFLAGS = -Wall

lab6: Employee.o Manager.o Supervisor.o
	$(CXX) $(CXXFLAGS) Employee.o Manager.o Supervisor.o lab6.cpp -o lab6

Supervisor.o: Supervisor.cpp Supervisor.h
	$(CXX) $(CXXFLAGS) -c Supervisor.cpp

Manager.o: Manager.cpp Manager.h
	$(CXX) $(CXXFLAGS) -c Manager.cpp

Employee.o: Employee.cpp Employee.h
	$(CXX) $(CXXFLAGS) -c Employee.cpp

clean:
	rm *.o
	rm *~

run:
	./lab6