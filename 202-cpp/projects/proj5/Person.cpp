// File: Person.cpp 
// Project: CMSC 202 Project 5, Fall 2016
// Author: Joel Okpara
// Date: 12/10/16
// Section 2
// Email: joelo1@umbc.edu
// Description: Class defining people. Used in personnel ships.

#include "Person.h"

//Constructor for Person
Person::Person(string infName, string inlName, double inWeight, int inAge, int inID)
{
  m_fName = infName;
  m_lName = inlName;
  m_weight = inWeight;
  m_age = inAge;
  m_id = inID;
}

//Accessors for Person
int Person::GetId() const
{
  return m_id;
}

string Person::GetFName() const
{
  return m_fName;
}

string Person::GetLName() const
{
  return m_lName;
}

int Person::GetAge() const
{
  return m_age;
}

double Person::GetWeight() const
{
  return m_weight;
}


// Name: ToString
// Precondition: Needs a Person object to create output string
// Postcondition: Creates a single string for output
string Person::ToString() const
{
  stringstream ss,tt;
  string strAge, strWeight, output;
  //non-strings put in sstreams then outputted in strings
  ss << m_age;
  ss >> strAge;
  tt << m_weight;
  tt >> strWeight;

  output = "First Name: " + m_fName
    + "\nLast Name: " + m_lName
    + "\nAge: " + strAge
    + "\nWeight: " + strWeight + "\n";

  return output;
}
