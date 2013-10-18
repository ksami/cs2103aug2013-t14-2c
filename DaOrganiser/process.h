#ifndef PROCESS_H
#define PROCESS_H

#include<iostream>
#include<vector>
#include <string>
#include"task.h"

using namespace std;

class process
{
private:
	vector<task> userTask; 
	vector<string> commandData;

public:
	void run();
	bool processCommand(string);
	bool processAdd();
	void scanWords(string);
	string findCommandWords();
	bool createTask(char);
	void readTask();
	bool updateTask();
	bool deleteTask();
	void trimSpace(string&);
	string extractFirstWord(string);
	void check();
};

#endif