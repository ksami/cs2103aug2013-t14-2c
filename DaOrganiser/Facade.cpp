#include "stdafx.h"
#include "Facade.h"
#include "Interface.h"

Facade::Facade() {
}

Facade::Facade(void* inter) {
	guiInterface = inter;
}

Facade::~Facade() {
}

//GUI's execute programme
void Facade::executeProgramme(bool& toExit) {
	if (inputCommand()) {
		parserCommand();
		//displayVector();		//testing
		toExit=executeCommand();
	}
}

//CLI's execute programme
void Facade::executeProgramme() {
	bool toExit=false;
	while (!toExit) {
		if (inputCommand()) {
			parserCommand();
			//displayVector();		//testing
			toExit=executeCommand();
		}
	}
}

vector<Task> Facade::getTaskStorage() {
	return taskStorage;
}

bool Facade::inputCommand() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	//guiLogicInterface->toDisplay("Enter instruction: ");
	_userCommand=guiLogicInterface->toGetInput();

	try {
		checkCommand();
		return true;
	} catch (const char* msg) {
		guiLogicInterface->toDisplay(msg);
	}
	return false;
}

bool Facade::checkCommand() {
	if (_userCommand.empty()) {
		throw "Command is blank";
	}
	return true;
}

void Facade::parserCommand() {
	parser commandline;
	commandInput=commandline.parseString(_userCommand);
}

bool Facade::executeCommand() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	bool checkFlag = false;
	if(_userCommand == "-quit" || _userCommand == "-Quit") 
		return true;
	else {
		for(int i=0;i<commandInput.size();i++)
		{
			if(commandInput[i]=="-add")
			{
				bool value = p.createTask(commandInput,taskStorage);
				if(value)
					guiLogicInterface->toDisplay("Task added successfully");
				else 
					guiLogicInterface->toDisplay("Error found while adding task");
				checkFlag=true;
			}
			else if(commandInput[i]=="-update")
			{
				bool value = p.updateTask(commandInput,taskStorage);
				if(value)
					guiLogicInterface->toDisplay("Task updated successfully");
				else
					guiLogicInterface->toDisplay("Error found while updating the task");
				checkFlag=true;
			}
			else if(commandInput[i]=="-delete")
			{
				bool value = p.deleteTask(commandInput,taskStorage);
				if(value)
					guiLogicInterface->toDisplay("Task deleted successfully");
				else
					guiLogicInterface->toDisplay("Error found while deleting the task");
				checkFlag=true;
			}
			else if (commandInput[i]=="-read")
			{
				p.readTask(taskStorage);
				checkFlag=true;
			}
			else if (commandInput[i]=="-undo")
            {
                p.undoTask(taskStorage);
                checkFlag=true;
            }
		}
	}
	commandInput.clear();
	if(checkFlag==false)
	{
		guiLogicInterface->toDisplay("Invalid command entered");
	}
	return false;
}

void Facade::displayCommand() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	guiLogicInterface->toDisplay(_userCommand);
	//guiLogicInterface->toDisplay("\n");
}

void Facade::displayVector() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	int size=commandInput.size();
	for (int i=0;i<size;i++) {
		guiLogicInterface->toDisplay(commandInput.at(i));
		//guiLogicInterface->toDisplay("\n");
	}
}

void Facade::setUserCommand(string input) {
	_userCommand=input;
}