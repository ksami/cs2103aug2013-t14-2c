#include "storage.h"

template <class T>
class storage{

	storage(char storageName) {
		STORAGE_NAME = new char();
		STORAGE_NAME = storageName;
	}

	~storage() {
		delete STORAGE_NAME;
	}

	bool isSafeToOpenStream() {
		return !(outputStream.is_open()||inputStream.is_open());
	}

	void initialOutputStream() {
		if(isSafeToOpenStream()){
			outputStream.open();
		}
		else{
			closeOutputStream();
			closeInputStream();
		}
	}

	void writeAllToFile(vector<task> allTask) {
		initialOutputStream();
		travelAllVector(allTask, writeOneToFile);
		closeOutputStream();
	}

	void travelAllVector(vector<task> allTask, void (storage::*work)(task)){
		for_each(allTask.begin(), allTask.end(), work);
	}

	void writeOneToFile(task t) {
		outputStream << getContentOfTask(t);
	}

	char* getContentOfTask(task t) {
		return getStartDate() + "," + getStartTime() + "," + getEndDate() + "," + getEndTime();
	}

	void closeOutputStream(){
		if(outputStream.is_open()){
			outputStream.close();
		}
	}

	void initialInputStream(){
		if(isSafeToOpenStream()){
			inputStream.open(STORAGE_NAME);
		}
		else{
			closeOutputStream();
			closeInputStream();
		}
	}

	vector<task> readAllFromFile(){
		while(!inputStream.eof()){
			vector<task> vt = new vector<task>();
			vt.insert(vt.end, readOneFromFile();)
		}
		return vt;
	}

	task readOneFromFile(){
		char* temp = new char[1024];
		inputStream.getline(temp, 1024);
		return putContentIntoTask(tokenize(temp));
	}

	char** tokenize(char *temp){
		char** info = new char*[4];
		int i = 0;
		info[0] = strtok(temp, ",");
		while (info[i] != NULL) {
			i++;
			info[i] = strtok(temp, ",");
		}
		return info;
	}

	task putContentIntoTask(char** info){
		if(info[2] != null){
			task* t = new task(info[0], info[1], info[2], info[3]);
		}
		else if(info[0] != null){
			task* t = new task(info[0], info[1]);
		}
		reutnr t;
	}

	void closeInputStream(){
		if(inputStream.is_open()){
			inputStream.close();
		}
	}
}