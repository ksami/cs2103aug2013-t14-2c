#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class logic {
private:
	string _userCommand;
	vector<string> commandInput;
public:
	logic();
	~logic();
	void inputCommand(string);
	void returnParserCommand(vector<string>);

	void displayCommand();
	void displayVector();
};
