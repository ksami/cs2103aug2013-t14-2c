#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Task.h"
#include "TaskManager.h"
#include "Parser.h"
#include "Storage.h"

using namespace std;

class Facade {
private:
		void* guiInterface;
        string _userCommand;
		string searchKey;
        vector<string> commandInput;
		vector<Task> taskStorage;
		vector<Task> keySearch;
		TaskManager p;
		Storage* saveFile;
public:
        Facade();
		Facade(void*);
        ~Facade();
		void executeProgramme();
		void executeProgramme(bool& toExit);
		
		vector<Task> getTaskStorage();

        bool inputCommand();
		bool checkCommand();
        void parserCommand();
		bool executeCommand();
		
		bool checkSearchKey();
        void displayCommand();
        void displayVector();
		void setUserCommand(string input); //for testing
};