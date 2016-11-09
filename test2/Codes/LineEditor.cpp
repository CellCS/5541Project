#include <iostream>
#include <fstream>
#include<istream>
#include <string>
#include <list>
#include<iomanip>
using namespace std;
#include "Command.h"
#include "LineEditor.h"
#include <iterator>



	LineEditor::LineEditor(string& filename) :filename{ filename } {}

	LineEditor:: ~LineEditor() {}

	// main run function
	//detect user inpute and prompt user actions
	//direct steps and inputs mail whole progress

	void LineEditor::run()
	{
		fstream infile(filename);
		//detect input filename and search
		// if there is no related filename, show new file but not write
		if (!infile)
		{
			cout << "Unable to open file " + filename << endl;
			cout << "\"" << filename << "\" " << "\[New File\]" << endl;
			cout << cmdMsg <<'\n'<<":";
			
		}
		else{
			//if there is realted file
			//first read lines to buffer
			//and show total lines information
			string fileLines;
			while (getline(infile, fileLines))
			{
				buffer.push_back(fileLines);
			}
			cout << filename << '\n';
			for (auto it = begin(buffer); it != end(buffer); it++) {
				cout << *it << '\n';
			}
			cout << endl;

			//then prompt user to input command
			cout << "\"" << filename << "\" " << size(buffer) << " lines" << '\n';
			cout << cmdMsg << '\n' << ":";
			current = buffer.size();
			infile.close();
		}

		//detect imput as command line
		//and check command words
		// prompt save change step when quit imput
		string cmd;
		getline(cin, cmd);

		while (cin.good() && cmd != "q")
		{
			runCommand(cmd);
			cout << ":";
			getline(cin, cmd);
		}
		// prompt user to choose
		//save all message lines
		//or give up
		cout << "Save changes to " << filename << " \(y\/n\) ";
		getline(cin, cmd);


		while (cin.good() && cmd != "y" && cmd != "Y" && cmd != "n" && cmd != "N")
		{
			cout << "Please type y or n" << '\n';
			cout << "Save changes to " << filename << " \(y\/n\) ";
			getline(cin, cmd);
		}
		if (cmd == "n" || cmd == "N") return;
		if (cmd == "y" || cmd == "Y")
		{
			cout << "\"" << filename << "\" " << buffer.size() << " lines" << endl;
			writeToFile();
		}
	}

	// write to file by ofstream at last
	void LineEditor::writeToFile() {
		if (filename.empty())
			getline(cin, filename);
		ofstream fout(filename, ios::out);
		string line;
		for (auto it = begin(buffer); it != end(buffer); it++) {
			fout << *it<<'\n';
		}
		cout << endl;
		fout.close();
		current = size(buffer);

	}

	//initialize command and buffer, and parse input command lines, mainly should be some possibilities
	// and use parse to get cmd
	// and commnad requirments
	void LineEditor::runCommand(string & commandLine)
	{
		command.setCurrLine(current);
		command.setEndLine(size(buffer));
		command.parse(commandLine);
		if (!command.isValid())
		{
			cout << errorMsg << endl;
			return;
		}

		//detect cmd input and find related cmd, also need parse inpute 
		if (buffer.empty() && command.getCmd() != 'a' && command.getCmd() != 'i')
		{
			cout << "error: file empty - enter 'q' to quit, 'a' to append, or 'i' to insert" << endl;
			return;
		}
		//detect right buffer ranges
		bool validateBuffer = (command.getFirstLine() > 0 && command.getFirstLine() <= command.getSecondLine() && command.getSecondLine() <= size(buffer));
		if (!validateBuffer && (command.getCmd() == 'r' || command.getCmd() == 'p' || command.getCmd() == 'n' || command.getCmd() == 'c'))
		{
			std::cout << "error: invalid range " << command.getFirstLine() << " through " << command.getSecondLine() << std::endl;
			return;
		}
		//limit condistion after get right buffer ranges
		validateBuffer = (0 <= command.getFirstLine() && command.getSecondLine() <= size(buffer));
		if (!validateBuffer && (command.getCmd() == 'i' || command.getCmd() == 'a'))
		{
			std::cout << "error: invalid address " << command.getSecondLine() << std::endl;
			return;
		}

		// based on Command Line Interpretation, chose corresponding memeber functions
		switch (command.getCmd())
		{
		//cout<<"cmd char"<<command.getCmd();
		case 'a':
			append(command.getSecondLine());
			isModified = true;
			break;
		case 'i':
			insert(command.getSecondLine());
			isModified = true;
			break;
		case 'r':
			remove(command.getFirstLine(), command.getSecondLine());
			isModified = true;
			break;
		case 'p':
			print(command.getFirstLine(), command.getSecondLine(), 'p');
			break;
		case 'n':
			print(command.getFirstLine(), command.getSecondLine(), 'n');
			break;
		case 'c':
			replace(command.getFirstLine(), command.getSecondLine());
			isModified = true;
			break;
		case 'u':
			moveUp(command.getSecondLine());
			break;
		case 'd':
			moveDown(command.getSecondLine());
			break;
		case 'w':
			writeToFile();
			isModified = false;
			break;
		case '=':
			cout << current << endl;
		default:
			break;
		}
		command.initializ();
	}

	//locate current index following user input
	// if input correct in buffer ranges, move current to target position
	// if not, show error message, and set current to max or mini position
	void LineEditor::setCurr(int i) {
		int temp = current + i;
		if (temp = 1) {
			current = 1;
		}
		else if (temp < 1) {
			current = 1;
			cout << "BOF reached" << endl;
		}
		else if (temp > size(buffer)) {
			current = size(buffer);
			cout << "EOF reached" << endl;
		}
		else if(temp = size(buffer)){
		current = size(buffer);
		}
		else {
			current = temp;
		}
					
	}

	// finde curent line num
	int LineEditor::getCurr() {
		return current;
	}

	//remove from lnum1 line to lnum2 line
	void LineEditor::remove(int lnum1, int lnum2) {
		auto iter = buffer.begin();
		for (size_t i = 1; i != lnum1; ++iter, ++i);

		for (size_t j = lnum1; j <= lnum2; ++j)
			iter = buffer.erase(iter);

		if (iter != buffer.end())
			current = lnum1;
		else
			current = lnum1 - 1;

	}

	// repalce function, need to locate first input line index
	//using iter to locate the first one
	// set current to last line after replace if it in buffer range
	void LineEditor::replace(int lnum1, int lnum2)
	{
		string s1;
		string s2; 
		cout << "change what? ";
		getline(cin, s1);
		cout << setw(4)<<"    " << "to what? ";
		getline(cin, s2);
		auto iter = buffer.begin();
		for (int i = 1; i != lnum1; ++iter, ++i);
		for (int i = lnum1; i <= lnum2; ++iter, ++i)
		{
			size_t charPosi = iter->find(s1);
			//cout << "debug marker charP in replace " << charPosi;
			while (charPosi != std::string::npos)
			{
				iter->replace(charPosi, s1.length(), s2);
				charPosi = iter->find(s1, charPosi + s2.length());
				current = i;
			}
		}
		current = lnum2;
		//cout << "debug marker "<< curent<<"replace1";
	}

	//push back in buffer with input, not using this function
	void LineEditor::push_back() {
		string line;
		getline(cin, line);
		while (cin.good() && line != ".")
		{
			buffer.push_back(line);
			getline(cin, line);
		}
		current = size(buffer);
		// appent (size(buffer));
	}

	//append after i line
	//set curent to the end line
	void LineEditor::append(int i) {
		if (i < buffer.size())
		{
			insert(i + 1);
		}
		else
		{
			string line;
			getline(cin, line);
			while (cin.good() && line != ".")
			{
				buffer.push_back(line);
				getline(cin, line);
			}
			current = size(buffer);
		}
	}

	// insert in front of i line
	void LineEditor::insert(int i) {

		if (empty(buffer)) {
			i = 1;
		}
		auto iter = buffer.begin();
		for (size_t j = 1; j < i; ++iter, ++j);
		int linetemp = i;
		string line;
		getline(cin, line);
		while (cin.good() && line != ".")
		{
			buffer.insert(iter, line);
			i++;
			getline(cin, line);
		}
		current = i-1;
	}


	void LineEditor::moveUp(int i) {
		//cout << "i =" << i;
		
		if (i >= size(buffer)||(current-i<=0) ){
			cout << "BOF reached jhhj" << endl;
			current = 1;
		}
		else {
			current = current - i;
		}
		
	}

	void LineEditor::moveDown(int i) {
		//cout << "debug marker i =" << i;
		//cout << "debug marker size buffer " << size(buffer);
		if (i > (size(buffer)-current)) {
			cout << "EOF reached hhh" << endl;
			current = size(buffer);
		}
		else {
			current = current + i;
		}
		
	}

	// print function from begin index to end index 
	// two different requirments
	// print line index of n or not p 
	//default is no line index, p
	void LineEditor::print(int ibegin, int iend, char cmd='p') {

		if (buffer.empty()) {
			cout << "This is no lines in file" << endl;
			current = -1;
			return;
		}

		if (ibegin < 1) {
			cout << "stare line could not less then the first line";
			ibegin = 1;
		}

		if (iend > size(buffer) ){
			cout << "Sorry, there are only " << size(buffer) << " in the file";
			iend = size(buffer);
		}

		auto iter = buffer.begin();
		for (int i = 1; i != ibegin && iter != buffer.end(); ++iter, ++i);
		//cout<< "marker locate line number"<<ibegin<<" and  ";
		for (int i = ibegin; i <= iend && iter != buffer.end(); ++iter, ++i)
		{
			if (cmd == 'n') {
				cout << i << "  ";
			}
			cout << *iter<<'\n';
		}
		//cout<< "finish print line";
		//cout << endl;
		current = iend;
		
	}


// add one function when only type one num
	void LineEditor::print(int index, char cmd) {
		if (index = 0 || buffer.empty()) {
			//cout << "Sorry, there is no line you asked to print" << endl;
			index = 1;
		}
		if (index > size(buffer)) {
			// if index > max line number of buffer, change index to the last line
			index = size(buffer);
		}
		auto iter = buffer.begin();

		//move inter to index line
		for (int i = 1; i != index && iter != buffer.end(); ++iter, ++i);
		for (int i = index; iter != buffer.end(); ++iter, ++i)
		{
			if (cmd == 'n') {
				cout << i << "  ";
			}
			cout << *iter;
		}
		iter = --buffer.end();
		current = size(buffer);
	}

	// get end line 
	int LineEditor::getendpos() {
		int i = 0;
		if (! buffer.empty()) {
			i = size(buffer);
		}
		else {
			cout << "There is no any lines in file" << endl;		
		}
		return i;
	}

	//beffer simply buffer.size()
	// or size(buffer)
	int LineEditor::getSize() {
		return buffer.size();
	}