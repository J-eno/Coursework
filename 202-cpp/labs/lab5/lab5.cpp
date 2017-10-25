#include "Point23.h"
#include <iostream>

using namespace std;

int main()
{
  // declaring points as variables (statically):   
  Point23 p1; // default: 2D point with coordinates 0, 0
  Point23 p2(3, 4, 5);   // 3D point with coordinates 3, 4, 5

  // testing p1, p2:
  cout << "point p1: " << endl;
  cout << "x = " << p1.get_x() << " y = " << p1.get_y() << endl;
   
  cout << "point p2: " << endl;
  cout << "x = " << p2.get_x() << " y = " << p2.get_y() << " z = " <<
  p2.get_z() << endl;
   
  // As an example of allocating memory for an instance of a
  // class, we declare a point dynamically:
  Point23 *Ptr1;  // declaring a pointer to a point
  Ptr1 = new Point23(7,8);// allocating memory, initializing the point 
  // to a 2D point with coordinates 7, 8.

  // testing the dynamically allocated point:
  cout << "point pointed to by Ptr1 " << endl;
  cout << "x = " << Ptr1->get_x() << " y = " << Ptr1->get_y() << endl;

  // Exercise 3: deleting the dynamically allocated point:
  // YOUR CODE GOES HERE
  delete Ptr1;

  // Note: there is no need to delete p1, p2, since these are local
  // variables which are deleted automatically when the program finishes.
  // Deleting p1, p2 would be an error, since they have not been allocated
  // by "new".
  
  return 0;
}
