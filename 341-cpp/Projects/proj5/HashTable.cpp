// File: HashTable.h
//
// CMSC 341 Spring 2017 Project 5
//
// Class declarations for Incremental Rehashing HastTable
//


#include "HashTable.h"
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
using namespace std;

char * const HashTable::DELETED = (char *)1;

//Constructor
HashTable::HashTable(int n)
{
  //if we try to make a table smaller than size 101, set table size to 101
  if(n < MIN_TABLE_SIZE)
    n = 101;
  //if we try to make a table bigger than our max size, throw exception
  else if(n > MAX_TABLE_SIZE)
    throw out_of_range("Cannot make Table of that size");
  //else if number isn't a prime, set equal to next biggest prime
  else if(!isPrime(n))
    {
      n = toPrime(primes, numPrimes, n);
    }

    m_tableSize = n;
    m_currSize = 0;
    m_array = new char*[m_tableSize];
    //init array data to NULL;
    for(int i = 0; i < m_tableSize; i++)
      {
	m_array[i] = NULL;
      }
    m_isRehashing = false;
    m_isMigrating = false;
    m_isRemoving = false;
    m_giveUp = false;
    m_wrapUp = false;
    m_second = NULL;
    m_third = NULL;
}

HashTable::~HashTable()
{
  if(m_array)
    {
      for(int i = 0; i < m_tableSize; i++)
	{
	  //deallocate array
	  if(m_array[i] != NULL && m_array[i] != DELETED)
	    {
	      free(m_array[i]);
	      m_array[i] = NULL;
	    }
	  else
	    m_array[i] = NULL;
	}
      //delete array
      delete [] m_array;
      m_array = NULL;
    }
  if(isRehashing())
    {
      //if rehashing, delete the old table too
      delete m_second;
      m_second = NULL;
    }
}

HashTable::HashTable(HashTable &other)
{
  if(!other.isRehashing())
    {
      //initialize our variables = to other's variables
      m_currSize = other.m_currSize;
      m_tableSize = other.m_tableSize;
      //create new array
      m_array = new char*[m_tableSize];
    
      //copy data from other into this table
      for(int i = 0; i < m_tableSize; i++)
	{
	  if(other.m_array[i] != NULL && other.m_array[i] != DELETED)
            {
	      char* myString = strdup(other.m_array[i]);
	      m_array[i] = myString;
	    }
	  else
	    m_array[i] = NULL;
	}

      //Initialize all the booleans
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      //initialize our second and third HashTables to NULL
      m_second = NULL;
      m_third = NULL;
    }
  else if(other.isRehashing())
    {
      //if our other table is rehashing, force it to wrap up
      other.wrapUp();
      //set this's variables to other's variables
      m_currSize = other.m_currSize;
      m_tableSize = other.m_tableSize;
      m_array = new char*[m_tableSize];

      //copy strings over
      for(int i = 0; i < m_tableSize; i++)
        {
	  if(other.m_array[i] != NULL && other.m_array[i] != DELETED)
            {
	      char* myString = strdup(other.m_array[i]);
	      m_array[i] = myString;
	    }
	  else
	    {
	      m_array[i] = NULL;
	    }
        }
      //initialize all the bools
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      //initialize second and third table to NULL
      m_second = NULL;
      m_third = NULL;


      m_second = NULL;
      m_third = NULL;
    }
}

