// comments

#include "Pyronite.h"
#include "Monster.h"
#include <stdlib.h>

//Name: Attack
//Precondition: Requires target
//Postcondition: Does calculated damage to the target based on table in project doc

void Pyronite::Attack(Monster *&target)
{
  cout << "Pyronite attacks with his " << m_nameNormal << " attack!" << endl;
  int miss = rand() % 100 + 1;
  if(miss <= m_missPercent)
    {
      cout << "Pyronite's Attack Missed!" << endl << endl;
    }
  else
    {
      int damage = rand() % m_maxDamageNormal + m_minDamageNormal;
      int targetLife = target->GetLife();
      targetLife -= damage;
      target->SetLife(targetLife);
      cout << "Pyronite did " << damage << " to " << target->GetName() << endl << endl;
    }

}


  //Name: Special Attack
  //Precondition: Needs a target (Finite number of special attacks by form)
  //Postcondition: Reduces life of target with output

void Pyronite::SpecialAttack(Monster *&target)
  {
    cout << "Pyronite attacks with his " << m_nameSpecial << " attack!" << endl;
    if(m_usedSpecial < m_maxSpecial)
      {
	int targetLife = target->GetLife();
	targetLife -= m_damageSpecial;
	target->SetLife(targetLife);
	cout << "Pyronite did " << m_damageSpecial  << " to " << target->GetName() << endl << endl;
	m_usedSpecial++;
      }
    else
      {
	cout << "Pyronite is out of special attacks! "
	     << target->GetName() << " retailiates!" << endl << endl;
      }
  }
