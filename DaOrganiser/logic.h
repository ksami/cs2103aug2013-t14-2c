#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "task.h"
#include "taskmanager.h"
#include "parser.h"

using namespace std;

class logic {
private:
		void* guiInterface;
        string _userCommand;
        vector<string> commandInput;
		vector<task> taskStorage;
		taskManager p;
public:
        logic();
		logic(void*);
        ~logic();
		void executeProgramme();
		void executeProgramme(bool& toExit);
		
		//bool addTaskStorage();
		vector<task> getTaskStorage();
		//void getCommand();

        bool inputCommand();
		bool checkCommand();
        void parserCommand();
		bool executeCommand();

        void displayCommand();
        void displayVector();
		void setUserCommand(string input); //for testing
};