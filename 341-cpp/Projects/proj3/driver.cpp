// File: driver.cpp
// 
// Simple test of insertion
// Should see rebalance when inserting 33.

#include <iostream>
using namespace std;

#include "LazyBST.h"

int main() {

	LazyBST T;

	T.insert(70);
	T.inorder(); cout << endl;

	T.insert(30);
	T.inorder(); cout << endl;

	T.insert(110);

	T.inorder(); cout << endl;

	T.insert(14);

	T.insert(7);
	T.insert(25);

	T.insert(3); T.insert(32);
	T.insert(9); T.insert(18);

	T.insert(1); T.insert(44);
	T.insert(12); T.insert(15);
	T.insert(4); T.insert(29);
	T.insert(10); T.insert(21);

	T.inorder(); cout << endl;

	int n;

	n = 44; cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
	n = 32; cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
	n = 29; cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
	n = 21; cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;
	n = 18; cout << "removing " << n << endl; T.remove(n); T.inorder(); cout << endl;

	n = 3;
	cout << "Find " << n << endl;
	if (T.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 4;
	cout << "Find " << n << endl;
	if (T.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 29;
	cout << "Find " << n << endl;
	if (T.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 39;
	cout << "Find " << n << endl;
	if (T.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	n = 301;
	cout << "Find " << n << endl;
	if (T.find(n)) {
		cout << "found = " << n << endl;
	}
	else {
		cout << "did not find = " << n << endl;
	}
	cout << endl;


	// Checking remove...

	n = 21;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 18;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 7;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 13;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 29;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 32;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;

	n = 14;
	cout << "Remove " << n << endl;
	if (T.remove(n)) {
		cout << n << " removed\n";
	}
	else {
		cout << n << " not found\n";
	}
	T.inorder(); cout << endl;


	cout << "Original T:         ";
	T.inorder(); cout << endl;

	// Use copy constructor
	LazyBST *Tptr = new LazyBST(T);

	cout << "Copied T:           ";
	Tptr->inorder(); cout << endl;

	LazyBST T2;

	T2.insert(50);
	T2.insert(25); T2.insert(75);
	// T2.inorder() ; cout << endl ;

	T2 = *Tptr;
	cout << "Second copy:         ";
	T2.inorder(); cout << endl;

	cout << "Delete first copy...\n";
	delete Tptr;

	cout << "Recheck original:    ";
	T.inorder(); cout << endl;
	cout << "Recheck second copy: ";
	T2.inorder(); cout << endl;



	int key = 9999;
	bool ans;
	const char *str;

	ans = T.locate(str = "", key = -1);
	cout << str << ": " << ans << " " << key << endl;

	ans = T.locate(str = "LL", key = -1);
	cout << str << ": " << ans << " " << key << endl;

	ans = T.locate(str = "LLR", key = -1);
	cout << str << ": " << ans << " " << key << endl;

	ans = T.locate(str = "RLLR", key = -1);
	cout << str << ": " << ans << " " << key << endl;


	return 0;
}