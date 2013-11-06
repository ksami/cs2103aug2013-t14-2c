#include "stdafx.h"
#include "Facade.h"
#include "Interface.h"

#define SAVE_FILENAME "storage.txt"

Facade::Facade() {
}

Facade::Facade(void* inter) {
	saveFile = new Storage(SAVE_FILENAME);
	saveFile->readAllFromFile(taskStorage);
	p.reupdateIDNumber(taskStorage);
	p.reupdateStatus(taskStorage);
	guiInterface = inter;
}

Facade::~Facade() {
	delete saveFile;
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
	Parser commandline;
	commandInput=commandline.parseString(_userCommand);
}

bool Facade::executeCommand() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	bool checkFlag = false;
	int counter = 0;
	if(_userCommand == "-quit" || _userCommand == "-Quit") 
		return true;
	else
	{
		for(int i=0;i<commandInput.size();i++)
        {
            if(commandInput[i]=="-add"||commandInput[i]=="-update"||commandInput[i]=="-delete"||commandInput[i]=="-read"||commandInput[i]=="-undo"||commandInput[i]=="-redo"||commandInput[i]=="-search"||commandInput[i]=="-all")
                counter++;
        }
 
        if(counter == 1)
        {
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
					guiLogicInterface->updateGuiList();
				}
				else if(commandInput[i]=="-update")
				{
					try {
						bool value = p.updateTask(commandInput,taskStorage);
						if(value)
							guiLogicInterface->toDisplay("Task updated successfully");
						else
							guiLogicInterface->toDisplay("Error found while updating the task");
					}
					catch(const char* except)
					{
						guiLogicInterface->toDisplay(except);
					}

					checkFlag=true;
					guiLogicInterface->updateGuiList();
				}
				else if(commandInput[i]=="-delete")
				{
					try
					{
						if (checkDeleteInput()) {
							bool value = p.deleteTask(commandInput,taskStorage);
							if(value)
								guiLogicInterface->toDisplay("Task deleted successfully");
							else
								guiLogicInterface->toDisplay("Error found while deleting the task");
						}
					}
					catch(const char* except)
					{
						guiLogicInterface->toDisplay(except);
					}
					checkFlag=true;
					guiLogicInterface->updateGuiList();
				}
				else if (commandInput[i]=="-read")
				{
					p.readTask(taskStorage);
					checkFlag=true;
				}
				else if (commandInput[i]=="-undo")
				{
					try
					{
						p.undoTask(taskStorage);
					}
					catch(const char* except)
					{
						guiLogicInterface->toDisplay(except);
					}
					checkFlag=true;
					guiLogicInterface->updateGuiList();
				}
				else if (commandInput[i]=="-redo")
				{
					try
					{
						p.redoTask(taskStorage);
					}
					catch(const char* except)
					{
						guiLogicInterface->toDisplay(except);
					}
					checkFlag=true;
					guiLogicInterface->updateGuiList();
				}
				else if (commandInput[i]=="-search")
				{
					try
					{
						if (checkSearchKey()) {
							p.searchkey(taskStorage,keySearch,searchKey);
						}
					}
					catch(const char* except)
					{
						guiLogicInterface->toDisplay(except);
					}
					checkFlag=true;
					//displayVector();
					guiLogicInterface->displayGuiSearchResults(keySearch);
				}
				else if (commandInput[i]=="-all")
				{
					checkFlag=true;
					guiLogicInterface->toDisplay("Displaying all entries");
					guiLogicInterface->updateGuiList();
				}
			}
		}
		else
			checkFlag = false;
	}
	commandInput.clear();
	keySearch.clear();
	if(checkFlag==false)
	{
		guiLogicInterface->toDisplay("Invalid command entered");
	}
	else
	{
		saveFile->writeAllToFile(taskStorage);
	}
	return false;
}

bool Facade::checkDeleteInput() {
	if (commandInput.size()>1) {
		deleteInput=commandInput.at(1);
		return true;
	}
	else throw "Invalid input";
}

bool Facade::checkSearchKey() {
	if (commandInput.size()>1) {
		searchKey=commandInput.at(1);
		return true;
	}
	else throw "Invalid input";
}

void Facade::displayCommand() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	guiLogicInterface->toDisplay(_userCommand);
	//guiLogicInterface->toDisplay("\n");
}

void Facade::displayVector() {
	Interface* guiLogicInterface = (Interface*) guiInterface;
	int size=keySearch.size();
	for (int i=0;i<size;i++) {
		guiLogicInterface->toDisplay(keySearch.at(i).getDetailsAsString());
		//guiLogicInterface->toDisplay("\n");
	}
}

void Facade::setUserCommand(string input) {
	_userCommand=input;
}