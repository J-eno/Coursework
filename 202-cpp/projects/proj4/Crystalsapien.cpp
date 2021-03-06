//comments

#include "Crystalsapien.h"
#include "Monster.h"
#include <stdlib.h>

//Name: Attack
//Precondition: Requires target
//Postcondition: Does calculated damage to the target based on table in project doc

void Crystalsapien::Attack(Monster *&target)
{
  cout << "Crystalsapien attacks using his " << m_nameNormal << " attack!" << endl;
  int miss = rand() % 100 + 1;
  if(miss <= m_missPercent)
    {
      cout << "Crystalsapien's Attack Missed!" << endl << endl;
    }
  else
    {
      int damage = rand() % m_maxDamageNormal + m_minDamageNormal;
      int targetLife = target->GetLife();
      targetLife -= damage;
      target->SetLife(targetLife);
      cout << "Crystalsapien did " << damage << " to " << target->GetName() << endl << endl;
    }
}


//Name: Special Attack
//Precondition: Requires target (finite uses)
//Postcondition: Does calculated damage to the target based on table in project doc

void Crystalsapien::SpecialAttack(Monster *&target)
{
  cout << "Crystalsapien attacks using his " << m_nameSpecial << " attack!" << endl; 
  if(m_usedSpecial < m_maxSpecial)
    {
      int targetLife = target->GetLife();
      targetLife -= m_damageSpecial;
      target->SetLife(targetLife);
      cout << "Crystalsapien did " << m_damageSpecial  << " to " << target->GetName() << endl << endl;
      m_usedSpecial++;
    }
  else
    {
      cout << "Crysstalsapien is out of special attacks! "
           << target->GetName() << " retailiates!" << endl << endl;
    }
}


//Name: Ultimate Attack
//Precondition: Requires target (unlimited  uses)
//Postcondition: Does calculated damage to the target (10x special attack damage)

void Crystalsapien::UltimateAttack( Monster *&target)
{
  cout << "Crystalsapien attacks using **ULTIMATE ENERGY LASER** ATTACK!!" << endl;
  int ultimateDamage = m_damageSpecial * 10;
  int targetLife = target->GetLife();
  targetLife -= ultimateDamage;
  target->SetLife(targetLife);
  cout << "Crystalsapien did " << ultimateDamage  << " to " << target->GetName() << endl << endl;

}
