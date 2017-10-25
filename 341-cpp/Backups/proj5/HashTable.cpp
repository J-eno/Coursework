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

    cout << "TABLE CREATED" << endl;
}

HashTable::~HashTable()
{
  if(m_array)
    {
      for(int i = 0; i < m_tableSize; i++)
	{
	  if(m_array[i] != NULL && m_array[i] != DELETED)
	    {
	      free(m_array[i]);
	      m_array[i] = NULL;
	    }
	}
      delete [] m_array;
      m_array = NULL;
    }
  if(isRehashing())
    {
      delete m_second;
      m_second = NULL;
    }
}

HashTable::HashTable(HashTable &other)
{
  if(!other.isRehashing())
    {
      m_currSize = other.m_currSize;
      m_tableSize = other.m_tableSize;
      m_array = new char*[m_tableSize];
    
      for(int i = 0; i < m_tableSize; i++)
	{
	  if(other.m_array[i] != NULL && other.m_array[i] != DELETED)
            {
	      char* myString = strdup(other.m_array[i]);
	      m_array[i] = myString;
	    }
	}

     
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      m_second = NULL;
      m_third = NULL;

      m_second = NULL;
      m_third = NULL;
    }
  else if(other.isRehashing())
    {
      other.wrapUp();
      m_currSize = other.m_currSize;
      m_tableSize = other.m_tableSize;
      m_array = new char*[m_tableSize];

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

      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      m_second = NULL;
      m_third = NULL;


      m_second = NULL;
      m_third = NULL;
    }
}

const HashTable& HashTable::operator=(HashTable &rhs)
{
  cout << "BEGINNING = " << endl;
  if(isRehashing())
    {
      delete m_second;
      m_second = NULL;
    }
  if(m_array != NULL)
    {
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
      delete [] m_array;
      m_array = NULL;
    }


  if(!rhs.isRehashing())
    {
      cout << "This joint aint eem rehashing"  << endl;
      m_currSize = rhs.m_currSize;
      m_tableSize = rhs.m_tableSize;
      m_array = new char*[m_tableSize];
      
      rhs.dump();

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
	      cout << " after " << endl;
	    }
        }

      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      m_second = NULL;
      m_third = NULL;


      m_second = NULL;
      m_third = NULL;
    }
  else if(rhs.isRehashing())
    {
      cout << "This joint rehashing, wrapping up!"  << endl;
      rhs.wrapUp();
      cout << "WRAPPED UP" << endl;

      m_currSize = rhs.m_currSize;
      m_tableSize = rhs.m_tableSize;
      m_array = new char*[m_tableSize];

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

      
      m_isRehashing = false;
      m_isMigrating = false;
      m_isRemoving = false;
      m_giveUp = false;
      m_wrapUp = false;
      m_second = NULL;
      m_third = NULL;
      rhs.dump();
      dump();
    }

}


void HashTable::insert(const char *str)
{
  char *myString = strdup(str);
  insertOther(myString);

}


void HashTable::insertOther(char *str)
{
  int firstIndex = getIndex(str);
  m_currSize++;
  
  if(isRehashing())
    {
      int secondIndex = m_second->getIndex(str);
      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp();
	}
      if(findOther(firstIndex, str, m_array) || 
	 findOther(secondIndex, str, m_second->m_array))
	{
	  m_currSize--;
	}
      else if (!findOther(firstIndex, str, m_array) && 
	       !findOther(secondIndex, str, m_second->m_array))
	{
	  m_second->m_array[secondIndex] = str;
	  m_second->m_currSize++;
	  m_currSize--;
	  
	}
      
      if(!isMigrating())
        {
          if(tooEmpty(m_currSize, m_tableSize))
            wrapUp();
	  if(tooFull(m_second->m_currSize, m_second->m_tableSize) || m_giveUp == true)
	    giveUp();
        }

    }
  //not rehashing
  else
    {
      if (findOther(firstIndex, str, m_array))
	{
	  m_currSize--;
	}
      else
	{
	  m_array[firstIndex] = str;
	  if(isRehashing())
	    migrateData(firstIndex);
	}
      if(tooFull(m_currSize, m_tableSize))
	{
	  rehash();
	}
    }
}



void HashTable::insertIn(char *str)
{
  int index = getIndex(str);
  
  if (findOther(index, str, m_array))
    {
      //
    }
  else
    {
      m_array[index] = str;
    }

}