const HashTable& HashTable::operator=(HashTable &rhs)
{
  //if this table is rehashing, delete it's second table
  if(isRehashing())
    {
      delete m_second;
      m_second = NULL;
    }
  //if there's an array existing
  if(m_array != NULL)
    {
      //delete contents and set to NULL;
      for(int i = 0; i < m_tableSize; i++)
        {
          if(m_array[i] == NULL || m_array[i] == DELETED)
            {
              m_array[i] = NULL;
            }
	  else
	    {
	      free(m_array[i]);
	      m_array[i] = NULL;
	    }
        }
      //deallocate the array and set to NULL;
      delete [] m_array;
      m_array = NULL;
    }


  if(!rhs.isRehashing())
    {
      //initialize this's variables to rhs' variables
      m_currSize = rhs.m_currSize;
      m_tableSize = rhs.m_tableSize;
      m_array = new char*[m_tableSize];
      
     
      //copy rhs' array
      for(int i = 0; i < m_tableSize; i++)
        {
	  if(rhs.m_array[i] == NULL || rhs.m_array[i] == DELETED)
	    {
	      m_array[i] = NULL;
	    }
	  else
            {
	      char* myString = strdup(rhs.m_array[i]);
	      m_array[i] = myString;
	    }
        }

      //initialize all our booleans
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      //initialize second and third table to NULL;
      m_second = NULL;
      m_third = NULL;


      m_second = NULL;
      m_third = NULL;
    }
  else if(rhs.isRehashing())
    {
      //if rhs is rehashing, force it to wrap up
      rhs.wrapUp();

      m_currSize = rhs.m_currSize;
      m_tableSize = rhs.m_tableSize;
      m_array = new char*[m_tableSize];

      //copy rhs' array
      for(int i = 0; i < m_tableSize; i++)
        {
	  if(rhs.m_array[i] != NULL && rhs.m_array[i] != DELETED)
            {
	      char* myString = strdup(rhs.m_array[i]);
	      m_array[i] = myString;
	    }
	  else
	    {
	      m_array[i] = NULL;
	    }
        }

      //initialize bools
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;

      m_second = NULL;
      m_third = NULL;
    }

}

//Public Insert Function - Makes copy of string
void HashTable::insert(const char *str)
{
  char *myString = strdup(str);//make copy of str
  insertOther(myString); //pass it to our other insert function

}

//Private Insert Function - Does not make a copy
void HashTable::insertOther(char *str)
{
  int firstIndex = getIndex(str); //get the index that the string hashes to
  m_currSize++; // add one to curr size
  
  //if we are in rehash mode
  if(isRehashing())
    {
      //also get the index that it hashes to in the second table
      int secondIndex = m_second->getIndex(str);
      //check if the table falls below min load factor
      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp(); //force to wrap up
	}

      //if we find our string in either table while rehashing
      if(findOther(firstIndex, str, m_array) || 
	 findOther(secondIndex, str, m_second->m_array))
	{
	  //decrement currentsize because we're not inserting anything
	  m_currSize--;
	}
      //if we don't find it in either table
      else if (!findOther(firstIndex, str, m_array) && 
	       !findOther(secondIndex, str, m_second->m_array))
	{
	  //since we're rehashing, we insert it in our second table
	  m_second->m_array[secondIndex] = str;
	  m_second->m_currSize++;
	  m_currSize--;//decrement because we didn't insert into this table
	  
	}
      
      if(!isMigrating())
        {
	  //after inserting, check if table is too empty
          if(tooEmpty(m_currSize, m_tableSize))
            wrapUp();//if too empty, wrap up the rehashing
	  if(tooFull(m_second->m_currSize, m_second->m_tableSize) || 
	     m_giveUp == true)//if our second table is too full
	    giveUp();//give up on incremental rehashing
        }

    }
  //not rehashing
  else
    {
      //if we find the string in our table
      if (findOther(firstIndex, str, m_array))
	{
	  //undo the increment we did at the start of the function
	  m_currSize--;
	}
      else//insert into the array
	{
	  m_array[firstIndex] = str;
	  if(isRehashing())//if start rehashing in the middle of this insert
	    migrateData(firstIndex);//move this string to new table
	}
      if(tooFull(m_currSize, m_tableSize))
	{
	  //if table becomes too full after this insert, start rehashing
	  rehash();
	}
    }
}


