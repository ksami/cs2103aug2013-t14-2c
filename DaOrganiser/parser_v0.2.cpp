#include "parser_v0.2.h"

parser::parser() {
}

parser::~parser() {
}

vector<string> parser::parseString(string userCommand) {
	string singleWord;
	istringstream toSplitString(userCommand);

	do
	{
		toSplitString>>singleWord;
		splitString.push_back(singleWord);
	}while(toSplitString);

	splitString.pop_back();
	return splitString;
}