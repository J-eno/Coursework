#include "Animals.h"
#include <iostream>
#include <string>
using namespace std;

Animals::Animals(string name){
  m_name = name;
}
void Animals::Eat(){
  cout << "I am an animal " << m_name << " who eats food." << endl;
}
void Animals::Speak(){
  cout << "I am an animal " << m_name << " who speaks." << endl;
}
void Animals::Pounce(){
  cout << "I am an animal " << m_name << " who pounces." << endl;
}
void Animals::Fly(){
  cout << "I am an animal " << m_name << " who flies." << endl;
  }

Bird::Bird(string name)
  : Animals(name)
{

}

void Bird::Eat(){
  cout << "I am a bird " << m_name << " who eats food." << endl;
}
void Bird::Speak(){
  cout << "I am a bird " << m_name << " who speaks." << endl;
}
void Bird::Fly(){
  cout << "I am a bird " << m_name << " who can fly!" << endl;
}

Cat::Cat(string name)
  : Animals(name)
{

}

void Cat::Eat(){
  cout << "I am a cat " << m_name << " who can eat." << endl;
}
void Cat::Speak(){
  cout << "I am a cat " << m_name << " who can speak." << endl;
}
void Cat::Pounce(){
  cout << "I am a cat " << m_name << " who can pounce." << endl;
}

