// File: Item.cpp
// Project: CMSC 202 Project 5, Fall 2016
// Author: Joel Okpara
// Date: 12/10/16
// Section 2
// Email: joelo1@umbc.edu
// Description: Class defining cargo items. Used in item ships.

#include "Item.h"
//constructor for Item
Item::Item(int inId, string inName, float inWeight)
{
  m_id = inId;
  m_name = inName;
  m_weight = inWeight;
}

//Accessors for Item
int Item::GetId() const
{
  return m_id;
}

string Item::GetName() const
{
  return m_name;
}

float Item::GetWeight() const
{
  return m_weight;
}

//Name: ToString
//Precondition: Requires item to be formatted for output
//Postcondition: Creates single string for output
string Item::ToString() const
{
  //creates two stringstreams
  stringstream ss, tt;
  string strID, strWeight, output;
  //inputs non-strings into the sstream and outputs the values into a string
  ss << m_id;
  ss >> strID;
  tt << fixed << setprecision(2) << m_weight;
  tt >> strWeight;
  
  output = "Item Name: " + m_name 
    + "\nID: " + strID 
    + "\nWeight: " + strWeight + "\n";

  return output;
  
}
