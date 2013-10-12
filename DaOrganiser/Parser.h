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
public:
	vector<task> getTasks();
	string parseString(string);
};

