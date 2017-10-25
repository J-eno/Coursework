#ifndef ANIMALS_H
#define ANIMALS_H

#include <iostream>
#include <string>
using namespace std;

class Animals{

 public:
  Animals(string name);
  virtual void Eat();
  virtual void Speak();
  virtual void Pounce();
  virtual void Fly();

 protected:
  string m_name;

};

class Bird : public Animals {
 public:
  Bird(string name);
  void Eat();
  void Speak();
  void Fly();
};

class Cat : public Animals {
 public:
  Cat(string name);
  void Eat();
  void Speak();
  void Pounce();

};

#endif
