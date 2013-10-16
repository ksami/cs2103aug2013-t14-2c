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
	//solved, should work with warning
	travelAllVector(allTask);
	closeOutputStream();
}

void storage::travelAllVector(vector<task> allTask){
	for(int i = 0; i < allTask.size(); i++)
		writeOneToFile(allTask[i]);
}

void storage::writeOneToFile(task t) {
	outputStream << getContentOfTask(t);
}

string storage::getContentOfTask(task t) {
	return t.getDetailsAsString() + "," + t.getStatusAsString() + "," + t.getStartDateAsString() + "," + t.getStartTimeAsString() + "," + t.getEndDateAsString() + "," + t.getEndTimeAsString();
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
	strtok_s(temp, ",", &info[0]);
	while (info[i] != NULL) {
		i++;
		strtok_s(temp, ",", &info[i]);
	}
	return info;
}

task storage::putContentIntoTask(char** info){
	task t;
	//sscanf(info[2],"%4d%2d%2d %2d%2d%2d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday, &tm1.tm_hour,&tm1.tm_min,&tm1.tm_sec);
	//t.assignDateValue(info[2], start);

	return t;
}

void storage::closeInputStream(){
	if(inputStream.is_open()){
		inputStream.close();
	}
}
