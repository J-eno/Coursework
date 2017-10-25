// File: HashTable.h
//
// CMSC 341 Spring 2017 Project 5
//
// Class declarations for Incremental Rehashing HastTable
//

#ifndef _HashTable_H_
#define _HashTable_H_

#include <cstring>
#include "primes.h"
using namespace std;

const int MIN_TABLE_SIZE = 101; //min table size
const int MAX_TABLE_SIZE = 199999; // max table size
const int IN_TABLE = -999;
const int NOT_IN_TABLE = -9999;
class HashTable
{
 public:
	static char * const DELETED;
  //constructors, destructor, equal operator
  HashTable(int n = 101);
  ~HashTable();
  HashTable(HashTable &other);
  const HashTable& operator=(HashTable &rhs);

  //member functions
  void insert(const char *str);
  
  bool find(const char *str);
  
  char * remove( const char *str);
  
  void dump();
  
  int toPrime(const int arr[], const int arrSize, int val);
  
  bool isPrime(int num);
  
  //hashCode function
  unsigned int hashCode(const char *str) {
    
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    
    int i = 0 ;
    while (str[i] != '\0') {
      val = val * thirtyThree + str[i] ;
      i++ ;
    }
    return val ;
  }
  
  //grading functions
  bool isRehashing();
  int tableSize(int table = 0);
  int size(int table = 0);
  const char *at(int index, int table = 0);
  
 private:
	
  void insertIn(char *str);
  void insertOther(char *str);
  bool findOther(int &index, const char *str, char ** arr);
  bool findProbe(int &index, const char *str, char ** arr);

  
  void rehash();
  unsigned int getIndex(const char *str);
  bool tooFull(int currSize, int tableSize);
  bool tooEmpty(int currSize, int tableSize);
  void migrateData(int from, int count = 2);
  bool isMigrating();
  
  void wrapUp();
  void giveUp();

  int m_currSize;
  int m_tableSize;
  char ** m_array;

  bool m_isRehashing;
  bool m_isMigrating;
  bool m_isRemoving;
  bool m_giveUp;
  bool m_wrapUp;

  HashTable *m_second;
  HashTable *m_third;

};

#endif // _HashTable_H_
