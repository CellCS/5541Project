#include <iostream>
#include <string>
#include <list>
using namespace std;


#ifndef LINEEDITOR_H
#define LINEEDITOR_H 

class LineEditor {

private:
	list<string> buffer;
	list<string>::iterator Iter;
	string filename;
	int current;
	int endposi;
	bool validateBuffer{false};
	string cmdMsg{ "Entering command mode. "};
	string errorMsg{ "error:  invalid command" }; // status of this command
	bool isModified{ false };
	Command command;
public:

	LineEditor(string&);
	~LineEditor();

	void runCommand(string&);
	void run();

	void setCurr(int i);
	int getCurr();
	int getSize();
	int getendpos();

	void writeToFile();
	void remove(int, int);

	void replace(int, int);
	void push_back();


	void append(int i);
	void insert(int i);


	void moveUp(int i);
	void moveDown(int i);


	//void print(int , int);
	void print(int, int, char);
	void print(int, char);

};

#endif