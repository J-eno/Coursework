// File: ManageShips.cpp
// Project: CMSC 202 Project 5, Fall 2016
// Author: Joel Okpara
// Date: 12/11/16
// Section 1
// Email: joelo1@umbc.edu

// Description:
/* This class manages a majority of the functions. 
After everything is loaded and some calculations are being done, 
this class manages the various aspects including getting the Heaviest and Lightest ships
(regardless if they are person or item ships), 
Oldest and Youngest person, and Heaviest and Lightest items. 
Also can output any person or item not loaded into a ship due to capacity limitations. 
Finally, can write an output file that contains each ship name and then each of the cargo.*/

#include "ManageShips.h"

 // Constructor for Managing the ships.
 // Once the data has been imported and split used to manage all additonal functions
 // Two ships (one for item and one for people)
 // Two cargo lists (one for items and one for people)
ManageShips::ManageShips(vector< Spaceship <Item> > itemShip,
			 vector< Spaceship <Person> > personShip,
			 vector< Item > itemCargo,
			 vector< Person > personCargo)
{
  m_itemShips = itemShip;
  m_personShips = personShip;
  m_items = itemCargo;
  m_person = personCargo;
  LoadItemShip();
  LoadPersonShip();
}


//Name: LoadItemShip
//Precondition: Requires itemShips and itemCargo
//Postcondition: Loads items into each ship
//Additional information: Cannot load more than capacity of each ship.
//It is possible that not all items will be loaded
void ManageShips::LoadItemShip()
{
  double currWeight = 0;
  //for each ship in our vector of ships
  for(unsigned int j = 0; j < m_itemShips.size(); ++j)
    {
      currWeight = 0;
      size_t i = 0;
      //while there are still items
      while (i < m_items.size())
	{
	  //If the current weight of the ship + the weight of the current item is under
	  // the ship's weight capacity
	  if((currWeight + m_items[i].GetWeight()) <= m_itemShips[j].GetCapacity())
	    {
	      //add the current item to the current ship's cargo
	      m_itemShips[j].AddCargo(m_items[i]);
	      //add the weight to the ship's current weight
	      currWeight += m_items[i].GetWeight();
	      //remove item from vector of items
	      m_items.erase(m_items.begin() + i);
	    }
	  else
	    {
	      ++i;
	    }
	}
    }
}

//Name: LoadPersonShip
//Precondition: Requires personShips and personCargo
//Postcondition: Loads people into each ship
//Additional information: Cannot load more than capacity of each ship.
//It is possible that not all items will be loaded
void ManageShips::LoadPersonShip()
{
  int currPeople = 0;
  //for each ship in vector of personShips
  for(unsigned int j = 0; j < m_personShips.size(); ++j)
    {
      currPeople = 0;
      size_t i = 0;
      while (i < m_person.size())
        {
	  //if the current amount of people on the ship + 1 is 
	  //still under or equal to the ship's capacity
          if((currPeople + 1) <= m_personShips[j].GetCapacity())
            {
	      //add person to the ship
              m_personShips[j].AddCargo(m_person[i]);
              currPeople++;
	      //remove person from vector of people
              m_person.erase(m_person.begin() + i);
            }
          else
            {
              ++i;
            }
        }
    }
}

//Name: DisplayItemLeft
//Precondition: Requires that all item ships have been loaded
//Postcondition: Outputs (cout) each item not loaded into a ship
void ManageShips::DisplayItemLeft()
{
  //if vector of items is empty
  if(m_items.empty())
    {
      cout << "None" << endl << endl;
    }
  else
    {
      //iterate through vector
      for (unsigned int i = 0; i < m_items.size(); ++i)
	{
	  //print items still in it
	  cout << "Item " << i + 1 << " - Name: " << m_items[i].GetName() << endl; 
	}
    }
}

//Name: DisplayPersonLeft
//Precondition: Requires that all people ships have been loaded
//Postcondition: Outputs (cout) each person not loaded into a ship
void ManageShips::DisplayPersonLeft()
{
  //if vector of people is empty
  if(m_person.empty())
    {
      cout << "None" << endl << endl;
    }
  else
    {
      //loop through vector of people
      for (unsigned int i = 0; i < m_person.size(); ++i)
        {
	  //print name of people still in the vector
          cout << "Person " << i + 1 << " - Name: " << m_person[i].GetFName() << endl << endl;
        }
    }
}