//InsertIn function I had to make because I'm bad at programming
void HashTable::insertIn(char *str)
{
  int index = getIndex(str);
  //if we find our string
  if (findOther(index, str, m_array))
    {
      //do nothing
    }
  else
    {
      //insert string
      m_array[index] = str;
    }

}


//public find function - returns whether string was found
bool HashTable::find(const char *str)
{
  //get the index that our string hashes to
  int firstIndex = getIndex(str);
  
  //if we are rehashing
  if(isRehashing())
    {
      //also get the index our string hashes to in the second table
      int secondIndex = m_second->getIndex(str);
      //check if we need to wrap up rehashing
      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp();
	}
      
      //if we find our string in either table
      if (findOther(firstIndex, str, m_array) || 
	  findOther(secondIndex, str, m_second->m_array))
	{
	  if(!isMigrating())
	    {
	      if(tooEmpty(m_currSize, m_tableSize))
		wrapUp();
	      
	    }
	  //return true
	  return true;
	}
      else 
	{
	  if(!isMigrating())
            {
              if(tooEmpty(m_currSize, m_tableSize))
                wrapUp();
	    }
	  //else return false
	  return false;
	}
    }    

  //not rehashing
  else
    {  
      //if we find it in this table
      if (findOther(firstIndex, str, m_array))
	{
	  return true;
	}
      else return false;
    }
}

//Private find function - returns a bool, but changes index
bool HashTable::findOther(int &index, const char *str, char ** arr)
{
  //if we have and array
  if(arr)
    {
      //and the array at our index is empty
      if (arr[index] == NULL)
	{
	  //not found
	  return false;
	}
      //if there was something there or the thing at our index isn't our string
      else if (arr[index] == DELETED || strcmp(arr[index], str) != 0)
	{
	  //linear probe to look for it
	  if (findProbe(index, str, arr))
	    {
	      return true;
	    }
	  else
	    return false;
	}
      //if the string at our index is our string
      else if (strcmp(arr[index], str) == 0)
	{
	  //we found it
	  return true;
	}
    }
}

//Remove function
char * HashTable::remove(const char *str)
{
  m_isRemoving = true;

  int firstIndex = getIndex(str);
  //string we will be returning
  char *theString = NULL;
  
  if(isRehashing())
    {
      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp();
	}
      
      int secondIndex = m_second->getIndex(str);
      
      //if we find the string in both tables somehow
      if (findOther(firstIndex, str, m_array) && 
	  findOther(secondIndex, str, m_second->m_array))
	{
	  char *theString = m_array[firstIndex];
	  //set their spots to DELETED
	  m_array[firstIndex] = DELETED;
	  m_second->m_array[secondIndex] = DELETED;
	  //decrement their current sizes
	  m_currSize--;
	  m_second->m_currSize--;

	  m_isRemoving = false;
	  //if the string we want to return end up being DELETED
	  if(theString == DELETED)
	    return NULL;
	  //else return our string
	  return theString;
	}
      //if string is found in the first table and not the second
      else if (findOther(firstIndex, str, m_array) && 
	       !findOther(secondIndex, str, m_second->m_array))
	{
	  char *theString = m_array[firstIndex];
	  //remove from first table
	  m_array[firstIndex] = DELETED;
	  m_currSize--;
	  m_isRemoving = false;
	  if(theString == DELETED)
	    return NULL;
	  
	  return theString;
	}
      //if found in the second table
      else if (!findOther(firstIndex, str, m_array) &&
	       findOther(secondIndex, str, m_second->m_array))
	{
	  char *theString = m_second->m_array[secondIndex];
	  //remove from second table
	  m_second->m_array[secondIndex] = DELETED;
	  m_second->m_currSize--;
	  m_isRemoving = false;
	  if(theString == DELETED)
	    return NULL;
	  
	  return theString;
	}
      //else if not found at all
      else 
	{
	  m_isRemoving = false;
	  return NULL;
	}
    }
  else //if not rehashing
    {
      //if we find str
      if (findOther(firstIndex, str, m_array))
	{
	  char *theString = m_array[firstIndex];
	  //remove string
	  m_array[firstIndex] = DELETED;
	  m_currSize--;
	  m_isRemoving = false;
	  if(theString == DELETED)
	    return NULL;
	  return theString;
	}
      else
	{
	  m_isRemoving = false;
	  return NULL;
	}
    }
}

