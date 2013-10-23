#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class parser {
private:
	vector<string> splitString;


public:
	parser();
	~parser();
	vector<string> parseString(string);
};