//Name: OutputShips
//Precondition: Requires that all ships have been loaded
//Postcondition: Writes out all ships and their cargo to a specific output file
//Output file will always be proj5_output.txt
void ManageShips::OutputShips()
{
  //open file to output to
  fstream output;
  output.open("proj5_output.txt", fstream::out);
  
  output << "**Personnel Ships**" << endl;
  //for each ship in our vector of people ships
  for(unsigned int i = 0; i < m_personShips.size(); ++i)
    {
      output << "**Ship Name: " << m_personShips[i].GetName() << "**\n";
      vector<Person> people = m_personShips[i].GetCargo();
      //iterate through the people on the ship
      for(unsigned int j = 0; j < people.size(); ++j)
	{
	  if(!people.empty())
	    {
	      //print person's first and last names
	      output << people[j].GetFName() + " "<< people[j].GetLName() << endl;
	    }
	  else
	    {
	      output << "Empty" << endl;
	    }
	}
    }
  output << "**Cargo Ships**" << endl;
  //for each ship in our vector of cargo ships
  for(unsigned int x = 0; x < m_itemShips.size(); ++x)
    {
      output << "**Ship Name: " << m_itemShips[x].GetName() << "**\n";
      vector<Item> items = m_itemShips[x].GetCargo();
      //iterate through the ship's cargo
      for(unsigned int y = 0; y < items.size(); ++y)
        {
	  if(!items.empty())
	    {
	      //print each item's name
	      output << items[y].GetName() << endl;
	    }
	  else
	    {
	      output << "Empty" << endl;
	    }
	}
    }

}

//Name: GetHeaviestShip()
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout) the heaviest ship based on total weight
string ManageShips::GetHeaviestShip()
{
  int personIndex = 0;
  int itemIndex = 0;
  
  //iterate through the vector of people ships
  for(unsigned int i = 0; i < m_personShips.size(); ++i)
    {
      //finds the index of the heaviest people ship
      if(m_personShips[i] > m_personShips[personIndex])
	{
	  personIndex = i;
	}
    }

  //iterate through the vector of item ships
  for(unsigned int i = 0; i < m_itemShips.size(); ++i)
    {
      //finds the index of the heaviest item ship
      if(m_itemShips[i] > m_itemShips[itemIndex])
	{
	  itemIndex = i;
	}
    }

  //compares heaviest item ship and heaviest people ship
  if(m_itemShips[itemIndex] > m_personShips[personIndex])
    {
      return m_itemShips[itemIndex].ToString();
    }
  else
    {
      return m_personShips[personIndex].ToString();
    }
}

//Name: GetLightestShip()
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout) the lightest ship based on total weight
string ManageShips::GetLightestShip()
{
  int personIndex = 0;
  int itemIndex = 0;

  //for each ship in vector of people ships
  for(unsigned int i = 0; i < m_personShips.size(); ++i)
    {
      //if ship at current index is lighter our lightest
      if(m_personShips[i] < m_personShips[personIndex])
	{
	  personIndex = i;
	}
    }

  //for each ship in our vector of item ships
  for(unsigned int i = 0; i < m_itemShips.size(); ++i)
    {
      if(m_itemShips[i] < m_itemShips[itemIndex])
	{
	  itemIndex = i;
	}
          
    }
  //compares the lightest item ship and lightest person ship
  if(m_itemShips[itemIndex] < m_personShips[personIndex])
    {
      return m_itemShips[itemIndex].ToString();
    }
  else
    {
      return m_personShips[personIndex].ToString();
    }
}

//Name: GetLightestItem
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout) the lightest item on a ship
string ManageShips::GetLightestItem()
{
  //vector for each ship's cargo
  vector<Item> cargo;
  //vector for the lightest items in each ship
  vector<Item> lightest;
  int index = 0;
  
  //for each ship in our ship of items
  for(unsigned int i = 0; i < m_itemShips.size(); ++i)
    {
      //make sure cargo vector is empty then fill it with current ship's cargo
      cargo.clear();
      cargo = m_itemShips[i].GetCargo();
      //if it has cargo
      if(!cargo.empty())
	{
	  //iterate through the cargo
	  for(unsigned int j = 0; j < cargo.size(); ++j)
	    {
	      //holds the index of the lighter item
	      if( cargo[j].GetWeight() < cargo[index].GetWeight())
		{
		  index = j;
		}
	    }
	  //adds the item at that index into our vector of lightest items
	  lightest.push_back(cargo[index]);
	}
    }

  int ltIndex = 0;
  //iterate through vector of lightest items
  for(unsigned int i = 0; i < lightest.size(); ++i)
    {
      //finds lightest item
      if( lightest[i].GetWeight() < lightest[ltIndex].GetWeight())
	{
	  ltIndex = i;
	}
    }
  //return the info of the lightest item
  return lightest[ltIndex].ToString();
}

