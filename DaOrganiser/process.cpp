#include"process.h"

void process::run() {
	string command;
	bool flag=true;

	cout<<"What would you like to do?"<<endl;;
	
	while (flag) {
		getline(cin,command);
		flag=processCommand(command);
	}
}

bool process::processCommand(string command) {
	string commandType;
	scanWords(command);
	commandType=findCommandWords();
	if (commandType=="exit") {
		commandData.clear();
		return false;
	}
	else if (commandType=="add") {
		cout<<"add command function called"<<endl;
		if (processAdd())
			cout<<"Task entered successfully"<<endl;
		commandData.clear();
		return true;
	}
	else {
		cout<<"Invalid command entered"<<endl;
		return true;
	}
}

bool process::processAdd() {
	bool flag=false;
	int size=commandData.size();
	for (int i=0;i<size;i++) {
		if (extractFirstWord(commandData.at(i))=="type") {
			int length=commandData.at(i).size();
			if (commandData.at(i).substr(5,length-5)=="timed") {
				flag=createTask('t');
			}
			else if (commandData.at(i).substr(5,length-5)=="deadline") {
				flag=createTask('d');
			}
			else if (commandData.at(i).substr(5,length-5)=="floating") {
				flag=createTask('f');
			}
		}
	}
	if (flag)
		return true;
	else {
		cout<<"Invalid task type entered"<<endl;
		return false;
	}
}

void process::scanWords(string command) {
	int length=command.size();
	int index=0;
	string temp;
	for (int i=0;i<length;i++) {
		if (command[i]=='-'&&!temp.empty()) {
			trimSpace(temp);
			commandData.push_back(temp);
			temp.clear();
		}
		else if (command[i]=='-') ;
		else {
			temp+=command[i];
		}
	}
	trimSpace(temp);
	commandData.push_back(temp);
	temp.clear();
}

string process::findCommandWords() {
	int size=commandData.size();
	for (int i=0;i<size;i++) {
		if (commandData.at(i)=="add")
			return commandData.at(i);
		else if (commandData.at(i)=="exit")
			return commandData.at(i);
	}
	return "invalid";
}

bool process::createTask(char value)
{
	bool flagKind=false;
	if(value == timed)
	{
		task newTask;
		newTask.assignKind('t');
		//missing some parts
		if (flagKind)
			userTask.push_back(newTask);
	}
	else if (value == deadline)
	{

	}
	else
	{

	}

	return true;
}

void process::readTask()
{
	// I didnt understand this function so just skipped it
	//NIC: this function is gernerally more for the command line interface so as to display out all the task that is stored into the vector
	//as previously discussed
}

bool process::updateTask()
{
	// What exactly to update?
	//NIC: update task function is for jobs that have been completed
	//so by updating it means that the task is completed
	return true;
}

bool process::deleteTask()
{
	// On what basis
	//NIC: this function can be used for undoing 
	//another way to use this function will be when the user specifically wished to delete a task from the vector
	return true;
}

void process::trimSpace(string &line) {
	size_t foundFront=line.find_first_not_of(" ");
	line.erase(0,foundFront);
	int length=line.size();
	size_t foundBack=line.find_last_not_of(" ");
	line.erase(foundBack+1,length-1-foundBack);
}

string process::extractFirstWord(string line) {
	size_t found=line.find_first_of(" ");
	string firstWord=line.substr(0,found);
	return firstWord;
}

void process::check() {
	int size=commandData.size();
	for (int i=0;i<size;i++)
		cout<<commandData.at(i);
}
//NIC: hope the above helps you a little in understanding the different functionality purposes.
//		another thing that i think is missing is the search function, when the user wants to search somethin via name or deadline