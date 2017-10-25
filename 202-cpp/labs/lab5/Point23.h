#include <iostream>
#include <cstdlib>

using namespace std;

// Class Point23 represents a point that may be two- or
// three-dimensional, depending on which constructor is used to create
// it. Coordinates are stored in a dynamically allocated array.

class Point23
{
 public:
  // default class constructor (with no arguments):
  Point23(); 

  // class constructor that creates a 2-dimensional point with
  // coordinates xval and yval:
  Point23(int xval, int yval);

  // class constructor that creates a 3-dimensional point with 
  // coordinates xval, yval, and zval:
  Point23(int xval, int yval, int zval);

  // class destructor:
  ~Point23();

  // member functions for getting values of x, y, and z (if it's present)
  int get_x() const;
  int get_y() const;
  int get_z() const;

  // private data members: size of the point and a pointer to the array of 
  // coordinates:
 private:
  int m_size;
  int *m_dataPtr;
};
