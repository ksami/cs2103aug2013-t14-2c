#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
class storage{
	private:
		ofstream outputStream;
	public:
		void initialOutputStream();
		void writeAllToFile(vector<task>);
		void travelAllVector(vector<task>, void (storage::*work)());
		void writeOneToFile(task);
		char* contentOfTask(task);
		void closeOutPutStream();
		void initialInputStream();
		vector<task> readAllFromFile();
		task readOneFromFile();
		task putContentIntoTask(char*);
		void closeInputStream();
};