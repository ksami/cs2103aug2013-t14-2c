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
	
	bool checkDateTimeLogic(Task &,char);
	bool checkTime(string);
	bool checkRecordUndoCommand();
	bool checkRecordRedoCommand();
	bool checkID(int,vector<Task>,int&);

	void updateIDNumber();
	void reupdateIDNumber(vector<Task>&);
	void reupdateStatus(vector<Task>&);
	double hoursBtwnTimes(std::tm, std::tm);
	void insertTaskExecuted(int, string);
	void storeTask(Task);
	void testingRecordCommand();
	int findIDPos(int,vector<Task>);
	string extractDetails(int,vector<string>);
	bool searchKeyBlank(vector<Task> &,vector<Task> &, string);
	int searchIDToBeUpdated(vector<string>);
	int stringToInt(string);
	bool checkDateValue(int);
	bool getDayMonthYear(int,date &);
	bool getHourMin(int,time_s &);

	bool assignTime(Task &,int,char);
	bool assignDate(Task &,int,char);
	void assignSystemTime(Task &,char);
	void assignSystemDate(Task &,char);
};

