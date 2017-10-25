#include <iostream>
using namespace std;

//Takes in a number and loops through and adds the number to the total.
//If total = 0 and we pass the literal 10 then it should
// print 10+0+1+2+3+4+5+6+7+8+9=55 

int addLoop(int num); //prototype

int main() {
  int total = 0; //Set total to 0
  total = addLoop(10); //Call addLoop with a literal of 10
  cout << "New total is: " << total << endl; //Print output
  return 0;
}

int addLoop(int num){
  int total = 0;
  for(int i = 0; i < num; i++) { //Loop 10 times
    total += i; //Add i to num
  }
  return total;
}
