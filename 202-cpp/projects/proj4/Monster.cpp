//comments

#include "Monster.h"

//Name: Monster (Constructor)
//Precondition: Must have the level of the game.
//Sets the name of the monster randomly from the monster.txt file.
//Sets the life and attack based on calculated values
//Postcondition: Loads a new monster with stats based on the level.
Monster::Monster(int level)
{
  int randHP = 0;
  int randATK = 0;
  LoadMonster();
  m_name = SummonMonster();

  if(level >= 3)
    {
      randHP = rand() % 30 + 40;
      randATK = rand() % 10 + 5;
    }
  else if(level == 2)
    {
      randHP = rand() % 31 + 30;
      randATK = rand() % 8 + 3;
    }
  else
    {
      randHP = rand() % 31 + 20;
      randATK = rand() % 6 + 1;
    }
  m_life = randHP;
  m_attack = randATK;

}

//Name: ~Monster
//Precondition: Something must be dynamically allocated
//Postcondition: None
Monster::~Monster()
{

}

//Name: SummonMonster
//Precondition: Need to have the m_monster vector populated by LoadMonster
//Postcondition: Returns the string value of a random monster from the vector
string Monster::SummonMonster()
{
  int randMonster = rand() % m_monster.size();
  return m_monster.at(randMonster);
}

//Name: LoadMonster
//Precondition: Must have the m_monster vector available and the monster.txt
//Postcondition: Populates the m_monster vector with the monster names in the file

void Monster::LoadMonster()
{
  fstream input;
  input.open("monster.txt");
  string lines;
  
  //while I can get a line, get line and push it into monster vector 
  while(getline(input, lines))
    {
      m_monster.push_back(lines);
    }
}

//Name: Attack
//Precondition: Must have a form of Ben to attack
//Postcondition: Reduces current version of Ben by calculated damage

void Monster::Attack(Ben *&target)
{
  cout << m_name << " attacks " << target->GetName() << " using a normal attack" 
       << endl;
  int benHP = target->GetLife();
  double defBonus = target->GetDefenseBonus();
  
  int damageBlocked = m_attack * defBonus;
  
  int newHP = benHP - (m_attack - damageBlocked);
  target->SetLife(newHP);

  cout << m_name << " did " << (m_attack - damageBlocked)
       << " to " << target->GetName() << endl << endl;
}

void Monster::SetLife(int life)
{
  m_life = life;
}

int Monster::GetLife()
{
  return m_life;
}

string Monster::GetName()
{
  return m_name;
}
