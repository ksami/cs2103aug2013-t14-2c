#include "stdafx.h"
#include "Storage.h"
#include "Log.h"
//#include <assert.h>

Storage::Storage(char* storageName) {
	_storageName = storageName;
}

Storage::~Storage() {
}

bool Storage::isSafeToOpenStream() {
	return !(outputStream.is_open()||inputStream.is_open());
}

void Storage::initialOutputStream() {
	if(isSafeToOpenStream()){
		outputStream.open(_storageName);
	}
	else{
		closeOutputStream();
		closeInputStream();
		outputStream.open(_storageName);
	}
}

char* Storage::getStorageName(){
	return _storageName;
}

void Storage::writeAllToFile(vector<Task> allTask) {

	initialOutputStream();
	travelAllVector(allTask);
	closeOutputStream();
}

void Storage::travelAllVector(vector<Task> allTask){
	//outputStream << allTask.size() << "\n";
	for(int i = 0; i < allTask.size(); i++){
		writeOneToFile(allTask[i]);
	}
}

void Storage::writeOneToFile(Task t) {
	outputStream << getContentOfTask(t);
}

string Storage::getContentOfTask(Task t) {
	logging("Task " + t.getDetailsAsString(), LogLevel::Debug);
	return t.getDetailsAsString() + "," + t.getStatusAsString() + "," + t.getStartDateAsString() + "," + t.getStartTimeAsString() + "," + t.getEndDateAsString() + "," + t.getEndTimeAsString() + "\n";
}

void Storage::closeOutputStream(){
	if(outputStream.is_open()){
		outputStream.close();
	}
}

void Storage::initialInputStream(){
	if(isSafeToOpenStream()){
		inputStream.open(_storageName);
	}
	else{
		closeOutputStream();
		closeInputStream();
		inputStream.open(_storageName);
	}
}

void Storage::readAllFromFile(vector<Task> &vt){
	initialInputStream();
	char* temp = new char[1024];
	/*
	inputStream.getline(temp, 1024);
	int noOfTask = atoi(temp);
	
	for(int i = 0; i < noOfTask; i++){
		vt.push_back(readOneFromFile());
	}
	*/
	while(inputStream.getline(temp, 1024)){
		vt.push_back(readOneFromFile(temp));
	}
}

Task Storage::readOneFromFile(char* temp){
	
	//char* temp = new char[1024];
	//inputStream.getline(temp, 1024);
	return putContentIntoTask(tokenize(temp));
}

char** Storage::tokenize(char *temp){
	char** info = new char*[7];
	char* nextToken = NULL;
	int i = 0;
	info[0] = strtok_s(temp, ",", &nextToken);
	while (info[i] != NULL) {
		i++;
		info[i] = strtok_s(NULL, ",", &nextToken);
	}
	return info;
}

Task Storage::putContentIntoTask(char** info){
	Task t;
	date startDate, endDate;
	time_s startTime, endTime;
	//t.assignIDNumber(atoi(info[0]));
	t.assignDetails(info[0]);
	t.assignKind(*info[1]);
	//to-do
	sscanf_s(info[2],"%d/%d/%d",&startDate.day, &startDate.month, &startDate.year);
	t.assignDateValue(startDate, 's');
	//toDisplay(t.getStartDateAsString());

	sscanf_s(info[3],"%d:%d",&startTime.hr, &startTime.min);
	t.assignTimeValue(startTime, 's');	
	//toDisplay(t.getStartTimeAsString());

	sscanf_s(info[4],"%d/%d/%d",&endDate.day, &endDate.month, &endDate.year);
	t.assignDateValue(endDate, 'e');
	//toDisplay(t.getEndDateAsString());

	sscanf_s(info[5],"%d:%d",&endTime.hr, &endTime.min);
	t.assignTimeValue(endTime, 'e');
	//toDisplay(t.getEndTimeAsString());
	return t;
}

void Storage::closeInputStream(){
	if(inputStream.is_open()){
		inputStream.close();
	}
}