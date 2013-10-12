#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class storage {
private:
	ifstream inputFile;
	ofstream fileVector;
	vector<string> temp;	//to be change to vector<task>

public:
	storage(): inputFile("input.txt", ios::in), fileVector ("storage.txt", ios::out | ios::trunc) {}
	~storage();
	void checkStatusInputFile();
	void checkStatusOutputFile();
	void readFile();
	void writeToFile(string);
	void getVector();
	void displayString(); //testing
};