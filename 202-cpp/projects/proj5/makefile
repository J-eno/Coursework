proj5: ReadySupply.o Item.o Person.o Spaceship.h ManageShips.o
	g++ -g ReadySupply.o Item.o Person.o ManageShips.o proj5.cpp -o proj5

Item.o: Item.h Item.cpp
	g++ -g -c Item.cpp

Person.o: Person.h Person.cpp
	g++ -g -c Person.cpp

ManageShips.o: ManageShips.h ManageShips.cpp Person.h Person.cpp Item.h Item.cpp Spaceship.h ReadySupply.h
	g++ -g -c ManageShips.cpp

ReadySupply.o: ReadySupply.h ReadySupply.cpp proj5.cpp
	g++ -g -c ReadySupply.cpp

clean:
	rm *.o
	rm *~

run:
	./proj5

run1:
	./proj5 proj5_ships.txt proj5_cargo.txt 