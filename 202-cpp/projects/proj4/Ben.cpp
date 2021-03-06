//Comments

#include "Ben.h"
#include "Monster.h"
#include <stdlib.h>

//Name: Ben (Constructor)
//Precondition: Need to have the name and the life (from table in project doc)
//Postcondition: Creates a default version of Ben (not transformed)

Ben::Ben(string name, int life)
{
  name = m_name;
  life = m_life;
}

//Name: Ben (Overloaded constructor)
//Precondition: Need to have all of the stats for an advanced form
//Data from table in project document
//Postcondition: Creates a specific version of Ben for use in transformed versions

Ben::Ben(string name, int life, string nameNorm, string nameSpecial, 
double defenseBonus, double missPercent, int usedSpecial, 
	 int maxSpecial, int minDamNorm, int maxDamNorm, int damSpec)
{
  m_name = name;
  m_life = life;
  m_nameNormal = nameNorm;
  m_nameSpecial = nameSpecial;
  m_defenseBonus = defenseBonus;
  m_missPercent = missPercent;
  m_usedSpecial = usedSpecial;
  m_maxSpecial = maxSpecial;
  m_minDamageNormal = minDamNorm;
  m_maxDamageNormal = maxDamNorm;
  m_damageSpecial = damSpec;
}

//Name: ~Ben
//Precondition: Dynamically allocated Ben (using new)
//Postcondition: Removes allocated Ben from memory

Ben::~Ben()
{

}

//Name: Attack
//Precondition: Need a target (May miss!)
//Postcondition: Reduces life of target with output

void Ben::Attack(Monster *&target)
{
  cout << "Ben attacks with his " << m_nameNormal << " attack!" << endl;
  //Generate a number between 1 and 100
  int miss = rand() % 100 + 1;
  //if number is less than miss% attack missed
  if(miss <= m_missPercent)
    {
      cout << "Ben's Attack Missed!" << endl << endl;
	}
  else
    {
      int damage = rand() % m_maxDamageNormal + m_minDamageNormal;
      int targetLife = target->GetLife();
      targetLife -= damage;
      target->SetLife(targetLife);
      cout << "Ben did " << damage << " to " << target->GetName() << endl << endl;
    }
}

//Name: Special Attack
//Precondition: Needs a target (Finite number of special attacks by form)
//Postcondition: Reduces life of target with output

void Ben::SpecialAttack(Monster *&target)
{
  cout << "Ben attacks with his " << m_nameSpecial<< " attack!" << endl;
  //if we still have specials left
  if(m_usedSpecial < m_maxSpecial)
    {
      int targetLife = target->GetLife();
      targetLife -= m_damageSpecial;
      target->SetLife(targetLife);
      cout << "Ben did " << m_damageSpecial  << " to " 
	   << target->GetName() << endl << endl;
      m_usedSpecial++;
    }
  else
    {
      cout << "Ben is out of special attacks! "
	   << target->GetName() << " retailiates!" << endl << endl;
    }
}

//Name: Ultimate Attack
//Precondition: Needs a target (only available with Crystalsapien)
//Postcondition: Reduces life of target with output

void Ben::UltimateAttack(Monster *&target)
{
  cout << m_name <<" has no ultimate attack! "
       << target->GetName() << " retaliates!" << endl << endl;
}

//Accessors and Mutators

void Ben::SetLife(int life)
{
  m_life = life;
}

string Ben::GetName()
{
  return m_name;
}


int Ben::GetLife()
{
  return m_life;
}


double Ben::GetDefenseBonus()
{
  return m_defenseBonus;
}
