#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include <string>

class Manager : public Employee {
 public:
  Manager(string name,
          double payRate,
          bool isSalaried);
  Manager(string name, double payRate);

  bool GetSalaried();
  double Pay(double hoursWorked);

  void SetSalaried(bool newSalaried);

 protected:
  bool m_salaried;
};

#endif
