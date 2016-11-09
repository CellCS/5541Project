/*
LineKeeper.cpp
LineKeeper class member-function definitions.
*/

#include <iostream>
#include "LineKeeper.h"

//Extracts lines in lename into this LineKeeper's list. 
//It terminates  and  exits  the  program  if  the  le  does  not exist;
// otherwise it constructs a LineKeeper object.

LineKeeper::LineKeeper(const char* filename) {
	FILE* pFile;
	char linewords[100];
	//FILE * fopen ( const char * filename, const char * mode );
	fopen_s(&pFile, filename, "r");
	if (pFile == NULL) {
		perror("Error oepning file");
	}
	else {
		//char * fgets ( char * str, int num, FILE * stream );
		while (fgets(linewords, 100, pFile) != NULL) {
			Line* temp = new Line(linewords);
			list.push_back(linewords);
		}
		fclose(pFile);
	}
}

//swaps m and n if m > n.Adjusts m and n depending on
//how the intervals[m, n] and [1, siz()] overlap.Finally,
//it prints lines m through n to standard output.
void LineKeeper::print(int m, int n) {
	int filesize = list.size();
	// if empty file
	if (filesize == 0) {
		cout << "Error, Empty File";
		return;
	}
	// test m, n, make sure n> m
	//if (m > n) swap(m, n) to make m < n
	if (m > n) {
		int temp = m;
		m = n;
		n = temp;
	}
	// now m < n
	// different out of range conditions
	// less than
	// more than
	if (m<1 || n<1) {
		cout << "invalid range of line numbers from " << m << " to " << n << endl;	
		if (m < 1) m = 1;
		if (n < 1) n = 1;
		cout << "default rage from " << m << " to " << n << " is not in effect "<< endl;
	}

	if (m > filesize || n > filesize) {
		cout << "invalid range of line numbers from " << m << " to " << n << endl;		
		if (m > filesize) m = filesize;
		if (n > filesize) n = filesize;
		cout << "default rage from " << m << " to " << n <<" is not in effect "<< endl;
	}
	
	//then in normal domain or reset m, n in regular domain, print
	for (int lineNum = m; lineNum <= n; lineNum++) {
		cout << "(" << lineNum << ")";
		list.print(lineNum);
	}
	
	cout << "\n" << endl;
}
