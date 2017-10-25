#include <iostream>
//#include <>
using namespace std;

int bSearch(const int arr[], const int arrSize, int val);

int main()
{
const int numPrimes = 22;

const int primes[numPrimes] = {
  101,
  103,
  107,
  109,
  113,
  127,
  131,
  137,
  139,
  149,
  151,
  157,
  199873,
  199877,
  199889,
  199909,
  199921,
  199931,
  199933,
  199961,
  199967,
  199999
} ;

int n = 158;

 cout << "n before turning to prime " << n << endl;


 int n2 = bSearch(primes, numPrimes, n);

 cout << "n after turning to prime " << n2 << endl;

 return 0;
}

int bSearch(const int arr[], const int arrSize, int val)
{
  int mid = 0, num = 0, min = 0, max = arrSize - 1;
  for(int i = 0; i < arrSize; i++)
    {
      //cout << arr[i];
    }

  while(min <= max)
    {
      mid = (min + max)/2;
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
