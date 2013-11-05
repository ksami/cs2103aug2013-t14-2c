 #pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Task.h"

using namespace std;

class Storage{
	private:
		ofstream outputStream;
		ifstream inputStream;
		char* _storageName;

	public:
		Storage(char*);
		~Storage();

		void readAllFromFile(vector<Task>&);
		void writeAllToFile(vector<Task>);

		char* getStorageName();
		bool isSafeToOpenStream();
		void initialOutputStream();
		void travelAllVector(vector<Task>);
		void writeOneToFile(Task);
		void taskDetailsBlankedHandler(Task&);
		string getContentOfTask(Task);
		void closeOutputStream();
		void initialInputStream();
		Task readOneFromFile(char*);
		string retrieveRealDetails(char*);
		Task putContentIntoTask(char**);
		void closeInputStream();
		char** tokenize(char*);
		
};