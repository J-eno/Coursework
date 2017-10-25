#include "Graph.h"
#include <iostream>
#include <utility>
using namespace std;


int main()
{
  // G has 5 vertices numbered 0 thru 4
  Graph G(5) ;
  Graph G2(4);
  // add some edges
  G.addEdge(3,4) ;
  G.addEdge(1,4) ;
  G.addEdge(2,1);
  G.addEdge(0,3) ;
  G.addEdge(0,4) ;

  G2.addEdge(0,1) ;
  G2.addEdge(1,2) ;
  G2.addEdge(2,3) ;
  G2.addEdge(0,3);
  G2.addEdge(3,1);


  // dump out data structure
  G.dump() ;

  // Test neighbor iterator
  //
  Graph::NbIterator nit ;

  cout << "\nThe neighbors of vertex 4 are:\n" ;
  for (nit = G.nbBegin(4); nit != G.nbEnd(4) ; nit++) {
    cout << *nit << " " ;
  }
  cout << endl ;


  // Test edge iterator
  //
  Graph::EgIterator eit ;
  pair<int,int> edge ;

  cout << "\nThe edges in the graph are:\n" ;
  for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {

    edge = *eit ;   // get current edge

    // the two data members of a pair are first and second
    //
    cout << "(" << edge.first << ", " << edge.second << ") " ;

  }
  cout << endl ;
  cout << endl;

  G2.dump();

  // Test neighbor iterator
  //
  Graph::NbIterator nit2 ;

  cout << "\nThe neighbors of vertex 2 are:\n" ;
  for (nit2 = G2.nbBegin(2); nit2 != G2.nbEnd(2) ; nit2++) {
    cout << *nit2 << " " ;
  }
  cout << endl ;

  Graph::EgIterator eit2 ;
  pair<int,int> edge2 ;

  cout << "\nThe edges in the graph are:\n" ;
  for (eit2 = G2.egBegin() ; eit2 != G2.egEnd() ; eit2++) {

    edge2 = *eit2 ;   // get current edge

    // the two data members of a pair are first and second
    //
    cout << "(" << edge2.first << ", " << edge2.second << ") " ;

  }
  cout << endl ;
  cout << endl;

  Graph G3(G2);
  cout << "Graph G3(G2) dump" << endl;
  G3.dump();

  cout << endl;
  cout << "G3 = G dump" << endl;
  G3 = G;
  G3.dump();


  cout << endl;
  cout << "G size: " << G.size() << endl
       << "G2 size: " << G2.size() << endl
       << "G3 size: " << G3.size() << endl;
 return 0;
}
