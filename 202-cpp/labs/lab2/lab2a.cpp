#include <iostream>
using namespace std;

const int EXTRA_POINTS = 2;

void extraCredit(int &exam01, int &exam02);

int main()
{
  int exam1, exam2 = 0;

  cout << "Enter score 1: ";
  cin >> exam1;
  cout << "Enter score 2: ";
  cin >> exam2;

  cout << "Score 1 before extra credit: " << exam1 << endl;
  cout << "Score 2 before extra credit: " << exam2 << endl;
  extraCredit(exam1, exam2);

  
  return 0;
}

void extraCredit(int &exam01, int &exam02)
{
  exam01 = exam01 + EXTRA_POINTS;
  cout << "Score 1 after extra credit: " << exam01 << endl;
  
  exam02 += EXTRA_POINTS;
  cout << "Score 2 after extra credit: " << exam02 << endl;

}
