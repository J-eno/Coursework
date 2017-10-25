// File: MinMaxHeap.h
//
// CMSC 341 Spring 2017 Project 4
//
// Class declarations for Fake Min Max Heap


#ifndef MinMaxHeap_H
#define MinMaxHeap_H

#include <stdexcept>   // for throwing out_of_range exceptions
#include <iostream>
#include <utility>  //pairs

using namespace std;

template <typename T>
class Heap
{
public:
	//Heap constructor
	Heap(int capacity, bool(*f)(const T&, const T&) = NULL);

	//Heap Copy constructor
	Heap(const Heap<T>& other);

	//Heap assignment operator
	const Heap<T>& operator=(const Heap<T> &rhs);

	//Heap destructor
	~Heap();


	//insert and delete
	int insert(const T &data, int index);
	void deleteAt(int index);

	//bubble up and trickle down
	int bubbleUp(T data, int position);
	void trickleDown(T data, int position);

	//this stuff should be private but I don't have time to write accessors and mutators right now
	int m_capacity;
	bool(*m_compare)(const T&, const T&);
	pair<T, int> *m_array;
	int m_end;
	Heap<T>* m_other;
};

template <typename T>
class Heap;

template <typename T>
class MinMaxHeap
{
public:
  //constructor
  MinMaxHeap(int capacity);
  //copy constructor
  MinMaxHeap(const MinMaxHeap &other);
  //destructor 
 ~MinMaxHeap();
 //assignment operator
 const MinMaxHeap<T>& operator=(const MinMaxHeap<T> &rhs);

 //Size
 int size();

 void insert(const T& data);
 
 T deleteMin();

 T deleteMax();

 void locateMin(int pos, T& data, int& index);
 void locateMax(int pos, T& data, int& index);
 void dump();

private:
	int m_capacity;
	int m_size;
	Heap<T>* m_minHeap;
	Heap<T>* m_maxHeap;
};
//comparison operators
template <typename T>
bool lesserT(const T &a, const T &b);

template <typename T>
bool greaterT(const T &a, const T &b);

//*********************************************************************************************************************
//Implementation of Classes


//comparison operator< 
template <typename T>
bool lesserT(const T& a, const T& b)
{
	//if a is less than b return true
	return a < b ? true : false;
}

//comparison operator>
template <typename T>
bool greaterT(const T& a, const T& b)
{
	//if a is greater than b return true
	return a > b ? true : false;
}

//MinMaxHeap constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity)
{
	m_capacity = capacity;
	m_size = 0;
	
	//create pointers to our comparison functions
	bool(*lessThan)(const T&, const T&) = lesserT;
	bool(*greaterThan)(const T&, const T&) = greaterT;
	
	//create two heaps min/max
	m_minHeap = new Heap<T>(m_capacity, lessThan);
	m_maxHeap = new Heap<T>(m_capacity, greaterThan);
	
	//give each heap a pointer to the other
	m_minHeap->m_other = m_maxHeap;
	m_maxHeap->m_other = m_minHeap;
}

//MinMaxHeap overloaded operator=
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T> &rhs)
{
	
	if (&rhs == this) return *this;
	
	delete m_minHeap;
	delete m_maxHeap;
	
	m_capacity = rhs.m_capacity;
	m_size = rhs.m_size;
	
	
	//Re-initialize heaps into our rhs heaps
	m_minHeap = new Heap<T>(*rhs.m_minHeap);
	m_maxHeap = new Heap<T>(*rhs.m_maxHeap);

	//Point heaps at eachother again
	m_minHeap->m_other = m_maxHeap;
	m_maxHeap->m_other = m_minHeap;
}

//MinMaxHeap copy constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T> &rhs)
{
 
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;


  //Re-initialize heaps into our rhs heaps
  m_minHeap = new Heap<T>(*rhs.m_minHeap);
  m_maxHeap = new Heap<T>(*rhs.m_maxHeap);

  //Point heaps at eachother again
  m_minHeap->m_other = m_maxHeap;
  m_maxHeap->m_other = m_minHeap;

}

