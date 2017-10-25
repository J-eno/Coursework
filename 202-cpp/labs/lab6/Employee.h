#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

using namespace std;

class Employee {
 public:
  Employee(string name, double payRate);
  
  string GetName();
  double GetPayRate();
  double Pay(double hoursWorked);

  void SetName(string newName);
  void SetPayRate(double newRate);

 protected:
  string m_name;
  double m_payRate;
};

#endif
