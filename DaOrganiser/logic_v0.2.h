#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "task_v0.2.h"
#include "taskmanager_v0.2.h"
#include "parser_v0.2.h"
#include "print_v0.2.h"
using namespace std;

class logic {
private:
        string _userCommand;
        vector<string> commandInput;
		vector<task> taskStorage;
		taskManager p;
public:
        logic();
        ~logic();
		void executeProgramme();

		void getCommand();

        bool inputCommand();
		bool checkCommand();
        void parserCommand();
		bool executeCommand();

		bool addTaskStorage();
		bool getTaskStorage();

        void displayCommand();
        void displayVector();
		void setUserCommand(string input); //for testing
};