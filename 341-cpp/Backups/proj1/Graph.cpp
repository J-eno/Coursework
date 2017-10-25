//File: Graph.cpp
//
// CMSC 341 Spring 2017
//
// Header file for Graph
//

#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int n)
{
  if(n <= 0)
    {
      throw out_of_range("Not enough Vectors");
    }
  else
    {
      m_size = n;
      m_adjLists = new AdjListNode*[m_size]();
      for(int i = 0; i < m_size; ++i)
	{
	  m_adjLists[i] = new AdjListNode;
	  m_adjLists[i] = NULL;
      	}
    }
}

Graph::Graph(const Graph &G)
{
  AdjListNode *ptr, *curr;
  for(int i = 0; i < m_size; i++)
    {
      curr = G.m_adjLists[i];
      if(curr == NULL)
	{
	  m_adjLists[i] = NULL;
	}
      else
	{
	  ptr = new AdjListNode(curr->m_vertex);
	  m_adjLists[i] = ptr;
	  curr = curr->next;
	  ptr = ptr->next;
	}
    }
}

Graph::~Graph()
{
  AdjListNode *prev, *curr;

  for(int i = 0; i < m_size; ++i)
    {
      curr = m_adjLists[i];
      while(curr != NULL)
	{
	  prev = curr;
	  curr = curr->next;
	  prev->next = NULL;
	  delete prev;
	}
    }
}

const Graph &Graph::operator= (const Graph &rhs)
{
  if(&rhs == this) return *this;
  delete [] m_adjLists;
  AdjListNode *ptr, *curr;
  for(int i = 0; i < m_size; i++)
    {
      curr = rhs.m_adjLists[i];
      if(curr == NULL)
        {
          m_adjLists[i] = NULL;
        }
      else
        {
          ptr = new AdjListNode(curr->m_vertex);
          m_adjLists[i] = ptr;
          curr = curr->next;
          ptr = ptr->next;
        }
    }
  return *this;
}


int Graph::size()
{
  return m_size;
}

 void Graph::addEdge(int u, int v)
 {
   AdjListNode *newNode = new AdjListNode(v);
   newNode->next = m_adjLists[u];
   m_adjLists[u] = newNode;
   //
   newNode = new AdjListNode(u);
   newNode->next = m_adjLists[v];
   m_adjLists[v] = newNode;
 }

Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr)
{
  m_vertex = v;
  next = ptr;
}

void Graph::dump()
{
  AdjListNode *curr;
  cout << "Dump out graph ( size = " << m_size << " ):" << endl;
  for(int i = 0; i < m_size; ++i)
    {
      cout << "[ " << i << "]: ";
      curr = m_adjLists[i];
      while( curr != NULL)
	{
	  cout << curr->m_vertex << " ";
	  curr = curr->next;
	}
      cout << endl;
    }
}

//Neighbor Iterator Implementation

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd)
{
  m_Gptr = Gptr;
  m_source = v;

  if(m_Gptr == NULL)
    {
      return;
    }

  if(isEnd)
    {
      m_where =  NULL;
      return;
    }
  
  m_where = m_Gptr->m_adjLists[m_source];
}

Graph::NbIterator Graph::nbBegin(int v)
{
  return NbIterator(this, v);
}

Graph::NbIterator Graph::nbEnd(int v)
{
  return NbIterator(this, v, true);
}

bool Graph::NbIterator::operator!=(const NbIterator& rhs)
{
  return(m_Gptr != rhs.m_Gptr 
	 || m_where != rhs.m_where);
}

void Graph::NbIterator::operator++(int dummy)
{
  if( m_Gptr == NULL || m_where == NULL)
    {
      return;
    }

  m_where = m_where->next;
}

int Graph::NbIterator::operator*()
{
  if(m_where == NULL)
    {
      throw out_of_range("NbIterator dereference error.");
    }
  return m_where->m_vertex;
}

// Edge Iterator Implementation

Graph::EgIterator::EgIterator(Graph *Gptr,bool isEnd)
{
  m_Gptr = Gptr;
  if(m_Gptr == NULL)
    {
      return;
    }
  
  if(isEnd)
    {
      m_source = m_Gptr->m_size;
      m_where = NULL;
    }

  m_source = 0;
  m_where = m_Gptr->m_adjLists[0];

  while(m_where == NULL)
    {
      m_source++;
      if(m_source == m_Gptr->m_size)
	{
	  break;
	}
      m_where = m_Gptr->m_adjLists[m_source];
    }
}

Graph::EgIterator Graph::egBegin()
{
  return EgIterator(this);
}

Graph::EgIterator Graph::egEnd()
{
  return EgIterator(this, true);
}

bool Graph::EgIterator::operator!= (const EgIterator& rhs)
{
  return(m_Gptr != rhs.m_Gptr
	 || m_source != rhs.m_source
	 || m_where != rhs.m_where);
}

void Graph::EgIterator::operator++(int dummy)
{
  if(m_Gptr == NULL || m_where == NULL)
    {
      return;
    }

  do
    {
      m_where = m_where->next;
      while( m_where == NULL)
	{
	  m_source++;
	  if( m_source == m_Gptr->m_size)
	    {
	      break;
	    }
	  m_where = m_Gptr->m_adjLists[m_source];
	}
    }
  while( m_source > m_where->m_vertex);
}

pair<int,int> Graph::EgIterator::operator*()
{
  if (m_where == NULL)
    {
      throw out_of_range("EgIterator dereference error");
    }
  return pair<int,int>(m_source, m_where->m_vertex);
}
