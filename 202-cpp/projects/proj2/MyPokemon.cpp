// File: MyPokemon.cpp 
// Project: CMSC 202 Project 2, Fall 2016
// Author: Joel Okpara
// Date: 
// Section 2
// Email: joelo1@umbc.edu

//Contains function definitions for all the member functions of the MyPokemon class 


#include "MyPokemon.h"

//Name: MyPokemon
//Constructor for the MyPokemon class
MyPokemon::MyPokemon(int num, string name, int cp, int hp, int rarity)
{
  m_Num = num;
  SetName(name);
  SetCP(cp);
  SetHP(hp);
  SetRarity(rarity);
}

//GetNum
//returns num
int MyPokemon::GetNum()
{
  return m_Num;
}

string MyPokemon::GetName()
{
  return m_Name;
}

int MyPokemon::GetCP()
{
  return m_CP;
}

int MyPokemon::GetHP()
{
  return m_HP;
}

int MyPokemon::GetRarity()
{
  return m_Rarity;
}
//SetName
//Sets a pokemon's name to whatever name we provide
void MyPokemon::SetName(string newName)
{
  m_Name = newName;
}

void MyPokemon::SetCP(int newCP)
{
  m_CP = newCP;
}

void MyPokemon::SetHP(int newHP)
{
  m_HP = newHP;
}

void MyPokemon::SetRarity(int newRarity)
{
  m_Rarity = newRarity;
}
//Train
//adds 10 the a pokemon's CP
void MyPokemon::Train()
{
  m_CP += 10;
}
