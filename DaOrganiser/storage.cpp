#include "stdafx.h"
#include "storage.h"
#include <assert.h>

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
		outputStream.open(_storageName);
	}
}

char* storage::getStorageName(){
	return _storageName;
}

void storage::writeAllToFile(vector<Task> allTask) {

	initialOutputStream();
	travelAllVector(allTask);
	closeOutputStream();
}

void storage::travelAllVector(vector<Task> allTask){
	outputStream << allTask.size() << "\n";
	for(int i = 0; i < allTask.size(); i++){
		writeOneToFile(allTask[i]);
	}
}

void storage::writeOneToFile(Task t) {
	outputStream << getContentOfTask(t);
}

string storage::getContentOfTask(Task t) {
	return t.getDetailsAsString() + "," + t.getStatusAsString() + "," + t.getStartDateAsString() + "," + t.getStartTimeAsString() + "," + t.getEndDateAsString() + "," + t.getEndTimeAsString() + "\n";
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
		inputStream.open(_storageName);
	}
}

void storage::readAllFromFile(vector<Task> &vt){
	initialInputStream();
	char* temp = new char[1024];
	inputStream.getline(temp, 1024);
	int noOfTask = atoi(temp);
	for(int i = 0; i < noOfTask; i++){
		vt.push_back(readOneFromFile());
	}
}

Task storage::readOneFromFile(){
	char* temp = new char[1024];
	inputStream.getline(temp, 1024);
	return putContentIntoTask(tokenize(temp));
}

char** storage::tokenize(char *temp){
	char** info = new char*[6];
	char* nextToken = NULL;
	int i = 0;
	info[0] = strtok_s(temp, ",", &nextToken);
	while (info[i] != NULL) {
		i++;
		info[i] = strtok_s(NULL, ",", &nextToken);
	}
	return info;
}

Task storage::putContentIntoTask(char** info){
	Task t;
	date startDate, endDate;
	time_s startTime, endTime;
	t.assignDetails(info[0]);
	t.assignKind(*info[1]);
	sscanf_s(info[2],"%4d/%2d/%2d",&startDate.year, &startDate.month, &startDate.day);
	t.assignDateValue(startDate, 's');
	//toDisplay(t.getStartDateAsString());

	sscanf_s(info[3],"%2d:%2d",&startTime.hr, &startTime.min);
	t.assignTimeValue(startTime, 's');	
	//toDisplay(t.getStartTimeAsString());

	sscanf_s(info[4],"%4d/%2d/%2d",&endDate.year, &endDate.month, &endDate.day);
	t.assignDateValue(endDate, 'e');
	//toDisplay(t.getEndDateAsString());

	sscanf_s(info[5],"%2d:%2d",&endTime.hr, &endTime.min);
	t.assignTimeValue(endTime, 'e');
	//toDisplay(t.getEndTimeAsString());
	return t;
}

void storage::closeInputStream(){
	if(inputStream.is_open()){
		inputStream.close();
	}
}