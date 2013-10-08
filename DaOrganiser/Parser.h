#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "newtask.h"
#include "newprocess.h"

class Parser
{
public:
	Parser(void);
private:
	process p;
	vector<int> spaceInString;
	vector<string> splitString;
	string singleWord;
public:
	string parseString(string);
};