//MinMaxHeap destructor
template <typename T>
MinMaxHeap<T>::~MinMaxHeap()
{
	m_capacity = m_size = 0;
	
	delete m_minHeap;
	m_minHeap = NULL;
	delete m_maxHeap;
	m_maxHeap = NULL;
}

//Size Function
template <typename T>
int MinMaxHeap<T>::size()
{
	//return size of min heap
	return m_minHeap->m_end;
}

//MinMaxHeap Insert
template <typename T>
void MinMaxHeap<T>::insert(const T& data)
{
	m_size++;
	//insert into min heap with a default index for twin in max heap
	int minInd = m_minHeap->insert(data, m_size);
	//insert into max heap with the index of twin in min heap
	int maxInd = m_maxHeap->insert(data, minInd);
	//update min heap index
	m_minHeap->m_array[minInd].second = maxInd;
}

//MinMaxHeap deleteMin
template <typename T>
T MinMaxHeap<T>::deleteMin()
{
	if (m_size < 1)
		throw out_of_range("NO ITEMS IN HEAP");

	T data;
	//delete root of min heap
	m_minHeap->deleteAt(1);
	data = m_minHeap->m_array[0].first;
	//delete twin in max heap
	m_maxHeap->deleteAt(m_minHeap->m_array[0].second);

	m_size--;
	return data;
}

//MinMaxHeap deleteMax
template <typename T>
T MinMaxHeap<T>::deleteMax()
{
	if (m_size < 1)
		throw out_of_range("NO ITEMS IN HEAP");

	T data;
	//delete root of max heap
	m_maxHeap->deleteAt(1);
	data = m_maxHeap->m_array[0].first;
	//delete twin in min heap
	m_minHeap->deleteAt(m_maxHeap->m_array[0].second);

	m_size--;
	return data;
}


//MinMaxHeap Dump
template <typename T>
void MinMaxHeap<T>::dump()
{
	cout << endl << "... MinMaxHeap::dump() ..." << endl << endl;
	cout << "-----MinHeap-----" << endl;
	cout << "Size = " << m_size << ", Capacity = " << m_capacity << endl;

	for (int i = 1; i < m_size + 1; i++)
	{
		cout << "Heap[" << i << "] = (" << m_minHeap->m_array[i].first << "," << m_minHeap->m_array[i].second << ")" <<endl;
	}

	cout << "-----MaxHeap-----" << endl;
	cout << "Size = " << m_size << ", Capacity = " << m_capacity << endl;

	for (int i = 1; i < m_size + 1; i++)
	{
		cout << "Heap[" << i << "] = (" << m_maxHeap->m_array[i].first << "," << m_maxHeap->m_array[i].second << ")" << endl;
	}
}

//LocateMin
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index)
{
	data = m_minHeap->m_array[pos].first;
	index = m_minHeap->m_array[pos].second;
}

//LocateMax
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index)
{
	data = m_maxHeap->m_array[pos].first;
	index = m_maxHeap->m_array[pos].second;
}


//********************************HEAP IMPLEMENTATION**********************************

//Heap constructor
template <typename T>
Heap<T>::Heap(int capacity, bool(*f)(const T&, const T&))
{
	m_capacity = capacity + 1;
	//initialize array
	m_array = new pair<T, int>[m_capacity];
	m_end = 0;
	//set comparison function to the one we passed in
	m_compare = f;
	
}

//Heap Copy constructor
template <typename T>
Heap<T>::Heap(const Heap<T> &rhs)
{
  m_capacity = rhs.m_capacity;
  m_end = rhs.m_end;
  m_array = new pair<T, int>[m_capacity];

  T defObj;
  
  m_compare = rhs.m_compare;
  m_other = NULL ;

  for (int i = 0; i <= m_end; i++)
    {
		m_array[i] = rhs.m_array[i];
    }

	
}

