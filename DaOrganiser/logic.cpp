#include "stdafx.h"
#include "logic.h"

logic::logic() {
}

logic::~logic() {
}

//GUI's execute programme
void logic::executeProgramme(bool& toExit) {
	if (inputCommand()) {
		parserCommand();
		//displayVector();		//testing
		toExit=executeCommand();
	}
}

//CLI's execute programme
void logic::executeProgramme() {
	bool toExit=false;
	while (!toExit) {
		if (inputCommand()) {
			parserCommand();
			//displayVector();		//testing
			toExit=executeCommand();
		}
	}
}

vector<task> logic::getTaskStorage() {
	return taskStorage;
}

bool logic::inputCommand() {
	toDisplay("Enter instruction: ");
	_userCommand=toGetInput();

	try {
		checkCommand();
		return true;
	} catch (const char* msg) {
		toDisplay(msg);
	}
	return false;
}

bool logic::checkCommand() {
	if (_userCommand.empty()) {
		throw "Command is blank\n";
	}
	return true;
}

void logic::parserCommand() {
	parser commandline;
	commandInput=commandline.parseString(_userCommand);
}

bool logic::executeCommand() {
	if(_userCommand == "-quit" || _userCommand == "-Quit") 
		return true;
	else {
		for(int i=0;i<commandInput.size();i++)
		{
			if(commandInput[i]=="-add")
			{
				bool value = p.createTask(commandInput,taskStorage);
				if(value)
					toDisplay("Task added successfully\n");
				else 
					toDisplay("Error found while adding task\n");
			}
			else if(commandInput[i]=="-update")
			{
				bool value = p.updateTask(commandInput,taskStorage);
				if(value)
					toDisplay("Task updated successfully\n");
				else
					toDisplay("Error found while updating the task\n");
			}
			else if(commandInput[i]=="-delete")
			{
				bool value = p.deleteTask(commandInput,taskStorage);
				if(value)
					toDisplay("Task deleted successfully\n");
				else
					toDisplay("Error found while deleting the task\n");
			}
			else if (commandInput[i]=="-read")
			{
				p.readTask(taskStorage);
			}
		}
	}
	toDisplay("Operation executed successfully\n");
	commandInput.clear();
	return false;
}

void logic::displayCommand() {
	toDisplay(_userCommand);
	toDisplay("\n");
}

void logic::displayVector() {
	int size=commandInput.size();
	for (int i=0;i<size;i++) {
		toDisplay(commandInput.at(i));
		toDisplay("\n");
	}
}

void logic::setUserCommand(string input) {
	_userCommand=input;
}