#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
#include "Task.h"

using namespace std;

class TaskManager
{
private:
	int ID;
	vector<int> recordCommand;
	vector<Task> recordTask;

public:
	TaskManager();
	~TaskManager();
	bool createTask(vector<string>,vector<Task>&);
	void readTask(vector<Task>&);
	bool updateTask(vector<string>,vector<Task>&);
	bool deleteTask(vector<string>,vector<Task>&);
	void undoTask(vector<Task>&);
	
	bool checkRecordCommand();
	bool checkID(int,vector<Task>,int&);
	void updateIDNumber();
	void insertTaskExecuted(int, string);
	void storeTask(Task);
	void testingRecordCommand();
	int findIDPos(int,vector<Task>);
};
