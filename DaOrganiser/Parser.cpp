#include "stdafx.h"
#include "Parser.h"

//@author A0092075E
Parser::Parser() {
}

Parser::~Parser() {
}

vector<string> Parser::parseString(string userCommand) {
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