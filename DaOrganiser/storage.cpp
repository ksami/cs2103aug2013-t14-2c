#include "stdafx.h"
#include "storage.h"

storage::storage(char* storageName) {
	_storageName = storageName;
}

storage::~storage() {
}

bool storage::isSafeToOpenStream() {
	return !(outputStream.is_open()||inputStream.is_open());
}

void storage::initialOutputStream() {
	if(isSafeToOpenStream()){
		outputStream.open(_storageName);
	}
	else{
		closeOutputStream();
		closeInputStream();
	}
}

void storage::writeAllToFile(vector<task> allTask) {
	initialOutputStream();
	//TODO
	//writeOneToFile missing argument list
	travelAllVector(allTask, writeOneToFile);
	closeOutputStream();
}

void storage::travelAllVector(vector<task> allTask, void (storage::*work)(task)){
	for_each(allTask.begin(), allTask.end(), work);
}

void storage::writeOneToFile(task t) {
	outputStream << getContentOfTask(t);
}

char* storage::getContentOfTask(task t) {
	//TODO
	//stub
	return "hello i am a stub";
	//return getStartDate() + "," + getStartTime() + "," + getEndDate() + "," + getEndTime();
}

void storage::closeOutputStream(){
	if(outputStream.is_open()){
		outputStream.close();
	}
}

void storage::initialInputStream(){
	if(isSafeToOpenStream()){
		inputStream.open(_storageName);
	}
	else{
		closeOutputStream();
		closeInputStream();
	}
}

vector<task> storage::readAllFromFile(){
	vector<task> vt;
	while(!inputStream.eof()){
		vt.insert(vt.end(), readOneFromFile());
	}
	return vt;
}

task storage::readOneFromFile(){
	char* temp = new char[1024];
	inputStream.getline(temp, 1024);
	return putContentIntoTask(tokenize(temp));
	delete temp;
}

char** storage::tokenize(char *temp){
	char** info = new char*[4];
	int i = 0;
	info[0] = strtok(temp, ",");
	while (info[i] != NULL) {
		i++;
		info[i] = strtok(temp, ",");
	}
	return info;
}

task storage::putContentIntoTask(char** info){
	task t;
	if(info[2] != NULL){
		//TODO
		//stub
		//task* t = new task(info[0], info[1], info[2], info[3]);
		//t.assignDateValue(date, char);
		//t.assignTimeValue(time, char);
		//t.assignKind(char);
		//t.assignDetails(string);
	}
	else if(info[0] != NULL){
		//TODO
		//stub
		//task* t = new task(info[0], info[1]);
	}
	//stub
	return t;
}

void storage::closeInputStream(){
	if(inputStream.is_open()){
		inputStream.close();
	}
}
