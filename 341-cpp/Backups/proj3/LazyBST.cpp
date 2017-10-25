// File: LazyBST.cpp
//
// CMSC 341 Spring 2017 Project 3
//
// Class implementations for Lazy Binary Search Tree
//

#include "LazyBST.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

LazyBST::LazyBST()
{
  root = NULL;
}

LazyBST::LazyBST(const LazyBST &other)
{
  root = NULL;
  *this = other;
}

LazyBST::~LazyBST()
{
  destroy(root);
}

void LazyBST::destroy(Node *leaf)
{
  if(leaf != NULL)
    {
      destroy(leaf->m_left);
      destroy(leaf->m_right);
      delete leaf;

      leaf = NULL;
    }
}

const LazyBST& LazyBST::operator= (const LazyBST &rhs)
{
  if(&rhs == this) return *this;

  destroy(root);
  
}

void LazyBST::insert(int key)
{
  insert(key, root);
  rebalance(root);
}

void LazyBST::insert(int key, Node *&leaf)
{
  if(leaf == NULL)// no node
    {
      //create node
      leaf = new Node(key);
    }
  //Value at current leaf is greater than the key
  else if(key < leaf->m_data)
    {insert(key, leaf->m_left);}
  //Value at current leaf is less than the key
  else if(key > leaf->m_data)
    {insert(key, leaf->m_right);}
  else;

}

bool LazyBST::remove(int key)
{
  return remove(key, root);
}

bool LazyBST::remove(int key, Node *&leaf)
{
  if(leaf == NULL)
    {return false;}
  //search for the key
  if(key < leaf->m_data)
    {remove(key, leaf->m_left);}
  else if(key > leaf->m_data)
    {remove(key, leaf->m_right);}

  else if(leaf->m_left != NULL && leaf->m_right != NULL)
    {
      leaf->m_data = findMin(leaf->m_right);
      remove(leaf->m_data, leaf->m_right);
    }
  else
    {
      Node *oldNode = leaf;

      leaf = (leaf->m_left != NULL) ? leaf->m_left : leaf->m_right;
      delete oldNode;
    }
  rebalance(root);
  return true;
}


bool LazyBST::find(int key)
{
  return find(key, root);
}

bool LazyBST::find(int key, Node *leaf)
{
  if(leaf == NULL) 
    {return false;}
  //the value is less than the current node's value
  else if( key < leaf->m_data) 
    {return find(key, leaf->m_left);}
  //the value is greater than the current node's value
  else if(key > leaf->m_data)
    {return find(key, leaf->m_right);}
  else 
    {return true;}
}

int LazyBST::findMin(Node *leaf)
{
  if(leaf == NULL)
    {
      return NULL;
    }
  if(leaf->m_left == NULL)
    {return leaf->m_data;}
  else
    {return findMin(leaf->m_left);}
}

int LazyBST::Node::size()
  {
    if(m_left == NULL && m_right == NULL)
      return 1;
    //size of left child if there is one
    int l = m_left ? m_left->size() : 0;
    //size of right child if there is one
    int r = m_right ? m_right->size() : 0;
    
    return 1 + (l + r);
  }

int LazyBST::Node::height()
{
 
  if(m_left == NULL && m_right == NULL)
    return 0;
  //height of left child if there is one
  int l = m_left  ? m_left->height() : 0;
  //height of right child if there is one
  int r = m_right ? m_right->height() : 0;

  
  return 1 + max(l,r);
}

 void LazyBST::inorder()
 {
   inorder(root);
 }

 void LazyBST::inorder(Node *leaf)
 {
   //cout << "hi- ";
   if(leaf != NULL)
     {
       cout << "(";
       if(leaf->m_left)
	 {
	     inorder(leaf->m_left);
	 }

       cout << leaf->m_data << ":" << leaf->height() << ":" << leaf->size();

       if(leaf->m_right)
	 {
	   inorder(leaf->m_right);
	 }
       cout << ")";
     }
   else return;
 }

void LazyBST::rebalance(Node *leaf)
{
  if (leaf != NULL && leaf->m_left != NULL && leaf->m_right != NULL)
	{
		if (((leaf->m_left->size() >= (leaf->m_right->size() * 2))
			&& (leaf->m_left->height() == 4))
			||
			leaf->m_right->size() >= (leaf->m_left->size() * 2)
			&& leaf->m_right->height() == 4)
		{
			cout << "REBALANCING..." << endl;
			int *arr = (int*)calloc(leaf->size(), sizeof(int));
			int arrayEnd = leaf->size() - 1;
			cout << arr[0] << " " << arrayEnd << endl;
			toArray(leaf, arr);
			delete leaf;
			leaf = NULL;
			leaf = toBST(arr, 0, arrayEnd);
		}
      else
	{
	  rebalance(leaf->m_left);
	  rebalance(leaf->m_right);
	}
	}

}

void LazyBST::toArray(Node *leaf, int arr[])
{
	fillArray(leaf, arr, 0);
}

int LazyBST::fillArray(Node* leaf, int arr[], int i)
{
	if (leaf == NULL)
		return i;

	if (leaf->m_left)
	{
		i = fillArray(leaf->m_left, arr, i);
	}
	arr[i] = leaf->m_data;
	i++;

	if (leaf->m_right)
	{
		i = fillArray(leaf->m_right, arr, i);
	}
	return i;
}

LazyBST::Node* LazyBST::toBST(int arr[], int start, int end)
{
	if (start > end)
	{
	//	cout << "hi" << endl;
		return NULL;
	}
	//Get middle element and make it the new root
	int middle = (start + end) / 2;
	cout << middle << " " << arr[middle] << endl;
	Node *newRoot = new Node(arr[middle]);
	//recreate left subtree
	newRoot->m_left = toBST(arr, start, middle - 1);
	//recreate right subtree
	newRoot->m_right = toBST(arr, middle + 1, end);
	return newRoot;

}