bool HashTable::find(const char *str)
{
  if(str == DELETED)
    cout << "WTH" << endl;

	int firstIndex = getIndex(str);

	if(isRehashing())
    {
      int secondIndex = m_second->getIndex(str);

      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp();
	}


      if (findOther(firstIndex, str, m_array) || 
	  findOther(secondIndex, str, m_second->m_array))
	{
	  if(!isMigrating())
	    {
	      if(tooEmpty(m_currSize, m_tableSize))
		wrapUp();
	      	    
	    }
	  return true;
	}
      else 
	{
	  if(!isMigrating())
            {
              if(tooEmpty(m_currSize, m_tableSize))
                wrapUp();
	    }
	  return false;
	}
    }    

  //not rehashing
  else
    {  
      if (findOther(firstIndex, str, m_array))
	{
	  return true;
	}
      else return false;
    }
}


bool HashTable::findOther(int &index, const char *str, char ** arr)
{
  if(arr)
    {
      if (arr[index] == NULL)
	{
	  return false;
	}
      else if (arr[index] == DELETED || strcmp(arr[index], str) != 0)
	{
	  
	  if (findProbe(index, str, arr))
	    {
	      return true;
	    }
	  else
	    return false;
	}
      else if (strcmp(arr[index], str) == 0)
	{
	  return true;
	}
    }
}

char * HashTable::remove(const char *str)
{
  m_isRemoving = true;
  int firstIndex = getIndex(str);
  char *theString = NULL;
	
  if(isRehashing())
    {
      if(!isMigrating())
	{
	  if(tooEmpty(m_currSize, m_tableSize))
	    wrapUp();
	}

	  int secondIndex = m_second->getIndex(str);
	  if (findOther(firstIndex, str, m_array) && 
	      findOther(secondIndex, str, m_second->m_array))
	    {
	      char *theString = m_array[firstIndex];
	      m_array[firstIndex] = DELETED;
	      m_second->m_array[secondIndex] = DELETED;
	      m_currSize--;
	      m_second->m_currSize--;
	      m_isRemoving = false;
	      if(theString == DELETED)
		return NULL;
	      return theString;
	    }
	  else if (findOther(firstIndex, str, m_array) && 
		   !findOther(secondIndex, str, m_second->m_array))
	    {
	      char *theString = m_array[firstIndex];
	      m_array[firstIndex] = DELETED;
	      m_currSize--;
	      m_isRemoving = false;
	      if(theString == DELETED)
                return NULL;

	      return theString;
	    }
	  else if (!findOther(firstIndex, str, m_array) &&
		   findOther(secondIndex, str, m_second->m_array))
	    {
	      char *theString = m_second->m_array[secondIndex];
	      m_second->m_array[secondIndex] = DELETED;
	      m_second->m_currSize--;
	      m_isRemoving = false;
	      if(theString == DELETED)
                return NULL;

	      return theString;
	    }
	  else return NULL;
	}
  else
    {
      if (findOther(firstIndex, str, m_array))
	{
	  char *theString = m_array[firstIndex];
	  m_array[firstIndex] = DELETED;
	  m_currSize--;
	  m_isRemoving = false;
	  if(theString == DELETED)
	    return NULL;

	  return theString;
	}
      else return NULL;
    }
}

bool HashTable::isRehashing()
{
  return m_isRehashing;
}

void HashTable::rehash()
{
  m_isRehashing = true;
  m_second = new HashTable(m_currSize * 4);
  cout << "NEW HASHTABLE OF SIZE " << m_second->m_tableSize <<endl;
  for(int i = 0; i < m_second->m_tableSize; i++)
    {
      m_second->m_array[i] = NULL;
    }

}

unsigned int HashTable::getIndex(const char *str)
{
  unsigned int index = hashCode(str) % m_tableSize;
  return index;
}


void HashTable::dump()
{
      cout << "HashTable #1: size = " << m_currSize << ", tableSize = " << m_tableSize << endl;
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
      if(isRehashing())
	{
	  cout << "HashTable #2: size = " << m_second->m_currSize 
	       << ", tableSize = " << m_second->m_tableSize << endl;
		for(int i = 0; i < m_second->m_tableSize; i++)
	    {
	      cout << "H2[ " << i << "] = ";
	      if(m_second)
		{
		  if(m_second->m_array[i] != NULL && m_second->m_array[i] != DELETED)
		    cout << m_second->m_array[i] << " (" << m_second->getIndex(m_second->m_array[i]) <<")";
		}
	      cout << endl;
	    }
	}

}


