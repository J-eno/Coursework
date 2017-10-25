#include "Manager.h"
using namespace std;

Manager::Manager(string name,
                 double payRate,
                 bool isSalaried)
  : Employee(name, payRate)
{
  m_salaried = isSalaried;
}

Manager::Manager(string name, double payRate)
  : Employee(name,payRate)
{

}

bool Manager::GetSalaried()
{
  return m_salaried;
}


double Manager::Pay(double hoursWorked)
{
  if (m_salaried)
    return m_payRate;
  /* else */
  return Employee::Pay(hoursWorked);
}

void Manager::SetSalaried( bool newSalaried)
{
  m_salaried = newSalaried;
}
