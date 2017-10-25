// File: Hero.cpp
//
// Implementation of Hero class.
//

#include <iostream>
#include "Hero.h"

// ------------- Constructors ----------------------

// Default constructor--used to initialize all new Heros.
// we'll learn about these later!
//
Hero::Hero() 
{
  cout << "Creating a Hero...\n";
  m_type = "Normal";
  m_name = "The Sheriff";
  m_birthYear = 2015;
  m_strength = 10;  // Start out at 10
}


// ------------- Accessors -------------------------
//
// These do what you think.

string Hero::GetType() {
  return m_type;
}

void Hero::SetType(const string &type) {
  m_type = type;
}

string Hero::GetName() {
  return m_name;
}

void Hero::SetName(const string &name) {
  m_name = name;
}

int Hero::GetBirthYear() {
  return m_birthYear;
}

void Hero::SetBirthYear(int birthYear) {
  m_birthYear = birthYear;
}

void Hero::SummonHero() {
  m_strength--;
}

void Hero::RewardHero() {
  m_strength++;
}



// ------ Helper Methods --------------

int Hero::GetAge(int currentYear) {
  return currentYear - m_birthYear;
}

string Hero::GetStrength() {
  if(m_strength > 10) {
    return "strong!";
  }

  else if(m_strength < 10) {
    return "showing weakness.";
  }
    
  else {
    return "ok.";
  }
}
        
void Hero::SpeakHero() {
  cout << "Here I come to save you!" << endl;
}