//MinMaxHeap overloaded operator=
template <typename T>
const Heap<T>& Heap<T>::operator=(const Heap<T> &rhs)
{
	if (this == &rhs) return *this;

	delete[] m_array;
	m_array = NULL;

	m_capacity = rhs.m_capacity;
	m_end = rhs.m_capacity;
	m_array = new pair<T, int>[m_capacity];
	m_compare = rhs.m_compare;

	for (int i = 1; i < rhs.m_capacity + 1; i++)
	{
		m_array[i] = rhs.m_array[i];
	}
}

//Heap destructor
template <typename T>
Heap<T>::~Heap()
{
	m_other = NULL;

	m_compare = NULL;
	delete[] m_array;
	m_array = NULL;
}

//Heap insert
template <typename T>
int Heap<T>::insert(const T& data, int index)
{
	if (m_end >= m_capacity)
		throw out_of_range("Heap has reached capacity");
	//increment the last position
	m_end++;
	//insert data at the last position
	m_array[m_end] = make_pair(data, index);
	//try to bubble up the array
	int a = bubbleUp(data, m_end);
	return a;
}

//Heap deleteAt
template <typename T>
void Heap<T>::deleteAt(int index)
{
	//put the data we want to delete in our free space
	m_array[0] = m_array[index];
	
	//if we're deleting in the last spot 
	if (index == m_end)
	{
		//'Shorten' array
		m_end--;
	}
	else
	{
		//put the data in the last spot into the spot we're deleting
		m_array[index] = m_array[m_end];
		//tell our twin we moved
		m_other->m_array[m_array[index].second].second = index;
		m_end--;
	}
	//Heap Fixing
	//if we're not at the root && we're not at last spot
	if (index > 1 && index < m_end)
	{
		//try to bubble up and trickle down
		int garbageInt = bubbleUp(m_array[index].first, index);
		trickleDown(m_array[index].first, index);
	}
	//else if we're at the root and not at the last spot
	else if(index == 1 && index < m_end)
	{
		//just trickle down
		trickleDown(m_array[index].first, index);
	}
}

//Heap Bubble Up
template <typename T>
int Heap<T>::bubbleUp(T data, int position)
{
	//the space we want to move up
	int space = position;
	T temp;
	int temp2;
	//while we're not at the root && we're bigger/smaller than our parent
	for (; space > 1 && (*m_compare)(data, m_array[space / 2].first); space /= 2)
	{
		//store our data in temp
		temp = m_array[space].first;
		temp2 = m_array[space].second;
		//Replace our data with parent data
		m_array[space].first = m_array[space / 2].first;
		
		//update our twin telling them that we moved
		m_other->m_array[m_array[space / 2].second].second = space;
		m_other->m_array[m_array[space].second].second = space / 2;

		//Replace our twin's index with parent's twin index
		m_array[space].second = m_array[space / 2].second;
		
		//put our data and index where parent used to be
		m_array[space / 2].first = temp;
		m_array[space / 2].second = temp2;
	}

	return space;

}

//Heap Trickle Down
template <typename T>
void Heap<T>::trickleDown(T data, int position)
{
	int space = position;
	//child to switch with
	int child = space * 2;
	T temp;
	int temp2;
	//while child isn't greater than the end of our array
	for (; child <= m_end; space = child, child *= 2 )
	{
		//if right child is bigger/smaller than current child use right child
		if (child < m_end && (*m_compare)(m_array[child + 1].first, m_array[child].first))
		{
			child++;
		}
		//if child is greater/smaller than us
		if ((*m_compare)(m_array[child].first, m_array[space].first))
		{
			//stor our data in temp
			temp = m_array[space].first;
			temp2 = m_array[space].second;

			//Replace our data with child data
			m_array[space].first = m_array[child].first;

			//update our twin and childs twin telling them that we swapped
			m_other->m_array[m_array[child].second].second = space;
			m_other->m_array[m_array[space].second].second = child;
			
			//Replace our twin index with childs
			m_array[space].second = m_array[child].second;

			//Put our data where child's used to be
			m_array[child].first = temp;
			m_array[child].second = temp2;
		}
	}
}

#endif
