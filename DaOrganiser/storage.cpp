#include "storage.h"

char storage::STORAGE_NAME[99] = "storage.txt";

storage::storage() {
}

storage::~storage() {
}

bool storage::isSafeToOpenStream() {
	return !(outputStream.is_open()||inputStream.is_open());
}

void storage::initialOutputStream() {
	if(isSafeToOpenStream()){
		outputStream.open(STORAGE_NAME);
	}
	else{
		closeOutputStream();
		closeInputStream();
	}
}

void storage::writeAllToFile(vector<task> allTask) {
	initialOutputStream();
	travelAllVector(allTask, writeOneToFile);
	closeOutputStream();
}

void storage::travelAllVector(vector<task> allTask, void (storage::*work)(task)){
	for_each(allTask.begin(), allTask.end(), work);
}

void storage::writeOneToFile(task t) {
	outputStream << getContentOfTask(t);
}

char* storage:: getContentOfTask(task t) {
	//TO-DO
	/*
	t.getHour();
	t.getMin();
	*/
}

void storage::closeOutputStream(){
	if(outputStream.is_open()){
		outputStream.close();
	}
}

void storage::initialInputStream(){
	if(isSafeToOpenStream()){
		inputStream.open(STORAGE_NAME);
	}
	else{
		closeOutputStream();
		closeInputStream();
	}
}

vector<task> storage::readAllFromFile(){
	while(!inputStream.eof()){
		readOneFromFile();
	}
}

task storage::readOneFromFile(){
	char* temp = new char[1024];
	inputStream.getline(temp, 1024);
	return putContentIntoTask(temp);
}

task storage::putContentIntoTask(char* temp){
	task* t = new task();
	//TO-DO
	/*

	*/
}

void storage::closeInputStream(){
	if(inputStream.is_open()){
		inputStream.close();
	}
}