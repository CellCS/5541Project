/*
LineKeeper.h
LineKeeper class declaration
prevent multiple inclusions of header
*/

#include <iostream>
#include "LinkedList.h"

#ifndef LINEKEEPER_H
#define LINEKEEPER_H

class LineKeeper {

private:
	LinkedList list{};

public:
	LineKeeper(const char* filename);
	void print(int m, int n = 1);
};

#endif
