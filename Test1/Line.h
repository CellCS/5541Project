/*
Line.h
Line class declaration
prevent multiple inclusions of header
*/

#include <iostream>
#include <cstring> 
using namespace std;

#ifndef LINE_H
#define LINE_H

class Line {

private:
	char* linePtr{ nullptr };
	int lineLength{ 0 };
	int lineCapacity{ 0 };

public:
	Line();
	Line(const char*);
	Line(char);
	Line(const Line&);
	const Line& operator=(const Line& rhs);
	virtual ~Line();
	const char* cstr() const;
	int  length() const;
	bool empty()const;
	bool full() const;
	int  capacity() const;
	void resize();
	void push_back(const char & ch);
	void pop_back();

	friend ostream & operator<< (ostream& out, const Line& line);
	friend istream & operator>> (istream& in, Line& line);
};


#endif