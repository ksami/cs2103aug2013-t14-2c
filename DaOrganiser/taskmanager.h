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
	vector<int> recordUndoCommand;
	vector<Task> recordUndoTask;
	vector<int>recordRedoCommand;
	vector<Task> recordRedoTask;

public:
	TaskManager();
	~TaskManager();
	char initStatus(Task);
	bool createTask(vector<string>,vector<Task>&);
	void readTask(vector<Task>&);
	bool updateTask(vector<string>,vector<Task>&);
	bool deleteTask(vector<string>,vector<Task>&);
	void searchkey(vector<Task> &,vector<Task> &,string);
	void undoTask(vector<Task>&);
	void redoTask(vector<Task>&);
	
	bool checkRecordUndoCommand();
	bool checkRecordRedoCommand();
	bool checkID(int,vector<Task>,int&);
	void updateIDNumber();
	void reupdateIDNumber(vector<Task>&);
	void insertTaskExecuted(int, string);
	void storeTask(Task);
	void testingRecordCommand();
	bool searchKeyBlank(vector<Task> &,vector<Task> &, string);
	int findIDPos(int,vector<Task>);

	int stringToInt(string);
	bool assignDate(Task &,int,char);
	bool getDayMonthYear(int,date &);
	bool assignTime(Task &,int,char);
	bool getHourMin(int,time_s &);
};

