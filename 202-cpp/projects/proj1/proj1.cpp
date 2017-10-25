// File: proj1.cpp
// Project: CMSC 202 Project 1, Fall 2016
// Author: Joel Okpara
// Date: 9/18/2016
// Section 1
// Email: joelo1@umbc.edu
/*
   This file is the main driver program for Project 1.
   This file implements a very basic ATM which:
   Has a starting menu that asks if the user wants to:
     Load data from a text file
     Input data themselves
   Has a main menu that asks if the user wants to:
     Check account balance
     Deposit money
     Withdraw money
     Display account details
     Exit and save account info

 */

#include "proj1.h"

const char  INPUT_FILE[50] = "proj1.txt"; // The profile data file
const int CLOSE = -1; //Used to close the application in the start menu

int main()
{
  //formats numbers to XX.XX
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  fstream profileData;

  //user information variables
  string userFName = "";
  string userLName = "";
  int userAge = 0;
  double initDeposit = 0.0;

  float accountBalance = 0.0;

  int startInput = 0; //input on start menu returns to this variable
  int menuInput = 0; //input on main menu returns to this variable
  string saveDetails = "";

  bool done = false; //are we ready to exit the file

  //while we don't have an acceptable input, show the start menu
  while(startInput < 1 || startInput > 3)
    {
      startInput = menuStart();

      switch(startInput)
	{
	// reads in user details from the preexisting file
	case 1:
	  profileData.open(INPUT_FILE);
	  profileData >> userFName >> userLName >> userAge >> initDeposit;
	  profileData.close();
	  accountBalance = initDeposit;
	  break;
	 //Allows user to input their details
	case 2:
	  cout << "Please enter the following" << endl << endl
	       << "First Name: ";
	  cin >> userFName;
	  cout << "Last Name: ";
	  cin >> userLName;
	  cout << "Age: ";
	  cin >> userAge;
	  cout << "Initial Deposit: ";
	  cin >> initDeposit;
	  accountBalance = initDeposit;
	  break;
	//exits code from the first menu
	case 3:
	  cout << "Goodbye!" << endl;
	  //sets menuInput to CLOSE so that the next while loop will never run
	  menuInput = CLOSE;
	  break;
	default:
	  cout << "hi" << endl;

	}
    }
  //while we don't have an acceptable input, and we haven't set it to CLOSE
  while ((menuInput < 1 || menuInput > 5) && menuInput != CLOSE)
    {
      //while we're not ready to exit program
      while (!done)
	{
	  menuInput = menuMain();
	  switch(menuInput)
	    {
	    case 1:
	      displayBalance(accountBalance);
	      break;
	    case 2:
	      deposit(accountBalance);
	      break;
	    case 3:
	      withdraw(accountBalance);
	      break;
	    case 4:
	      displayAccountDetails(userFName, userLName, userAge, accountBalance);
	      break;
	    case 5:
	      //asks whether or not user would like to save their details
	      cout << "Would you like to save your account information? y/n" << endl;
	      cin >> saveDetails;
	      //if yes writes to the preexisting file
	      if(saveDetails == "y")
		{
		  profileData.open(INPUT_FILE);
		  profileData << userFName << endl 
			      << userLName << endl 
			      << userAge << endl 
			      << accountBalance;
		  profileData.close();
		  cout << "File Saved" << endl;
		}
	      cout << "Thanks you for using the UMBC ATM" << endl;
	      //tells us that we can exit program now
	      done = true;
	      break;
	    default:
	      cout << "what?" << endl;
	    }
	}
    }

  return 0;
}

// menuStart
//Displays the start menu and receives user input
int menuStart()
{
  int userInput = 0;
  cout << "Welcome to the UMBC ATM" << endl
       << "Choose from below:\n"
       << "1. Load a User Profile from File" << endl
       << "2. Enter a new User Profile" << endl
       << "3. Exit" << endl;
  cin >> userInput;
  
    return userInput;
}


//menuMain
//Displays main menu and receives user input
int menuMain()
{
  int userInput = 0;
  cout << "******** Please Choose an Option from the Menu ********" << endl
       << "1. Account Balance" << endl
       << "2. Deposit money" << endl
       << "3. Withdraw money" << endl
       << "4. Display your account details" << endl
       << "5. Exit" << endl
       << "Enter your choice: ";

  cin >> userInput;


  return userInput;
}


//displayBalance
//displays account balance
void displayBalance(float accountBalance)
{
  cout << endl;
  cout << "Account Balance: $" << accountBalance << endl;
  cout << endl;
}


//displayAccountDetails
//Displays the details that the user provided in the start menu
void displayAccountDetails(string fName, string lName, int age, float accountBalance)
{
  cout << endl 
       << "First Name: " << fName << endl
       << "Last Name: " << lName << endl
       << "Age: " << age << endl
       << "Account Balance: $" << accountBalance << endl << endl;

}

// deposit
// takes in the deposit amount and adds it to the account balance
void deposit( float &accountBalance)
{
  double depositAmount = 0;

  cout << endl 
       << "Please enter the amount to be deposited"
       << endl;
  cin >> depositAmount;
 
  if(depositAmount < 0)
    {
      cout  << endl << "Amount should be greater than 0" << endl << endl;
    }
  else
    {
      accountBalance += depositAmount;
      cout << endl << "$" << depositAmount << " deposited to your account" << endl << endl;
    }

}


// withdraw
// takes in the withdrawal amount and subtracts it from account balance
void withdraw( float &accountBalance)
{
  double withdrawAmount = 0;

  cout << endl
       << "Please enter the amount to be withdrawn"
       << endl;
  cin >> withdrawAmount;

  if(withdrawAmount < 0)
    {
      cout << endl << "Amount should be greater than 0" << endl << endl;
    }
  else
    {
      accountBalance -= withdrawAmount;
      cout << endl << "$" << withdrawAmount << " withdrawn from your account" << endl << endl;
    }

}
