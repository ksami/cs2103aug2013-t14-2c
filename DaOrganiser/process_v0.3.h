/*

Author: Priya


*/

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
	bool createTask(vector<string>);
	void readTask();
	bool updateTask(vector<string>);
	bool deleteTask(vector<string>);
};

#endif