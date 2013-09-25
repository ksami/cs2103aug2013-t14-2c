#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
class storage{
	private:
		ofstream outputStream;
      const char STORAGE_NAME[] = "storage.txt";
  
	public:
		void initialOutputStream();
		void writeAllToFile(vector<task> allTask);
		void travelAllVector(vector<task> allTask, void (storage::*work)(task));
		void writeOneToFile(task t);
		char* contentOfTask(task t);
		void closeOutPutStream();
};