#include <iostream>
#include<string>
#include <regex>
using namespace std;
#include "Command.h"
#include "LineEditor.h"

//destructor
Command::~Command() {
}



void Command::setFirstLine(int linenum)
{
	firstLine = linenum;
}

//locate last line
void Command::setSecondLine(int linenum)
{
	secondLine= linenum;
}
// get cmd input first line needed
int Command::getFirstLine() const
{
	return firstLine;
}

//get input second cmd line
int Command::getSecondLine() const
{
	return secondLine;
}

//detect cmd
bool Command::isValid() const
{
	return validCmd;
}

//locate current line
void Command::setCurrLine(int linenum)
{
	currline = linenum;
}

//locate last line
void Command::setEndLine(int linenum)
{
	endline = linenum;
}

//get cmd
char Command::getCmd() const
{
	return cmdChar;
}

// initialize everything
void Command::initializ()
{
	firstLine = -1;
	secondLine = -1;
	validCmd= false;
	currline = -1;
	endline= -1;
	cmdChar = 'p';
}

// search line number needed from command line
// by using parse member functions
int Command::findLine(const string& str, int line1, int line2) const
{
	
	if (line1 == 0 && line2 == 0) {
		string temp1 = str.substr();
		//cout << "debug marker temp" << temp1 << endl;
		if (temp1 == "d" || temp1 == "u") {
			int index = 1;
			return index;
		}
	}
	//cout<< "debug marker3 line2 and line1 =="<<line1<<line2;

	if (line1 == line2)
	{	
			//cout << "debug marker1 ==";
			return currline;
		
	}

	string temp = str.substr(line1, line2 - line1);
	if (temp == ".")
	{
		return currline;
	}
	if (temp == "$")
	{
		return endline;
	}

	return atoi(temp.c_str());
};



// parse command line into different parts
// and transfer parts to line editor into memberfunctions
void Command::parse(string & commandLine)
{
	// parse command line 
	// find and get command word
	// produce valid cmd that will be used
	commandLine.erase(remove(commandLine.begin(), commandLine.end(), '\t'), commandLine.end());
	commandLine.erase(remove(commandLine.begin(), commandLine.end(), ' '), commandLine.end());

	validCmd= std::regex_match(commandLine, regex("(((\\d*|\\.|\\$)?\\,(\\d*|\\.|\\$)?)|((\\d*|\\.|\\$)))[rpncaiudw=]?"));

	if (!validCmd)
	{
		return;
	}
	// when cmd have two main parts by ',' seperated int,int char 
	//or , int  or , char
	if (commandLine.compare(",") == 0)
	{
		firstLine = 1;
		secondLine= endline;
		return;
	}

	//default
	if (commandLine.compare("") == 0)
	{
		firstLine = 1;
		secondLine= 1;
		cmdChar = 'd';
		return;
	}
	//get cmd position
	//get cmd range to help find cmd 
	size_t cmdPos = commandLine.find_first_of("airpncudw=");
	size_t cmdEnd = size(commandLine);
	//get cmd
	if (cmdPos != string::npos)
	{
		cmdChar = commandLine.at(cmdPos);
		--cmdEnd;
		//cout << "debug marker " << cmdChar << endl;
	}

	// get line numbers
	size_t seperate = commandLine.find(',');
	if (seperate != string::npos)
	{
		firstLine = findLine(commandLine, 0, seperate);
		secondLine= findLine(commandLine, seperate + 1, cmdEnd);
	}
	else
	{
		firstLine = findLine(commandLine, 0, cmdEnd);
		secondLine= firstLine;
	}
	//cout << "debug marker " << "1st "<<firstLine<<"2nd"<< secondLine<< endl;
}


