//lab11.cpp
#include <iostream>
#include <string>
using namespace std;

//Implement a templated class named swapMax that compares two items.
//It can accept an int, char, double, float, or string.
//The parameters are value1 and value2. If value1 is less than value2, they swap.
//HINT: Use pass-by-reference for the templated class.

//Class Definition here!
template <class T>
void swapMax(T& value1, T& value2)
{
  T temp;
  if(value1 < value2)
    {
      temp = value1;
      value1 = value2;
      value2 = temp;
    }
}

int main () {
  int a1 = 5;
  int b1 = 10;
  char a2 = 'A';
  char b2 = 'F';
  double a3 = 5.3;
  double b3 = 15.1;
  string a4 = "candy";
  string b4 = "pizza";
  swapMax(a1,b1);
  swapMax(a2,b2);
  swapMax(a3,b3);
  swapMax(a4,b4);
  cout << "a1=" << a1 << " b1=" << b1 << endl;
  cout << "a2=" << a2 << " b2=" << b2 << endl;
  cout << "a3=" << a3 << " b3=" << b3 << endl;
  cout << "a4=" << a4 << " b4=" << b4 << endl;
  return 0;
}