//isRehashing()
bool HashTable::isRehashing()
{
  //return whether we're rehashing or not
  return m_isRehashing;
}

//rehash()
void HashTable::rehash()
{
  //set rehashing to true
  m_isRehashing = true;
  //allocate memory for the second table
  m_second = new HashTable(m_currSize * 4);
  //initialize contents to NULL
  for(int i = 0; i < m_second->m_tableSize; i++)
    {
      m_second->m_array[i] = NULL;
    }
  
}

//getIndex() - returns the index of any given string
unsigned int HashTable::getIndex(const char *str)
{
  //result from running string through hashCode() % tableSize
  unsigned int index = hashCode(str) % m_tableSize;
  return index;
}

//dump() - prints the  Tables
void HashTable::dump()
{
  cout << "HashTable #1: size = " << m_currSize 
       << ", tableSize = " << m_tableSize << endl;

  for(int i = 0; i < m_tableSize; i++)
    {
      cout << "H1[ " << i << "] = ";
      if(m_array)
	{
	  if(m_array[i] != NULL && m_array[i] != DELETED)
	    cout << m_array[i] << " (" << getIndex(m_array[i]) <<")";
	}
      cout << endl;
    }
  cout << endl;
  //if rehashing, also print out table 2's contents
  if(isRehashing())
    {
      cout << "HashTable #2: size = " << m_second->m_currSize 
	       << ", tableSize = " << m_second->m_tableSize << endl;
      for(int i = 0; i < m_second->m_tableSize; i++)
	{
	  cout << "H2[ " << i << "] = ";
	  if(m_second)
	    {
	      if(m_second->m_array[i] != NULL && 
		 m_second->m_array[i] != DELETED)
		
		cout << m_second->m_array[i] << " (" 
		     << m_second->getIndex(m_second->m_array[i]) <<")";
	    }
	  cout << endl;
	}
    }
  
}

