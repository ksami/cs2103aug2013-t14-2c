#ifndef STORAGE_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "task.h"

using namespace std;

template <class T>
class storage{
	private:
		ofstream outputStream;
		ifstream inputStream;
		char* STORAGE_NAME;

	public:
		storage(char);
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
		task putContentIntoTask(char*);
		void closeInputStream();
		
};

#endif // !STORAGE_H