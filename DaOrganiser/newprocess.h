#pragma once

#include <iostream>
#include <vector>
#include "newtask.h"

using namespace std;

class process
{
private:
	vector<task> toBeDone; 

public:
	vector<task> getTasks();

	bool createTask(vector<string> splitString);
	void readTask();
	bool updateTask();
	bool deleteTask();
};