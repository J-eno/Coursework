#include "LinkedList.h"
#include "proj3.h"

int main () {
  LinkedList list;
  mainMenu(list);
  return 0;
}

void readFile(LinkedList &list)
{
  fstream theFile;
  char inputFile[20];
  int theInt;
  string theString;

  /*if the linked list is empty*/
  if(list.IsEmpty())
    {
  cout << "What is the file name?:" << endl;
  cin >> inputFile;
  theFile.open(inputFile);
  //if we cannot find the file inputed
  if(!theFile)
    {
      cerr << "Unable to open " << inputFile << endl << endl;
    }
  else
    {
      //while we can read this data in
      while(theFile >> theInt >> theString)
	{
	  list.InsertEnd(theInt, theString);
	}
      cout << "New message loaded" << endl << endl;
    }
  theFile.close();
    }
  /*else if there are already nodes in our list*/
  else
    {
      bool isEnd = 0;
      int choice = 0;
      do
	{
	  while(choice < 1 || choice > 3)
	    {
	      cout << "Do you want to:" << endl
		   << "1. Overwrite the message" << endl
		   << "2. Append the message" << endl
		   << "3. Cancel" << endl;
	      cin >> choice;
	    }
	  
	  switch(choice)
	    {
	    case 1:
	      //if they want to overwrite, clear the list
	      list.Clear();
	      cout << "previous message cleared" << endl << endl;
	      isEnd = 1;
	      break;
	    case 2:
	      //if they want to append, get new file and import the data again
	      cout << "What is the name of the next file?:" << endl;
	      cin >> inputFile;
	      theFile.open(inputFile);
	      if(!theFile)
		{
		  cerr << "Unable to open " << inputFile << endl << endl;
		}
	      else
		{
		  while(theFile >> theInt >> theString)
		    {
		      //add new nodes to the list
		      list.InsertEnd(theInt, theString);
		    }
		  cout << "Rest of message loaded" << endl << endl;
		}
	      theFile.close();
	      isEnd = 1;
	      break;
	    case 3:
	      isEnd = 1;
	      break;
	      
	    }
	}while(isEnd == 0);
    }
}

void mainMenu(LinkedList &list){
  int option = 0;
  bool isExit = 0;
  do {
    do {
      cout << "What would you like to do?: " << endl;
      cout << "1. Load a new encrypted message" << endl;
      cout << "2. Display a raw message" << endl;
      cout << "3. Display an encrypted message" << endl;
      cout << "4. Exit" << endl;
      cin >> option;
    }while(option < 1 || option > 4);

    switch(option){
    case 1:
      readFile(list);
      break;
    case 2:
      displayMessage(list);
      break;
    case 3:
      displayEncrypt(list);
      break;
    case 4:
      exitLinked(list);
      isExit = 1;
    }
  }while(isExit == 0);
}

void displayMessage(LinkedList &list)
{
  if(list.IsEmpty())
    {
      cout << "You haven't loaded an encrypted message yet" << endl << endl;
    }
  else
    {
      //displays encrypted message, sorts message then displays again
      list.Display();
      list.Sort();
      list.Display();
    }
}

void exitLinked(LinkedList &list)
{
  //clear list and deallocate the memory when they want to exit
  list.Clear();
  cout << "Have a nice day!"<< endl;
}

void displayEncrypt(LinkedList &list)
{
  if(list.IsEmpty())
    {
      cout << "You haven't loaded an encrypted message yet" << endl << endl;
    }
  else
    {
      //returns new decrypted list to list2, sorts, and displays it
      LinkedList list2 = list.Decrypt();
      list2.Sort();
      list2.Display();
    }
}
