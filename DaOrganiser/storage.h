 #pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Task.h"

using namespace std;

class storage{
	private:
		ofstream outputStream;
		ifstream inputStream;
		char* _storageName;

	public:
		storage(char*);
		~storage();
		char* getStorageName();
		bool isSafeToOpenStream();
		void initialOutputStream();
		void writeAllToFile(vector<Task>);
		void travelAllVector(vector<Task>);
		void writeOneToFile(Task);
		string getContentOfTask(Task);
		void closeOutputStream();
		void initialInputStream();
		void readAllFromFile(vector<Task>&);
		Task readOneFromFile();
		Task putContentIntoTask(char**);
		void closeInputStream();
		char** tokenize(char*);
		
};