//Name: GetHeaviestItem
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout) the heaviest item on a ship
string ManageShips::GetHeaviestItem()
{
  vector<Item> cargo;
  vector<Item> heaviest;
  int index = 0;

  //for each ship in our vector of item ships
  for(unsigned int i = 0; i < m_itemShips.size(); ++i)
    {
      //get ship's cargo
      cargo.clear();
      cargo = m_itemShips[i].GetCargo();
      //if it has cargo
      if(!cargo.empty())
	{
	  //iterate through cargo
	  for(unsigned int j = 0; j < cargo.size(); ++j)
	    {
	      //gets the index of heaviest item in cargo
	      if(cargo[j].GetWeight() > cargo[index].GetWeight())
		{
		  index = j;
		}
	    }
	  //add that cargo to vector of heaviest cargo
	  heaviest.push_back(cargo[index]);
	}
    }

  int hvIndex = 0;
  //iterate through vector of heaviest cargo
  for(unsigned int i = 0; i < heaviest.size(); ++i)
    {
      //gets index of heaviest cargo
      if(heaviest[i].GetWeight() > heaviest[hvIndex].GetWeight())
	{
	  hvIndex = i;
	}
    }
  //returns info on the cargo at that index
  return heaviest[hvIndex].ToString();

}

//Name: GetOldestPerson
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout)  the oldest person on a ship
string ManageShips::GetOldestPerson()
{
  //vector to hold all the people on a particular ship
  vector<Person> people;
  //vector to hold the oldest people on each ship
  vector<Person> oldest;
  int index = 0;

  //for each ship in vector of people ships
  for(unsigned int i = 0; i < m_personShips.size(); ++i)
    {
      //gets the ship's cargo(people)
      people.clear();
      people = m_personShips[i].GetCargo();
      //if there are people on the ship
      if(!people.empty())
        {
	  //get the oldest person on the ship
          for(unsigned int j = 0; j < people.size(); ++j)
            {
              if(people[j].GetAge() > people[index].GetAge())
                {
                  index = j;
                }
            }
	  //add the person to our vector of oldest people across ships
          oldest.push_back(people[index]);
        }
    }

  int oldIndex = 0;
  //find oldest person in our vector of old people
  for(unsigned int i = 0; i < oldest.size(); ++i)
    {
      if(oldest[i].GetAge() > oldest[oldIndex].GetAge())
        {
          oldIndex = i;
        }
    }
  //return oldest person's info
  return oldest[oldIndex].ToString();

}

//Name: GetYoungestPerson
//Precondition: Requires that all ships have been loaded
//Postcondition: Outputs (cout)  the youngest person on a ship
string ManageShips::GetYoungestPerson()
{
  vector<Person> people;
  //vector to hold the youngest people on each ship
  vector<Person> youngest;
  int index = 0;

  //for each ship in vector of people ships
  for(unsigned int i = 0; i < m_personShips.size(); ++i)
    {
      //get the people on that ship
      people.clear();
      people = m_personShips[i].GetCargo();
      //if there are people on the ship
      if(!people.empty())
        {
	  //get the youngest on that ship
          for(unsigned int j = 0; j < people.size(); ++j)
            {
              if(people[j].GetAge() < people[index].GetAge())
                {
                  index = j;
                }
            }
	  //add that person to vector of youngest people
          youngest.push_back(people[index]);
        }
    }

  int ygIndex = 0;
  //find youngest in vector of youngest people
  for(unsigned int i = 0; i < youngest.size(); ++i)
    {
      if(youngest[i].GetAge() < youngest[ygIndex].GetAge())
        {
          ygIndex = i;
        }
    }
  //return youngest person's info
  return youngest[ygIndex].ToString();

}
