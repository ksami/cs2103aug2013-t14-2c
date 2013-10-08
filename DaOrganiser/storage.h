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
		bool isSafeToOpenStream();
		void initialOutputStream();
		void writeAllToFile(vector<task>);
		void travelAllVector(vector<task>, void (storage::*work)(task));
		void writeOneToFile(task);

		void closeOutputStream();
		void initialInputStream();
		vector<task> readAllFromFile();
		task readOneFromFile();
		task putContentIntoTask(char**);
		void closeInputStream();
		char** tokenize(char*);
		char* getContentOfTask(task);
		
};