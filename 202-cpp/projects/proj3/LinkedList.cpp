#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
  m_head = NULL;
  m_tail = NULL;
}

LinkedList::~LinkedList()
{
  Clear();
}
//name: CreateNode
//pre: Takes in an int and a string
//post: Dynamically creates a new node with a pointer to the next item plus the int
// and string

Node *LinkedList::CreateNode(int newInt, string newPayload)
{
  //create new node when CreateNode is called
  Node *nodePtr = new Node;
  //set it to point to null
  nodePtr->m_next = NULL;
  nodePtr->m_int = newInt;
  nodePtr->m_payload = newPayload;
  return nodePtr;
}

void LinkedList::InsertEnd(int newInt, string newPayload)
{
  Node *newNode = CreateNode(newInt, newPayload);
  //if m_head isn't pointing to anything
  if(m_head == NULL)
    {
      //set the head and the tail to the new node
       m_head = newNode;
       m_tail = newNode;
    }
  else
    {
      //have the tail point to the new node
      m_tail->m_next = newNode;
      m_tail = newNode;
    }
 
}

void LinkedList::Display()
{
  cout << "Payload of list are:" << endl;
  //Make a current node pointer and set equal to head pointer
  Node *curr = m_head;
  //while the current node has a value
  while(curr != NULL)
    {
      cout << curr->m_payload << "->";
      //current node is now whatever current was pointing to
      curr = curr->m_next;
    }
  cout << "END" << endl << endl;
}

void LinkedList::Sort()
{
  int temp;
  string tempStr;
  Node *temp1, *temp2;
  
  for(temp1 = m_head; temp1 != NULL; temp1 = temp1->m_next)
    {
      for(temp2 = temp1->m_next; temp2 != NULL; temp2 = temp2->m_next)
	{
	  //if a bigger int is to the left of a smaller int
	  if(temp1->m_int > temp2->m_int)
	    {
	      //put temp1's data in different temp variables
	      temp = temp1->m_int;
	      tempStr = temp1->m_payload;

	      //make temp1's data now equal to temp2's data 
	      temp1->m_int = temp2->m_int;
	      temp1->m_payload = temp2->m_payload;
	      
	      //make temp2's data now equal to temp1's old data
	      temp2->m_int = temp;
	      temp2->m_payload = tempStr;
	    }
	}
    }

}

bool LinkedList::IsEmpty()
{
  //if there is no data in the head node, the list is empty
  if(m_head == NULL)
    {
      return true;
    }
  else return false;
}


LinkedList LinkedList::Decrypt()
{
  LinkedList decrypted;
  Node *curr;

  //iterating through old linked list
  for(curr = m_head; curr!= NULL; curr = curr->m_next)
    {
      bool isSq = IsPerfectSquare(curr->m_int);
      bool isCb = IsPerfectCube(curr->m_int);
      //if our int is a perfect square
      if(isSq)
	{
	  //insert the square root into our new LinkedList
	  decrypted.InsertEnd(sqrt(curr->m_int),curr->m_payload);
	}
      //if our int is a perfect cube
      else if(isCb)
	{
	  //insert the cube root into the new LinkedList
	  decrypted.InsertEnd(cbrt(curr->m_int), curr->m_payload);
	}
    }

  return decrypted;
}      

bool LinkedList::IsPerfectSquare(int n)
{
  int temp;
  //round the sqrt of given int
  temp = round(sqrt(n));
  //if the sqrt * sqrt equals given int it is a perfect square
  if(temp * temp == n)
    {
       return true;
    }
  else
    {
      return false;
    }
  
}

bool LinkedList::IsPerfectCube(int n)
{
  int temp;
  //round the cbrt of given int
  temp = round(cbrt(n));
  //if the cbrt * cbrt * cbrt equals given int, it is a perfect square
  if (temp * temp * temp == n)
    {
      return true;
    }
  else
    {
      return false;
    }

}

void LinkedList::Clear()
{
  Node *del = m_head;
  //while there is data in our delete pointer node
  while(del != NULL)
    {
      //set data to useless values
      del->m_int = 0;
      del->m_payload = "";
      //m_head is now the next node
      m_head = m_head->m_next;
      //deallocate the old node
      delete del;
      del = m_head;
    }
  m_head = NULL;
  m_tail = NULL;

}
