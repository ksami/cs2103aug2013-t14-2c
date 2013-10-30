#include "Facade.h"

Facade::Facade() {
}

Facade::~Facade() {
}

void Facade::runProgramme() {
	bool toExit=false;
	while (!toExit) {
		if (inputCommand()) {
			parserCommand();
			toExit=executeCommand();
		}
	}
}

bool Facade::inputCommand() {
	toDisplay("Enter instruction: ");
	getline(std::cin,_userCommand);

	try {
		checkCommand();
		return true;
	} catch (const char* msg) {
		toDisplay(msg);
	}
	return false;
}

bool Facade::checkCommand() {
	if (_userCommand.empty()) {
		throw "Command is blank\n";
	}
	return true;
}

void Facade::parserCommand() {
	Parser commandline;
	commandInput=commandline.parseString(_userCommand);
}

bool Facade::executeCommand() {
	bool checkFlag=false;
	if(_userCommand == "-quit" || _userCommand == "-Quit") 
		return true;
	else {
		for(int i=0;i<commandInput.size();i++)
		{
			if(commandInput[i]=="-add")
			{
				bool value = p.createTask(commandInput,taskStorage);
				if(value)
					cout<<"Task added successfully"<<endl;
				else 
					cout<<"Error found while adding task"<<endl;
				checkFlag=true;
			}
			else if(commandInput[i]=="-update")
			{
				bool value = p.updateTask(commandInput,taskStorage);
				if(value)
					cout<<"Task updated successfully"<<endl;
				else
					cout<<"Error found while updating the task" <<endl;
				checkFlag=true;
			}
			else if(commandInput[i]=="-delete")
			{
				bool value = p.deleteTask(commandInput,taskStorage);
				if(value)
					cout<<"Task deleted successfully"<<endl;
				else
					cout<<"Error found while deleting the task"<<endl;
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
	if (checkFlag==false)
		cout<<"Invalid command entered"<<endl;
	return false;
}

void Facade::displayCommand() {
	toDisplay(_userCommand);
	toDisplay("\n");
}

void Facade::displayVector() {
	int size=commandInput.size();
	for (int i=0;i<size;i++) {
		toDisplay(commandInput.at(i));
		toDisplay("\n");
	}
}

void Facade::setUserCommand(string input) {
	_userCommand=input;
}