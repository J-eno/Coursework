//comments

#include "Game.h"

//Name: Game (Constructor)
//Precondition: None
//Postcondition: Game is started with monsters initialized, ben initialized,
//decides number of levels
Game::Game()
{
  m_levels = NumLevels();
  m_level = 1;
  m_formsBen = 1;
  
  InitBen();
  InitMonsters();
  Start(100);
}

//Name: ~Game (Destructor)
//Precondition: Destructor for the game
//Postcondition: Deletes all dynamically allocated data

Game::~Game()
{
  //Delete each element in m_mons
  for(int i = 0; i < 20; ++i)
    {
      delete m_mons[i];
      m_mons[i] = NULL;
    }
  //Delete each element in m_ben
  for (int i = 0; i < 3; ++i)
    {
      delete m_ben[i];
      m_mons[i] = NULL;
    }

  //Free m_mons Array
  delete [] m_mons;
  m_mons = NULL;
  
  //Free m_ben Array
  delete [] m_ben;
  m_ben = NULL;
  
}

//Name: InitMonsters
//Precondition: Requires m_mons
//Postcondition: Dynamically populates m_mons with one monster per level

void Game::InitMonsters()
{
  //set m_mons to an array of size 20
  m_mons = new Monster*[20]();
  //for each level populate the array with a new monster
  for(int i = 0; i < m_levels; i++)
    {
      Monster *mon =  new Monster(i+1);
      m_mons[i] = mon;
    }
}

//Name: InitBen
//Precondition: Requires m_ben
//Postcondition: Dynamically populates m_ben with all possible forms
// Level 1 = Ben, Level 2 = Pyronite, Level 3 = Crystalsapien

void Game::InitBen()
{
  //Initialize m_ben to an array of size 3 (3 forms)
  m_ben = new Ben*[3]();
  // first Ben = normal Ben
  m_ben[0] = new Ben("Ben", 100, "hand-to-hand", "kick", 0.0, 10, 0, 2, 10, 20, 25);
  //second Ben = Pyronite
  m_ben[1] = new Pyronite("Pyronite", 100, "fire", "flamer", 0.0, 15, 0, 1, 15, 20, 30);
  //third Ben = Crystal
  m_ben[2] = new Crystalsapien("Crystalsapien", 100, "energy", "laser", 0.25, 25, 0, 1, 25, 30, 10);


}

//Name: SetBen
//Precondition: Requires populated m_ben (Lists all possible Bens for that level)
//Postcondition: Sets m_currBen based on the user choice
void Game::SetBen(int startLife)
{
  if(m_level == 2)
    {
      m_formsBen = 2;
    }
  if(m_level > 2)
    {
      m_formsBen = 3;
    }

  int choice = 0;
  cout << "Select one from the available forms of Ben at level " << m_level
       << " are" << endl;
  //Displays the bens available
  for(int i = 0; i < m_formsBen; ++i)
    {
      cout << (i+1) << "." << m_ben[i]->GetName() << endl;
    }

  //while choice != one of bens fors
  while(choice < 1 || choice > m_formsBen)
    {
      cout << "What would you like to do?" << endl
	   << "Enter 1 to " << m_formsBen << ":" << endl;

      cin >> choice;
      cout << endl;
      if(choice < 1 || choice > m_formsBen)
	{
	  cout << "Invalid input; please re-enter." << endl;
	}
    }
  //current Ben = the Ben at [choice - 1] in m_ben
  m_currBen = m_ben[choice - 1];
  m_currBen->SetLife(startLife);

}


//Name: Start
//Precondition: Starts the game (Primary driver of game)
//Postcondition: May exit if Ben dies (exits game) or Monster dies (goes to
//next level or wins game!
void Game::Start(int startLife)
{

  //current Monster = monster corresponding with the current level
  m_currMons = m_mons[m_level - 1];
  cout << endl << "\t \t The game starts...." << endl
       << "\t \t Level " << m_level << " of " << m_levels << endl;
  SetBen(startLife);

  string currBen = m_currBen->GetName();
  string currMon = m_currMons->GetName();

  cout << "BEN: " << currBen << endl;
  cout << "MONSTER: " << currMon  << endl << endl;

  cout << "The start life of " << currBen << " is: " << startLife << endl;
  cout << "The start life of " << currMon << " is: " << m_currMons->GetLife() << endl << endl;
  //while Input() has not returned false
  while(Input())
    {
      //if both Ben and the Monster are alive
      if( m_currBen->GetLife() > 0 && m_currMons->GetLife() > 0)
	{
	  //display their HP
	  cout << currBen << " :" << m_currBen->GetLife() << "\t" 
	       << currMon << " :" << m_currMons->GetLife() << endl << endl;
	}
    }
  //if Monster is defeated
  if(m_currMons->GetLife() <= 0)
    {
      cout << "Congrats! " << currBen << " won that level!" << endl;
      //and we are on the last level
      if(m_level == m_levels)
        {
          cout << "Congrats! You won the game!" << endl;
	}

    }
  //if Ben is defeated
  else if(m_currBen->GetLife() <= 0)
    {
      cout << currBen << " was defeated at level " << m_level << "!" << endl
	   << "You have lost the game" << endl;
      
    }
  //if we beat monster and we're not on the final level
  if(m_currMons->GetLife() <= 0 && m_level != m_levels)
    {
      m_level++;
      //Call start again with start life being the current HP of ben
      Start(m_currBen->GetLife());
    }
}

//Name: NumLevels
//Precondition: Prompts user for number of levels between 1 and 20
//Postcondition: Returns user response
int Game::NumLevels()
{
  int input = 0;
  while(input < 1 || input > 20)
    {
      cout << "How many levels would you like to try?" << endl;
      cin >> input;
    }
  return input;
}

//Name: Input
//Precondition: Checks to see if Ben and monster are alive
//During: Prompts user with menu
//Postcondition: Manages types of attacks (normal, special, or ultimate)
bool Game::Input()
{
  int choice = 0;
  if(m_currBen->GetLife() > 0 && m_currMons->GetLife() > 0)
    {
      while(choice < 1 || choice > 3)
	{
	  cout << "What would you like to do?" << endl
	       << "1. Normal Attack" << endl
	       << "2. Special Attack" << endl
	       << "3. Ultimate Attack" << endl
	       << "Enter 1 to 3:" << endl;
	  cin >> choice;

	  if(choice < 1 || choice > m_formsBen)
	    {
	      cout << "Invalid input; please re-enter." << endl;
	    }

	}
      switch(choice)
	{
	case 1:
	  cout << endl;
	  m_currBen->Attack(m_currMons);
	  break;
	case 2:
	  cout << endl;
	  m_currBen->SpecialAttack(m_currMons);
	  break;
	case 3:
	  cout << endl;
	  m_currBen->UltimateAttack(m_currMons);
	  break;
	}
      if(m_currMons->GetLife() > 0)
	{
	  m_currMons->Attack(m_currBen);
	}
      return true;
    }
  return false;
}
