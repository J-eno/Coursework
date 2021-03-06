#include <iostream>
#include "IntArray.h"

using namespace std;

int main()
{
  // Create IntArray objects and call methods here...
  IntArray ia(10);
  IntArray neg(-5);
  IntArray zero(0,0);
  IntArray ia2(0,1);
  IntArray empty();

  bool equal = zero == ia;

  bool equal2 = (zero == ia2);

  bool dne = (zero != zero);

  ia += zero;

  IntArray newOne = zero + ia2;

  newOne[-1];
  ia.Get(-1);
  ia.Get(50);

  ia.SetItem(-5,30);
  ia.SetItem(30,5);

  zero.Insert(0,20);
  ia.Insert(-34, 22);
  ia.Insert(22,34);

  zero.Del(0);
  ia.Del(-12);
  ia.Del(50);

  ia.Remove(99);
  zero.Remove(0);
  zero.Clear();

  zero.Contains(5);
  zero.Contains(5,5);
  ia.Contains(5,-1);
  ia.Contains(5,98);
  
  // Print out the number of errors/edge cases found
  cout << endl << endl << IntArray::GetProgress() << endl;
    
  return 0;
}
