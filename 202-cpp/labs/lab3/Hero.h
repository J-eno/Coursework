// File: hero.h
//
// Modified class definition from Lab 3.
// Added #ifndef ...  macros, default constructor, 
// GetName accessor.

#ifndef HERO_H
#define HERO_H

#include <string>

using namespace std;

class Hero {
 public:
  // Default constructor--used to initialize all new Dogs.
  // we'll learn about these later!
  Hero();

  // Returns the type of hero
  string GetType();

  // Sets the type of hero
  void SetType(const string &type);

  // Returns the name of the hero
  string GetName();

  // Gives the hero a new name
  void SetName(const string &name);

  // Returns year the hero was born
  int GetBirthYear();

  // Gives the hero a new birth year
  void SetBirthYear(int birthYear);

  // Summon the hero
  void SummonHero();

  // Reward the hero
  void RewardHero();

  // Returns the age of the hero at a given year
  int GetAge(int current_year);

  // See how strong the hero is
  string GetStrength();

  // Prompt the hero to talk to you
  void SpeakHero();

 private:
  string m_name;// Name of hero
  int m_birthYear;// Year hero was born
  string m_type;// Type of hero
  int m_strength;// Strength of hero

};

#endif 
