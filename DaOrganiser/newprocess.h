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
	bool createTask(string);
	void readTask();
	bool updateTask();
	bool deleteTask();
};