//findProbe() - linear probes and returns a bool while altering the index given
bool HashTable::findProbe(int &index, const char *str, char ** arr)
{
  int possibleIndex = -1;
  //starts the start and end of cluster at the index we're given
  int clusterStart = index, clusterEnd = index;
  int probeCount = 1; //we've encountered one spot so far
  bool found = false, stop = false;
  
  //if the array we're probing in is our first array
  if (arr == m_array)
    {
      //if clusterEnd is greater than or equal to the size of our table
      if (clusterEnd >= m_tableSize)
	{
	  //subtract tablesize from the number(to wrap it back to the top)
	  clusterStart -= m_tableSize;
	  clusterEnd -= m_tableSize;
	}
    }
  else //we're probing in our second table
    {
      if (clusterEnd >= m_second->m_tableSize)
	{
	  clusterStart -= m_second->m_tableSize;
	  clusterEnd -= m_second->m_tableSize;
	}
    }
  //while we haven't reached an empty spot
  while (arr[clusterEnd] != NULL)
    {
      probeCount++;
      //if there's something at this spot and it is our string
      if ((arr[clusterEnd] != NULL && arr[clusterEnd] != DELETED) &&
	  strcmp(str, arr[clusterEnd]) == 0)
	{
	  //the index we found it at = current end of the cluster
	  index = clusterEnd;
	  found = true; // we found it
	  stop = true; 
	}
      //if we hit a spot for the first time that has been deleted
      else if (arr[clusterEnd] == DELETED && possibleIndex == -1)
	{
	  //this is the place we could insert to
	  possibleIndex = clusterEnd;
	}
      clusterEnd++;
      
      //check if we need to wrap after incrementing the end of the cluster
      if (arr == m_array)
	{
	  if (clusterEnd >= m_tableSize)
	    {
	      clusterEnd -= m_tableSize;
	    }
	}
      else
	{
	  if (clusterEnd >= m_second->m_tableSize)
	    {
	      clusterStart -= m_second->m_tableSize;
	      clusterEnd -= m_second->m_tableSize;
	    }
	}
    }
  
  //if we encounter a long probe sequence and we're not rehashing
  if (probeCount >= 10 && !isRehashing())
    rehash();//start rehashing
  
  //if a second table exists
  if(m_second)
    {
      //if we're probing the second table and hit a long prob
      if(arr == m_second->m_array && probeCount >= 10)
	m_giveUp = true; //it's time to give up on incremental rehashing
    }
  //if we're rehashing while probing we want to find the start of the cluster
  if(isRehashing())
    {
      while (arr[clusterStart - 1] != NULL)
	{
	  //while there's something before the current start of the cluster
	  clusterStart--;
	  probeCount++;
	  //check if we need to wrap to the end of cluster
	  if (arr == m_array)
	    {
	      if (clusterStart < 0)
		clusterStart += m_tableSize;
	    }
	  else
	    {
	      if (clusterStart < 0)
		clusterStart += m_second->m_tableSize;
	    }
	}

      // if our array exists
      if(m_array)
	{
	  //if we're not migrating data/wrapping up and 
	  //we're in the first table
	  if (!isMigrating() && arr == m_array && !m_wrapUp)
	    {
	      //move this cluster
	      migrateData(clusterStart, probeCount);
	    }
	}
    }
  //if we have a possible index we could insert to
  // and this probe sequence isn't being called by remove
  if(possibleIndex != -1 && m_isRemoving == false)
    {
      
      index = possibleIndex;
    }
  else if(stop == false)
    {
      index = clusterEnd;
    }
  //return if we found str or not
  return found;
}

//wrapUp() - wraps up incremental rehashing
void HashTable::wrapUp()
{
  m_wrapUp = true;
  char *myString;
  //loop through table 1
  for(int i = 0; i < m_tableSize; i++)
    {
      //if we encounter a string
      if(m_array[i] != DELETED && m_array[i] != NULL)
	{
	  //copy it
	  myString = strdup(m_array[i]);
	  //free it in table 1
	  free(m_array[i]);
	  //insert it into the second table
	  m_second->insertIn(myString);
	  m_second->m_currSize++;
	}
    }
  // deallocate table 1 array
  delete [] m_array;
  //make it point to m_second's array
  m_array = m_second->m_array;
  m_currSize = m_second->m_currSize;
  m_tableSize = m_second->m_tableSize;
  m_second->m_array = NULL; // point m_second's array at NULL;
  delete m_second; //delete table 2
  m_second = NULL;
  m_wrapUp = false;
  m_isRehashing = false;
}

//giveUp() - gives up on incremental rehash and puts everything in 3rd table
void HashTable::giveUp()
{
  char *myString;

  //create m_third table
  m_third = new HashTable((m_currSize + m_second->m_currSize) * 4);
  for(int i = 0; i < m_third->m_tableSize; i++)
    {
      m_third->m_array[i] = NULL;
    }

  //copy first table into third table
  for(int i = 0; i < m_tableSize; i++)
    {
      if(m_array[i] != DELETED && m_array[i] != NULL)
        {
          myString = strdup(m_array[i]);
          free(m_array[i]);
          m_third->insertIn(myString);
	  m_third->m_currSize++;
        }
    }

  //copy second table into third table
  for(int i = 0; i < m_second->m_tableSize; i++)
    {
      if(m_second->m_array[i] != DELETED && m_second->m_array[i] != NULL)
        {
          myString = strdup(m_second->m_array[i]);
          free(m_second->m_array[i]);
          m_third->insertIn(myString);
	  m_third->m_currSize++;
        }
    }

  //deallocate first table array and point it to third tables array
  delete [] m_array;
  m_array = m_third->m_array;
  m_currSize = m_third->m_currSize;
  m_tableSize = m_third->m_tableSize;
  // deallocate second and third tables
  m_second->m_array = NULL;
  m_third->m_array = NULL;
  delete m_second;
  delete m_third;
  m_second = NULL;
  m_third = NULL;

  m_isRehashing = false;
  m_giveUp = false;
}

