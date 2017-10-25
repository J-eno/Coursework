// File: lab3.cpp
	//
	// Demonstrates use of the Hero class.
	// Compile together with Hero.cpp
	//

#include <iostream>
#include "Hero.h"

using namespace std;

int main() {
  // Instantiate "Hero" class twice
  // Create "hero1" object and "hero2" object
  Hero hero1;
  Hero hero2;

  //Part 1: Using getters to access private data members for hero1
  cout << "Hero1's original data:\n";
  cout << "\tName is: " << hero1.GetName() << endl;
  cout << "\tAge in 2016 is: " << hero1.GetAge(2016) << endl;
  cout << "\tType is: " << hero1.GetType() << endl;
  cout << "\tStrength is: " << hero1.GetStrength() << endl;

  // MODIFY hero1 AND hero2, BY USING THE Hero CLASS METHODS,
  // TO SET THE "type" FIELD TO SOMETHING NEW, GET THE FIELDS
  // BACK OUT AND PRINT

  //Part 2: Using setters to update private data members for hero1 and hero2
  cout << "Your hero1 has earned a super ability." << endl;
  hero1.SetType("Super"); // set new type for hero1 to Super.
  cout << "Hero1's new type is: " << hero1.GetType() << endl;
  cout << "Your hero2 has earned an evil ability." << endl;
  hero2.SetType("Evil"); // Set new type for hero2 to Evil.
  cout << "Hero2's new type is: " << hero2.GetType() << endl << endl;

  // INTERACT WITH YOUR HERO TO AFFECT STRENGTH RATING
  // BY USING THE SummonHero() AND RewardHero() METHODS

  //Part 3: Calling methods on a specific object that modify data members
  cout << "Call and reward your hero several times:" << endl;

  // Fetch current Strength value and display it
  cout << "Hero1 starts out " << hero1.GetStrength() << endl;

  // Now, summon your hero1 once, then reward hero1 twice.
  // Printing out the strength level after each change:

  hero1.SummonHero();  // Summon hero1 - Reduces hero strength
  cout << "You summoned the hero. Hero1's strength is now " 
       << hero1.GetStrength() << endl;
  hero1.RewardHero();  // Reward hero1 - Increases hero strength
  cout << "You rewarded the hero. Hero1's strength is now " 
       << hero1.GetStrength() << endl;
  hero1.RewardHero();  // Reward hero1 - Increases hero strength
  cout << "You rewarded the hero. Hero1's strength is now " 
       << hero1.GetStrength() << endl << endl;


  //Part 4: Calling a specific method of an object
  cout << "You speak to the hero:" << endl;
  hero1.SpeakHero();
 
  return 0;

}
