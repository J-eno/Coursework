#include "Point23.h"

// default class constructor creates a 2-dimensional point with
// coordinates x = 0, y = 0.
Point23::Point23()
{
  m_size = 2;

  // Exercise 1: allocate memory for an array of two integers
  m_dataPtr = new int[2];

  // Exercise 1: initialize the coordinates to 0s:
  m_dataPtr[0] = 0;
  m_dataPtr[1] = 0;
}

// class constructor creates a 2-dimensional point with
// coordinates xval, yval.

Point23::Point23(int xval, int yval)
{
  m_size = 2;

  // Exercise 1: allocate memory for an array of two integers
  m_dataPtr = new int[2];

  // Exercise 1: initialize the coordinates:
  m_dataPtr[0] = xval;
  m_dataPtr[1] = yval;

}

// class constructor creates a 3-dimensional point with
// coordinates xval, yval, and zval

Point23::Point23(int xval, int yval, int zval)
{
  m_size = 3;

  // Exercise 1: allocate memory for an array of three integers
  m_dataPtr = new int[3];  
  // Exercise 1: initialize the coordinates:
  m_dataPtr[0] = xval;
  m_dataPtr[1] = yval;
  m_dataPtr[2] = zval;

} 

// class destructor deallocates all memory allocated for an object of the 
// class
Point23::~Point23()
{
  // Exercise 2: deallocate memory for the array of coordinates
  // Exercise 2: set the pointer to NULL or 0
  delete [] m_dataPtr;
  m_dataPtr = NULL;
  cout << "Pointer Deleted" << endl;

}

int Point23::get_x() const
{
  // every point has an x coordinate
  return m_dataPtr[0];
}

int Point23::get_y() const
{
  // every point has a y coordinate
  return m_dataPtr[1];
} 

int Point23::get_z() const
{
  // check if the point has a z coordinate:
  if (m_size == 3)
    return m_dataPtr[2];
  else {
    cerr << "attempt to return a third coordinate of a 2D point" <<
      endl;
    exit(1);
  }
}
