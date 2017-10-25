#include "Animals.h"
#include <iostream>
#include <string>
using namespace std;

int main () {

  Bird bird1("Tweety");
  Cat cat1("Tom");
  //Animals animal1("Generic Animal");

  Animals * tweety = &bird1;
  Animals * tom = &cat1;
  //Animals * animal = &animal1;

  cout << "Tweety Bird" << endl;
  tweety->Speak();
  tweety->Eat();
  tweety->Fly();

  cout << "Tom the Cat" << endl;
  tom->Speak();
  tom->Eat();
  tom->Pounce();

  //cout << "The Generic Animal" << endl;
  //animal->Eat();
  //animal->Speak();

  return 0;
}
