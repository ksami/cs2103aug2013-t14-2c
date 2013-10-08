#ifndef PROCESS_H
#define PROCESS_H

#include<iostream>
#include<vector>
#include"task.h"

using namespace std;

class process
{
private:
	vector<task> toBeDone; 

public:
	bool createTask(string);
	void readTask();
	bool updateTask();
	bool deleteTask();
};

#endif