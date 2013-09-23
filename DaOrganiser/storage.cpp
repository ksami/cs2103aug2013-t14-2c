#include "storage.h"

const char STORAGE_NAME[] = "storage.txt";

class task{
};

class storage{
	private:
		ofstream outputStream;
		ifstream inputStream;
	public:
		bool isSafeToOpenStream(){
			return !(outputStream.is_open()||inputStream.is_open());
		}
		void initialOutputStream(){
			if(isSafeToOpenStream()){
				outputStream.open(STORAGE_NAME);
			}
			else{
				closeOutputStream();
				closeInputStream();
			}
		}

		void writeAllToFile(vector<task> allTask){
			initialOutputStream();
			travelAllVector(allTask, writeOneToFile);
			closeOutputStream();
		}

		void travelAllVector(vector<task> allTask, void (storage::*work)(task)){
			for_each(allTask.begin(), allTask.end(), work);
		}

		void writeOneToFile(task t){
			outputStream << getContentOfTask(t);
		}

		char* getContentOfTask(task t){
			//TO-DO
			/*
			t.getHour();
			t.getMin();
			*/
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
				readOneFromFile();
			}
		}
		task readOneFromFile(){
			char* temp = new char[1024];
			inputStream.getline(temp, 1024);
			return putContentIntoTask(temp);
		}
		task putContentIntoTask(char* temp){
			task* t = new task();
			//TO-DO
			/*
				
			*/
		}
		void closeInputStream(){
			if(inputStream.is_open()){
				inputStream.close();
			}
		}
};