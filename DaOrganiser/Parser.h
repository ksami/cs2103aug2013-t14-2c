#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Parser {
private:
	vector<string> splitString;


public:
	Parser();
	~Parser();
	vector<string> parseString(string);
};