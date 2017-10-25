#include <iostream>
#include "Employee.h"
#include "Manager.h"
#include "Supervisor.h"

using namespace std;

int main()
{
  Employee emp("Stevie Curry", 23.0);
  Manager mgr("Al Ovechkin", 1450.0, true);
  Supervisor sup("James Flacco", 480.0, "Accounting");

  // Assume all employees worked 40 hours this period.

  cout << "For Employee:" << endl;
  cout << "Name: " << emp.GetName() << endl;
  cout << "Pay: " << emp.Pay(40.0) << endl;

  cout << "Changing the Employee's name..." << endl;
  emp.SetName("Jon Conners");
  cout << "New Name: " << emp.GetName() << endl;

  cout << endl;
  cout << "For Manager:" << endl;
  cout << "Name: " << mgr.GetName() << endl;
  cout << "Salaried: " << mgr.GetSalaried() << endl;
  cout << "Pay: " << mgr.Pay(40.0) << endl;

  cout << "Changing the Manager's salaried status..." << endl;
  mgr.SetSalaried(false);
  cout << "New Pay: " << mgr.Pay(40.0) << endl;

  cout << endl;
  cout << "For Supervisor:" << endl;
  cout << "Name: " << sup.GetName() << endl;
  cout << "Pay: " << sup.Pay(40.0) << endl;
  cout << "Dept: " << sup.GetDept() << endl;

  cout << "Changing the Supervisor's pay rate..." << endl;
  sup.SetPayRate(900.0);
  cout << "New Pay: " << sup.Pay(40.0) << endl;

  return 0;
}
