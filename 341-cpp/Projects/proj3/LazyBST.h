// File: LazyBST.h
//
// CMSC 341 Spring 2017 Project 3
//
// Class declarations for Lazy Binary Search Tree
//

#ifndef _LAZYBST_H_
#define _LAZYBST_H_

#include <cstddef>

using namespace std;

class LazyBST
{
struct Node
{
  int m_data;

  Node *m_left;
  Node *m_right;

  //Node Constructor
  Node(const int &key = 0, Node *lt = NULL, Node *rt = NULL)
  {
    m_data = key;
    m_left = lt;
    m_right = rt;

  }

  int height();
  int size();
};

 public:
  LazyBST();
  LazyBST(const LazyBST &other);
  ~LazyBST();
  const LazyBST& operator= (const LazyBST& rhs);
  void insert(int key);
  bool remove(int key);
  bool find(int key);
  void inorder();
  bool locate(const char *position, int &key);

 private:
  void insert(int key, Node *&leaf);
  bool remove(int key, Node *&leaf);
  bool find(int key, Node *leaf);
  int findMin(Node *leaf);
  //perform inorder walk
  void inorder(Node *leaf);
  //converts a BST to an Array
  void toArray(Node *leaf, int arr[]);
  //Fills Array with Nodes from BST
  int fillArray(Node *leaf, int arr[], int i);
  //Converts Array to BST
  Node* toBST(int arr[], int start, int end);
  void rebalance(Node *leaf);
  void destroy(Node *leaf);
  void copyTree(Node *& lhsRoot, Node *rhsRoot);
 private:
  Node *root;
};

#endif
 
