#include <iostream>
#include <cmath>

using namespace std;

bool IsPerfSq(int n);

int main()
{
  cout << "hi" << "" << "bye" << endl;
  long n;
  cout << "enter nummmm: ";
  cin >> n;

  cout << sqrt(n) << " " << cbrt(n)<< endl;
  // bool sad = IsPerfSq(n);
  //cout << sad << endl;

}

bool IsPerfSq(int n)
{
  int temp;
  temp = sqrt(n);
  if(temp*temp == n)
    {
      return true;
    }
  else
{
    return false;
}
}
