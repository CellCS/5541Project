/*
Line.cpp
Line class member-function definitions.
*/

#include <iostream>
#include <cstring> 
#include "Line.h"

// define maxum capacity of char array for one line, TA define 400 at lab
#define maxCap 400

// ctor
Line::Line(){}

Line::Line(const char * line)
{
	lineCapacity = maxCap;
	lineLength = strlen(line);
	if (lineLength > (maxCap - 1)) {
		lineCapacity = maxCap * 2; // if linelength is bigger than maxum capacity-1 (need '\0'), just double capacity	
	}
	else {
		lineCapacity = maxCap; // or just defualt capacity
	}

	linePtr = new char[lineLength + 1]; // line just need line length +1 chars incudling last char '\0'
	strcpy(linePtr, line); //copy
}

// ctor
Line::Line(char line) {
	lineCapacity = maxCap;
	lineLength = 1;
	linePtr = new char[lineLength + 1];
	linePtr[0] = line;
	linePtr[lineLength + 1] = '\0';
	lineLength = strlen(linePtr);
	lineCapacity = lineLength + 1;
}

// copy ctor
Line::Line(const Line& line) {
	lineCapacity = line.lineCapacity;
	lineLength = strlen(line.linePtr);
	linePtr = new char[lineLength + 1];
	strcpy(linePtr, line.cstr());
}

//destructor Line
Line:: ~Line() {
	delete[] linePtr;
}

//copy assignment operator voerload
const Line& Line:: operator= (const Line& rhs) {
	if (this == &rhs) return *this;
	//if ( strcmp (this, &rhs) == 0 ) return *this;
	delete[] linePtr; //clear current line
	
	lineCapacity = rhs.lineCapacity;
	lineLength = strlen(rhs.linePtr);
	linePtr = new char[lineLength + 1];// creat new char array with new lenght and \0.
	
	strcpy(linePtr, rhs.cstr());
	return *this;
}


//returns C-style version of this line
const char * Line::cstr() const {
	return linePtr;
}


//returns length of this line
int Line::length() const {
	return lineLength;
}

//returns whether this line is empty
bool Line::empty() const {
	return (lineLength == 0);
	//return (linePtr == '');
}

//returns whether this line is full
bool Line::full() const {
	return (lineCapacity == lineLength + 1);
}

//returns capacity of this line
int Line::capacity() const {
	return lineCapacity;
}

//doubles capacity if this line is full
void Line::resize() {
	if (full()) {
		lineCapacity = lineCapacity * 2;
		char* temp = new char[lineCapacity];
		strcpy(temp, linePtr);
		delete linePtr;
		linePtr = temp;
		temp = nullptr;
	}
}

//appends ch to the end of this line
void Line::push_back(const char & word) {
	if (full()) resize();
	
	linePtr[lineLength] = word;
	lineLength = lineLength + 1;
	linePtr[lineLength] = '\0';
}

//removes the last character in this line
void Line::pop_back() {
	if (empty()) return;
	linePtr[lineLength - 1] = '\0';
	lineLength = lineLength - 1;
}

//prints this line
ostream& operator<< (ostream& out, const Line& line) {
	out << line.linePtr;
	return out;
}

//reads into this line, because maxCap 400 is enough,so here is suppose less than maxCap.
istream& operator>>(istream& in, Line& line) {
	in >> line.linePtr;
	return in;
}