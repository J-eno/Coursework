// File: Pokemon.cpp 
// Project: CMSC 202 Project 2, Fall 2016
// Author: Joel Okpara
// Date: 
// Section 2
// Email: joelo1@umbc.edu
// 
// Contains the function definitions for all the member functions of the Pokemon class

#include "Pokemon.h"

Pokemon::Pokemon()
{
  
}

Pokemon::Pokemon(int num, string name, int cpMin, int cpMax, int rarity)
{
  m_Num = num;
  SetName(name);
  m_MinCP = cpMin;
  m_MaxCP = cpMax;
  SetRarity(rarity);
}

int Pokemon::GetCPMin()
{
  return m_MinCP;
}

int Pokemon::GetCPMax()
{
  return m_MaxCP;
}

int Pokemon::GetRarity()
{
  return m_Rarity;
}

string Pokemon::GetName()
{
  return m_Name;
}

int Pokemon::GetNum()
{
  return m_Num;
}

void Pokemon::SetRarity(int newRarity)
{
  m_Rarity = newRarity;
}

void Pokemon::SetName(string newName)
{
  m_Name = newName;
}

void Pokemon::SetCP(int newCP)
{
  
}
