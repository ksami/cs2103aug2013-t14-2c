#include "stdafx.h"
#include "print.h"

void toDisplay(string sentence) {
	cout<<sentence;	
}

void toDisplayNum(int number) {
	cout<<number;
}

string toGetInput() {
	string input;
	getline(std::cin, input);
	return input;
}