bool HashTable::findProbe(int &index, const char *str, char ** arr)
{
	///WHAT DO I WANT FIND OTHER TO DO
	/*
	return true if we find the string
	return false if we don't
	change index to the index of the string or to the next empty spot

	*/

	int possibleIndex = -1;
	int clusterStart = index, clusterEnd = index;
	int probeCount = 1;
	bool found = false, stop = false;
	
	if (arr == m_array)
	{
		if (clusterEnd >= m_tableSize)
		{
			clusterStart -= m_tableSize;
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
	while (arr[clusterEnd] != NULL)
	{
	  probeCount++;
	  if ((arr[clusterEnd] != NULL && arr[clusterEnd] != DELETED) &&
	      strcmp(str, arr[clusterEnd]) == 0)
	    {
	      index = clusterEnd;
	      found = true;
	      stop = true;
	    }
	  else if (arr[clusterEnd] == DELETED && possibleIndex == -1)
	    {
	      possibleIndex = clusterEnd;
	    }
		clusterEnd++;

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
	
	if (probeCount >= 10 && !isRehashing())
	  rehash();

	if(m_second)
	  {
	    if(arr == m_second->m_array && probeCount >= 10)
	      m_giveUp = true;
	  }

	if(isRehashing())
	  {
	    while (arr[clusterStart - 1] != NULL)
	      {
		clusterStart--;
		probeCount++;
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
	    if(m_array)
	      {
		if (!isMigrating() && arr == m_array && !m_wrapUp)
		  {
		    migrateData(clusterStart, probeCount);
		  }
	      }
	  }
	
	if(possibleIndex != -1 && m_isRemoving == false)
	  {
	    index = possibleIndex;
	  }
	else if(stop == false)
	  {
	    index = clusterEnd;
	  }

	return found;
}

void HashTable::wrapUp()
{
  m_wrapUp = true;
  char *myString;
 
  for(int i = 0; i < m_tableSize; i++)
    {
      if(m_array[i] != DELETED && m_array[i] != NULL)
	{
	  myString = strdup(m_array[i]);
	  free(m_array[i]);
	  m_second->insertIn(myString);
	  m_second->m_currSize++;
	}
    }
  delete [] m_array;
  m_array = m_second->m_array;
  m_currSize = m_second->m_currSize;
  m_tableSize = m_second->m_tableSize;
  m_second->m_array = NULL;
  delete m_second;
  m_second = NULL;
  m_wrapUp = false;
  m_isRehashing = false;
}


void HashTable::giveUp()
{
  cout << "ENTERING GIVE UP" << endl;

  char *myString;

  m_third = new HashTable((m_currSize + m_second->m_currSize) * 4);
  cout << "NEW HASHTABLE OF SIZE " << m_third->m_tableSize <<endl;
  for(int i = 0; i < m_third->m_tableSize; i++)
    {
      m_third->m_array[i] = NULL;
    }

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


  delete [] m_array;
  m_array = m_third->m_array;
  m_currSize = m_third->m_currSize;
  m_tableSize = m_third->m_tableSize;
  m_second->m_array = NULL;
  m_third->m_array = NULL;
  delete m_second;
  delete m_third;
  m_second = NULL;
  m_third = NULL;

  m_isRehashing = false;
  m_giveUp = false;
  cout << "EXITING WRAP UP" << endl;

}

bool HashTable::tooFull(int currSize, int tableSize)
{
  float loadFactor = (float)currSize/(float)tableSize;
  if(loadFactor > 0.5)
    return true;
  else
    return false;
}


bool HashTable::tooEmpty( int currSize, int tableSize)
{
  //cout << currSize << " " << tableSize << endl;
  float loadFactor = (float)currSize/(float)tableSize;
  //cout << loadFactor << endl;
  if(loadFactor < 0.03)
    return true;
  else
    return false;
}

bool HashTable::isMigrating()
{
  return m_isMigrating;
}


void HashTable::migrateData(int from, int count)
{
  m_isMigrating = true;
  int start = from;
  int counter = count;
  
  if(m_array[start] != NULL && m_array[start] != DELETED)
    {
      while(counter > 0)
	{
	  if(counter == 1)
	    {break;}
	  char *str = m_array[start];
	  if(str == DELETED)
	    {
	      //Next
	    }
	  else
	    {
	      remove(str);
	      insertOther(str);
	    }
	  start++;
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

  int HashTable::tableSize(int table)
  {
    if(isRehashing())
      {
	if(table == 0)
	  return m_tableSize;
	else
	  return m_second->m_tableSize;
      }
    else return m_tableSize;

  }

  int HashTable::size(int table)
  {
    if(isRehashing())
      {
        if(table == 0)
          return m_currSize;
        else
          return m_second->m_currSize;
      }
    else return m_currSize;

  }

  const char * HashTable::at(int index, int table)
  {
    char * stringAt;
    
    if(table == 0)
      {
	if(index < 0 || index >= m_tableSize)
	  throw out_of_range("Invalid index");
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


