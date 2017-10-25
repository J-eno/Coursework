// File: Spaceship.cpp
// Project: CMSC 202 Project 5, Fall 2016
// Author: Joel Okpara
// Date: 12/10/16
// Section 2
// Email: joelo1@umbc.edu
// Description: Templated class. Used to build either item ships or personnel ships. Also has overloaded operators to compare templated ships

#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Item.h"
#include "Person.h"

#include <vector>
#include <sstream> //Used to concatenate a string that includes numbers
#include <iomanip> //Used to format weights to make more sense

using namespace std;

template <class T>
class Spaceship
{
 public:
  //Name: Spaceship
  //Default constructor 
  Spaceship();
  
  //Name: Spaceship(string, string, double) Overloaded constructor.
  //Precondition: Requires ship file has been loaded
  //Postcondition: Builds a new templated ship
  Spaceship(string inName, string inType, double inCapacity);

  //Name: GetCargo
  //Precondition: Requires that the ship's cargo has been populated
  //Postcondition: Templated accessor for this ship's cargo
  vector<T> GetCargo() const;

  //Name: GetCargoAt
  //Precondition: Requires that the ship's cargo has been populated
  //Postcondition: Templated accessor for this ship's cargo at a specific location
  const T& GetCargoAt(int index) const;

  //Name: AddCargo
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Adds an item into this ship
  void AddCargo(T inputObject);
  //Name: ToString
  //Precondition: Requires that the ships and cargo have been loaded
  //Postcondition: Used to output information about a specific ship
  string ToString() const;
  //Name: GetCapacity
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Used to access the capacity of a ship
  double GetCapacity() const;
  //Name: GetName
  //Precondition: Requires that the ships have been loaded
  //Postcondition: Used to access the name of a ship
  string GetName() const;

  //Name: operator> (Overloaded) Both ships are templated!
  //Precondition: Requires two ships
  //Postcondition: Returns which ship heavier including cargo
  template <class U>
  bool operator>( Spaceship<U> &otherShip) ;
  //Name: operator< (Overloaded) Both ships are templated!
  //Precondition: Requires two ships
  //Postcondition: Returns which ship lighter including cargo
  template <class U>
  bool operator<( Spaceship<U> &otherShip) ;

private:
  string m_name;
  string m_type;
  double m_capacity;
  vector<T> m_cargo;	
};
//*************************************************************
//You need to implement all of this code - it is templated so we can't split the file

//Name: Spaceship(string, string, double) Overloaded constructor.
//Precondition: Requires ship file has been loaded
//Postcondition: Builds a new templated ship
template <class T>
Spaceship<T>::Spaceship(string inName, string inType, double inCapacity)
{
  m_name = inName;
  m_type = inType;
  m_capacity = inCapacity;
}

//Name: GetCargo
//Precondition: Requires that the ship's cargo has been populated
//Postcondition: Templated accessor for this ship's cargo
template <class T>
vector<T> Spaceship<T>::GetCargo() const
{
  return m_cargo;
}

//Name: GetCargoAt
//Precondition: Requires that the ship's cargo has been populated
//Postcondition: Templated accessor for this ship's cargo at a specific location
template <class T>
const T& Spaceship<T>::GetCargoAt(int index) const
{
  return m_cargo.at(index);
}

//Name: AddCargo
//Precondition: Requires that the ships have been loaded
//Postcondition: Adds an item into this ship
template <class T>
void Spaceship<T>::AddCargo(T inputObject)
{
  m_cargo.push_back(inputObject);
}

//Name: ToString
//Precondition: Requires that the ships and cargo have been loaded
//Postcondition: Used to output information about a specific ship
template <class T>
string Spaceship<T>::ToString() const
{
  //creates two stringstreams
  stringstream ss,tt;
  double weight = 0.0;
  string strWeight, strCapacity, output;

  //for each item in m_cargo
  for( unsigned int i = 0; i < m_cargo.size(); ++i)
    {
      //add Item's weight to weight variable
      weight += m_cargo[i].GetWeight();
    }
  //puts doubles into string stream then outputs it as string
  ss << fixed << setprecision(2) << weight;
  ss >> strWeight;
  tt << fixed << setprecision(2) << m_capacity;
  tt >> strCapacity;

  //creates string of all the ship's info
  output = "Ship Type: " + m_type
    + "\nShip Name: " + m_name
    + "\nTotal Weight: " + strWeight
    + "\nTotal Capacity: " + strCapacity + "\n";
  return output;
}

//Name: GetCapacity
//Precondition: Requires that the ships have been loaded
//Postcondition: Used to access the capacity of a ship
template <class T>
double Spaceship<T>::GetCapacity() const
{
  return m_capacity;
}

//Name: GetName
//Precondition: Requires that the ships have been loaded
//Postcondition: Used to access the name of a ship
template <class T>
string Spaceship<T>::GetName() const
{
  return m_name;
}

//Name: operator> (Overloaded) Both ships are templated!
//Precondition: Requires two ships
//Postcondition: Returns which ship heavier including cargo
template <class T>
template <class U>
bool Spaceship<T>::operator>(Spaceship<U> &otherShip)
{
  double thisWeight = 0.0;
  double otherWeight = 0.0;
  //vector of the other ship's cargo
  vector<U> otherCargo = otherShip.GetCargo();
  
  //calculates the cargo on this ship
  for(unsigned int i = 0; i < m_cargo.size(); ++i)
    {
      thisWeight += m_cargo[i].GetWeight();
    }

  //calculates the cargo on the other ship
  for(unsigned int j = 0; j < otherCargo.size(); ++j)
    {
      otherWeight += otherCargo[j].GetWeight();
    }
  //if this ship's weight it greater than the other ship's weight
  if(thisWeight > otherWeight)
    {
      return true;
    }
  else 
    {
      return false;
    }

}

//Name: operator< (Overloaded) Both ships are templated!
//Precondition: Requires two ships
//Postcondition: Returns which ship lighter including cargo
template <class T>
template <class U>
bool Spaceship<T>::operator<(Spaceship<U> &otherShip)
{
  double thisWeight = 0.0;
  double otherWeight = 0.0;
  //vector of the other ship's cargo
  vector<U> otherCargo = otherShip.GetCargo();

  //calculates the weight of this ship
  for(unsigned int i = 0; i < m_cargo.size(); ++i)
    {
      thisWeight += m_cargo[i].GetWeight();
    }
  //calculates the weight of the other ship
  for(unsigned int j = 0; j < otherCargo.size(); ++j)
    {
      otherWeight += otherCargo[j].GetWeight();
    }

  // this ship weighs less than the other ship
  if(thisWeight < otherWeight)
    {
      return true;
    }
  else
    {
      return false;
    }

}

#endif