//tooFull() checks if load factor exceeds 50%
bool HashTable::tooFull(int currSize, int tableSize)
{
  float loadFactor = (float)currSize/(float)tableSize;
  if(loadFactor > 0.5)
    return true;
  else
    return false;
}

//tooEmpty() checks if load factor falls under 3%
bool HashTable::tooEmpty( int currSize, int tableSize)
{
  float loadFactor = (float)currSize/(float)tableSize;
  if(loadFactor < 0.03)
    return true;
  else
    return false;
}

//isMigrating() checks if m_isMigarting
bool HashTable::isMigrating()
{
  return m_isMigrating;
}

//migrateData() moves clusters
void HashTable::migrateData(int from, int count)
{
  m_isMigrating = true;
  int start = from;
  int counter = count;

  // if there's something at the current index
  if(m_array[start] != NULL && m_array[start] != DELETED)
    {
      while(counter > 0)
	{
	  if(counter == 1)
	    {break;}

	  char *str = m_array[start];
       
	  if(str == DELETED)
	    {
	      //Do nothing
	    }
	  else
	    {
	      //remove the string
	      remove(str);
	      //insert the string
	      insertOther(str);
	    }
	  start++;
	  //wrap to beginning if needed
	  if(start >= m_tableSize)
	    start -= m_tableSize;
	  
	  counter--;
	  
	}
    }
  m_isMigrating = false;
}

//isPrime() checks if a number is a prime number
bool HashTable::isPrime(int num) 
{
	if (num < 2) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;
	for (int i = 3; (i*i) <= num; i += 2) {
		if (num % i == 0) return false;
	}
	return true;
}

//bSearch() performs a binary search on an array
int HashTable::toPrime(const int arr[], const int arrSize, int val)
{
  int mid, num = 0, min = 0, max = arrSize - 1;
  while(min <= max)
    {
      mid=(min + max)/2;
      if(val > arr[mid])
	min = mid + 1;
      else if(val < arr[mid])
	{
	  num = arr[mid];
	  max = mid-1;
	}
    }
  return num;
}

//tableSize() returns the capacity of a table
int HashTable::tableSize(int table)
{
  //if we're rehashing
  if(isRehashing())
    {
      if(table == 0)
	return m_tableSize;
      else
	return m_second->m_tableSize;
    }
  else return m_tableSize;
  
}

//size returns the current size of a table
int HashTable::size(int table)
{
  //same as above ^^ pretty straight forward
  if(isRehashing())
    {
      if(table == 0)
	return m_currSize;
      else
	return m_second->m_currSize;
    }
  else return m_currSize;
  
}

//at() returns the string at a given index
//*************NOTE: I didn't check to see if there was a string at the index
//*******************because it wasn't specified
const char * HashTable::at(int index, int table)
{
  char * stringAt;
  
  if(table == 0)
    {
      //if given an invalid index, throw out of range
      if(index < 0 || index >= m_tableSize)
	throw out_of_range("Invalid index");
      //else get the str at that index
      else
	{
	  stringAt = m_array[index];
	}
    }
  else
    {
      if(index < 0 || index >= m_second->m_tableSize)
	throw out_of_range("Invalid index");
      else
	{
	  stringAt = m_second->m_array[index];
	}
      
    }
  return stringAt;
}


