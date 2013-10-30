#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Task.h"
#include "TaskManager.h"
#include "Parser.h"
#include "Print.h"
using namespace std;

class Facade {
private:
        string _userCommand;
        vector<string> commandInput;
		vector<Task> taskStorage;
		TaskManager p;
public:
        Facade();
		~Facade();
		void runProgramme();

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