#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

class storage {
private:
	ofstream outputStream;
	ifstream inputStream;
	static char STORAGE_NAME[99]; 

public:
	storage();
	~storage();
	bool isSafeToOpenStream();
	void initialOutputStream();
	void writeAllToFile(vector<task> allTask);
	void travelAllVector(vector<task> allTask, void (storage::*work)(task));
	void writeOneToFile(task t);
	char* getContentOfTask(task t);
	void closeOutputStream();
	void initialInputStream();
	vector<task> readAllFromFile();
	task readOneFromFile();
	task putContentIntoTask(char* temp);
	void closeInputStream();	
};