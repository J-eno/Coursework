// File: ReadySupply.cpp
// Project: CMSC 202 Project 5, Fall 2016
// Author: Joel Okpara
// Date: 12/11/2016
// Section 2
// Email: joelo1@umbc.edu

// Description: Class designed to load files into vectors. Uses the proj5_cargo.txt to build Items and Persons. Uses proj5_ships.txt to build item ships and person ships. After ships are “built” they are filled with the appropriate cargo: person ships are filled with persons (only) and item ships are filled with items (only)

#include "ReadySupply.h"


//Name: ReadySupply() and ReadySupply(string, string)
//Precondition: Requires two files a ship file and a cargo file
//Postcondition: Populates two vectors
ReadySupply::ReadySupply(string shipFile, string cargoFile)
{
  m_shipFile = shipFile;
  m_cargoFile = cargoFile;
  LoadShips();
  LoadCargo();

  
}

//Name: LoadShips
//Precondition: Requires a ships file
//Postcondition: Builds TWO vectors
//Ship 1: Holds people (person)
//Ship 2: Holds cargo (items)
void ReadySupply::LoadShips()
{
  string sName, sType;
  double sCapacity;
  fstream ships;
  //opens file of ships
  ships.open(m_shipFile.c_str());
  //while we can get this information
  while(ships >> sType >> sName >> sCapacity)
    {
      //if the ship's type is item
      if(sType == "Item")
	{
	  //create an Item ship and put it in the itemShip vector
	  Spaceship<Item> aShip(sName, sType, sCapacity);
      	  m_itemShips.push_back(aShip);
	}
      else
	{
	  //create a Person ship and put it in the personsShip vector
	  Spaceship<Person> aShip(sName, sType, sCapacity);
	  m_personShips.push_back(aShip);
	}
    }
  ships.close();
}

//Name: LoadCargo
//Precondition: Requires a cargo file
//Postcondition: Builds TWO vectors
//Cargo 1: Holds people (person)
//Cargo 2: Holds cargo (item)
void ReadySupply::LoadCargo()
{
  string type;
  //variables for People
  string fName, lName;
  double weight;
  int age, id;
  //variables for Items
  string cName;
  int cID;
  double cWeight;

  //open cargoFile
  fstream cargos;
  cargos.open(m_cargoFile.c_str());
  //while we can get the type
  while(cargos >> type)
    {
      //if cargo is an item
      if(type == "i")
	{
	  //read in it's info
	  cargos >> cID >> cName >> cWeight;
	  //create an Item object and put it in Item vector
	  Item anItem(cID, cName, cWeight);
	  m_itemCargo.push_back(anItem);
	}
      else
	{
	  //else read in the person's info
	  cargos >> fName >> lName >> weight >> age >> id;
	  //create a Person object and put it in the person vector
	  Person aPerson(fName, lName, weight, age, id);
	  m_personCargo.push_back(aPerson);
	}
    }
  cargos.close();
}

//Name: GetItemShips
//Precondition: Requires that item ships have been built
//Postcondition: Returns a vector of all item ships
vector< Spaceship<Item> > ReadySupply::GetItemShips()
{
  return m_itemShips;
}

//Name: GetPersonShips
//Precondition: Requires that person ships have been built
//Postcondition: Returns a vector of all person ships
vector< Spaceship<Person> > ReadySupply::GetPersonShips()
{
  return m_personShips;
}

//Name: GetItemCargo
//Precondition: Requires that all item vectors have been built
//Postcondition: Returns a vector of all items
vector<Item> ReadySupply::GetItemCargo()
{
  return m_itemCargo;
}

//Name: GetPersonCargo
//Precondition: Requires that all person vectors have been built
//Postcondition: Returns a vector of all people (person)
vector<Person> ReadySupply::GetPersonCargo()
{
  return m_personCargo;
}
