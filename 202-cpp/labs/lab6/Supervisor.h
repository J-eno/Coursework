#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Employee.h"
#include "Manager.h"
#include <string>

class Supervisor : public Manager {
 public:
  Supervisor(string name, double payRate, string department);
  
  string GetDept();

  void SetDept(string newDept);

 protected:
 string  m_department;

};


#endif
