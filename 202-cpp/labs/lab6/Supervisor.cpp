#include "Supervisor.h"
using namespace std;


Supervisor::Supervisor(string name, double payRate, string department)
: Manager(name, payRate)
{
  m_salaried = true;
  SetDept(department);
}

string Supervisor::GetDept()
{
  return m_department;
}

void Supervisor::SetDept(string newDept)
{
  m_department = newDept;
}
