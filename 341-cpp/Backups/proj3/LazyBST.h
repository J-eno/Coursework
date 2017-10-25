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

  Node(const int &key, Node *lt = NULL, Node *rt = NULL)
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
  // void rebalance();

 private:
  void insert(int key, Node *&leaf);
  bool remove(int key, Node *&leaf);
  bool find(int key, Node *leaf);
  int findMin(Node *leaf);
  void inorder(Node *leaf);
  void toArray(Node *leaf, int arr[]);
  int fillArray(Node *leaf, int arr[], int i);
  Node* toBST(int arr[], int start, int end);
  void rebalance(Node *leaf);
  void destroy(Node *leaf);

 private:
  Node *root;
};

#endif
 
