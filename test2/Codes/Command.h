#include <iostream>
#include<string>
using namespace std;
#ifndef COMMAND_H
#define COMMAND_H


class Command
{
	
private:
	string validCommands{ "=aiprudcnwqw.,$" };
	int firstLine = -1;    // first line address
	int secondLine = -1;    // second line address
	int endline =-1;
	int currline=-1;
	char cmdChar = 0;  // the command character
	string errorMsg{ "invalid command" }; // status of this command
	bool errorFlag{ true };
	bool validCmd{ false };
	int findLine(const string&, int, int) const;
	//void executeCommandLine(string&, string&, string&, LineEditor &);

public:
	Command() = default;
	Command(const Command&) = delete;
	~Command();
	bool bad() const { return errorFlag; }
	int getFirstLine() const;
	int getSecondLine() const;
	void setFirstLine(int);
	void setSecondLine(int);
	bool isValid() const;
	void setCurrLine(int);
	void setEndLine(int);
	char getCmd() const;
	void initializ();// sets member values as shown above
	// breaks down a given commandLine into its component parts
	void parse(string & );

	friend class LineEditor;
};

#endif