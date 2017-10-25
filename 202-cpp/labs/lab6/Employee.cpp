#include "Employee.h"

Employee::Employee(string name, double payRate)
{
  m_name = name;
  m_payRate = payRate;
}

string Employee::GetName()
{
  return m_name;
}

double Employee::GetPayRate()
{
  return m_payRate;
}

double Employee::Pay(double hoursWorked)
{
  return hoursWorked * m_payRate;
}

void Employee::SetName(string newName)
{
  m_name = newName;
}

void Employee::SetPayRate(double newRate)
{
  m_payRate = newRate;
}
