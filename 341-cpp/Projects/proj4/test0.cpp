#include "MinMaxHeap.h"
using namespace std;

int main()
{
  MinMaxHeap<int> H(25);
  H.insert(5);
  H.insert(10);
  H.insert(7);
  H.insert(9);
  H.insert(2) ;
  H.insert(16) ;
  H.insert(12) ;
  H.insert(11) ;

  H.dump();

  H.insert(8);
  cout << "After inserting 8\n" ;
  H.dump() ;

  int answer ;
  answer = H.deleteMin() ;
  cout << "\n\nMin item " << answer << " removed from MinMax Heap\n" ;

  H.dump() ;



  answer = H.deleteMax() ;
  cout << "\n\nMax item " << answer << " removed from MinMax Heap\n" ;

  H.dump() ;


  cout << endl << endl << endl << "Initial MinMax Heap\n" ;
  H.dump() ;

  MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H) ;
  cout << "copied MinMax Heap\n" ;
  Gptr->dump();

 H.deleteMax() ;
   Gptr->deleteMin() ;
   cout << "\nH and *Gptr after deleteMax and deleteMin\n" ;
   
   H.dump();
   cout << endl << "Gptr Dump";
   Gptr->dump();
   delete Gptr ;



 MinMaxHeap<int> K1(11) ;
   K1.insert(29) ;
   K1.insert(24) ;
   K1.insert(23) ;
   K1.insert(22) ;
   K1.insert(28) ;
   K1.insert(26) ;
   K1.insert(30) ;
   K1.insert(21) ;
   K1.insert(25) ;
   K1.insert(27) ;

   cout << "\nK1 after inserts\n" ;
   K1.dump();

   MinMaxHeap<int> K2(4) ;
   K2.insert(43) ;
   K2.insert(42) ;
   K2.insert(44) ;
   K2.insert(41) ;

   cout << "\nK2 after inserts\n" ;
   K2.dump();

   K2 = K1 ;
   K1.deleteMax() ;
   K2.insert(57) ;

   cout << "\nK1 & K2 after assignment, etc...\n" ;
   
   cout << "\nK1 Dump\n";
   K1.dump();

   cout << "\nK2 Dump\n";
   K2.dump();

}
