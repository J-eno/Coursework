#include <iostream>
using namespace std;

int main()
{
  int numCoffee = 10;
  int *ptrCoffee;
  ptrCoffee = &numCoffee;
  
  cout << "ptrCoffee = " << ptrCoffee << endl;
  cout << "*ptrCoffee = " << *ptrCoffee << endl;
  
  *ptrCoffee = 20;

  cout << "numCoffee = " << numCoffee << endl;
  cout << "ptrCoffee = " << *ptrCoffee << endl;


  return 0;
}
