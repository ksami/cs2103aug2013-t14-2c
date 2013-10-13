#include "logic.h"

logic::logic() {
}

logic::~logic() {
}

void logic::inputCommand(string command) {
	if (!_userCommand.empty())
		_userCommand.clear();
	_userCommand=command;
}

void logic::returnParserCommand(vector<string> temp) {
	//to create a parse class and get the parse vector from the parser class
	commandInput=temp;
}

void determineCommand() {
	//this function reads in the parse string and calls to the taskManager class to create the respective class
	//already written by Priyaa
}

void logic::displayCommand() {
	cout<<_userCommand<<endl;
}

void logic::displayVector() {
	int size=commandInput.size();
	for (int i=0;i<size;i++) {
		cout<<commandInput.at(i)<<endl;
	}
}