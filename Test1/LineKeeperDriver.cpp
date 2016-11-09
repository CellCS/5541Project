/*
LineKeeperDriver.cpp
the same as in assignment
*/

#include <iostream>
#include"LineKeeper.h"
#include"Line.h"
#include "LinkedList.h"

int main() {

	LineKeeper lk("Input.txt");
	cout << "\n" << "lk.print(2)"       << "\n"; lk.print(2);
	cout << "\n" << "lk.print(13,7)"    << "\n"; lk.print(13,7);
	cout << "\n" << "lk.print(25,5)"    << "\n"; lk.print(25,5);
	cout << "\n" << "lk.print(-25,5)"   << "\n"; lk.print(-25,5);
	cout << "\n" << "lk.print(-25,-85)" << "\n"; lk.print(-25,-85);
	cout << "\n" << "lk.print(25, 50)"  << "\n"; lk.print(25,50);
	cout << "Done !" << endl;
	 
	return 0;
}