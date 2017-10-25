proj4: Monster.o Game.o Ben.o Pyronite.o Crystalsapien.o
	g++ -g Monster.o Game.o Ben.o Pyronite.o Crystalsapien.o proj4.cpp -o proj4

Monster.o: Monster.h Monster.cpp
	g++ -g -c Monster.cpp

Game.o: Game.h Game.cpp Ben.h Ben.cpp Pyronite.h Pyronite.cpp Monster.h Monster.cpp Crystalsapien.h Crystalsapien.cpp
	g++ -g -c Game.cpp

Ben.o: Ben.h Ben.cpp Pyronite.h Pyronite.cpp Crystalsapien.h Crystalsapien.cpp
	g++ -g -c Ben.cpp

Pyronite.o: Pyronite.h Pyronite.cpp Ben.h Ben.cpp
	g++ -g -c Pyronite.cpp

Crystalsapien.o: Crystalsapien.h Crystalsapien.cpp Ben.h Ben.cpp
	g++ -g -c Crystalsapien.cpp

clean:
	rm *.o
	rm *~

run:
	./proj4
