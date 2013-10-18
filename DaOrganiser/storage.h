 #pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "newtask.h"

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
		void writeAllToFile(vector<task>);
		void travelAllVector(vector<task>);
		void writeOneToFile(task);
		string getContentOfTask(task);
		void closeOutputStream();
		void initialInputStream();
		void readAllFromFile(vector<task>&);
		task readOneFromFile();
		task putContentIntoTask(char**);
		void closeInputStream();
		char** tokenize(char*);
		
};