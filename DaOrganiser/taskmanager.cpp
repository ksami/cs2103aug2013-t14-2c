#include "stdafx.h"
#include "TaskManager.h"
#include "Log.h"
TaskManager::TaskManager()
{
	ID=0;
}

TaskManager::~TaskManager()
{
}

char TaskManager::initStatus(Task newTask)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	date temp, edate;
	temp.day = ltm->tm_mday;
	temp.month = 1 + ltm->tm_mon;
	temp.year = (1900 + ltm->tm_year)%100;

	time_s tempTime, etime;
	tempTime.hr = ltm->tm_hour;
	tempTime.min = 1 + ltm->tm_min;

	if(newTask.returnKind() == 'd' || newTask.returnKind() == 't')
	{
		edate = newTask.returnDate('e');
		etime = newTask.returnTime('e');
		if(newTask.checkDate(edate, temp) == 0)
			if(newTask.checkTime(etime, tempTime) == 1)
				return 'm';
			else
				return 'a';
	}
	return 'n';
}

bool TaskManager::createTask(vector<string>splitString,vector<Task> &TaskStorage) 
{ 
    Task newTask; 
    int i;
	bool dateFlagStart, dateFlagEnd, timeFlagStart, timeFlagEnd; 
    string singleWord; 
	logging("create entered", LogLevel::Debug);
  
    dateFlagStart = dateFlagEnd = timeFlagStart = timeFlagEnd = false;

	for(i=0;i<splitString.size();i++) 
	{ 
		if(splitString[i]=="-startdate") { 
			int dateValue=stringToInt(splitString[i+1]);
			dateFlagStart = assignDate(newTask,dateValue,'s');
			if (dateFlagStart==false)
				return false;
		} 
		else if(splitString[i]=="-enddate") { 
			int dateValue=stringToInt(splitString[i+1]);
			dateFlagEnd = assignDate(newTask,dateValue,'e');	
			if (dateFlagEnd==false)
				return false;
		}
		else if(splitString[i]=="-starttime") 
		{ 
			int timeValue=stringToInt(splitString[i+1]);
			timeFlagStart = assignTime (newTask,timeValue,'s');
			if (timeFlagStart==false)
				return false;
		} 
		else if(splitString[i]=="-endtime") 
		{ 
			int timeValue=stringToInt(splitString[i+1]);
			timeFlagEnd = assignTime (newTask,timeValue,'e');
			if (timeFlagEnd==false)
				return false;
		} 
        else if(splitString[i]=="-details") 
        { 
			string details=extractDetails(i,splitString);
			newTask.assignDetails(details); 
		} 
		else if(splitString[i]=="-status") 
		{ 
			newTask.changeStatus(splitString[i+1][0]); 
			if(!newTask.changeStatus(splitString[i+1][0])) 
				return false; 
		} 
	}

	if (dateFlagStart==0 && timeFlagStart==1) {
		assignSystemDate(newTask,'s');
	}
	else if (dateFlagStart==0 && timeFlagStart==0) {
		assignSystemDate(newTask,'s');
		assignSystemTime(newTask,'s');
	}

	// Checking if time and date have logical values
	if((dateFlagStart)&&(dateFlagEnd)) {
		date date1 = newTask.returnDate('s'), date2 = newTask.returnDate('e');
		if(newTask.checkDate(date1, date2) == 1)
			return false;
	}

	if((timeFlagStart)&&(timeFlagEnd)) {
		time_s time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
		if(newTask.checkTime(time1, time2) == 1)
			return false;
	}

	if (dateFlagStart==1 && dateFlagEnd==1 && timeFlagStart==1 &&timeFlagEnd==1) {
		newTask.assignKind('t');
	}
	else if (dateFlagEnd==1 && timeFlagEnd==1) {
		newTask.assignKind('d');
	}
	else {
		newTask.assignKind('f');
	}
 
    // Status assignment occurs here
    char statusAssign = initStatus(newTask);
    newTask.changeStatus(statusAssign);

	updateIDNumber();
	newTask.assignIDNumber(ID);
	insertTaskExecuted(ID,"create");
  
    TaskStorage.push_back(newTask);
	recordRedoCommand.clear();
    return true; 
} 

void TaskManager::readTask(vector<Task> &TaskStorage)
{
	if(TaskStorage.empty()) 
		cout<<"No Tasks exist"<<endl;
	else {
		for(unsigned int i=0;i<TaskStorage.size();i++)
		{
			cout<<"--------------Task"<<i+1<<"--------------"<<endl;;
			TaskStorage[i].displayDetail();
			cout<<endl;
		}
	}
}

bool TaskManager::updateTask(vector<string> splitString,vector<Task> &TaskStorage)
{       
	date d;
	time_s t;
	int i, j;
	bool dateFlagStart, dateFlagEnd, timeFlagStart, timeFlagEnd, statusFlag;
	string singleWord, text;

	dateFlagStart = dateFlagEnd = timeFlagStart = timeFlagEnd = statusFlag = 0;

	// Searchs for the Task number to be updated 
	//------------------------------------------
	i=0;
	while(splitString[i]!="-update")
	{
		i++;
	}
	i++;
	//------------------------------------------
	//please change and refactor the code below 
	if (i>=splitString.size())
		return false;
		// Converts the string to number
	int number = atoi(splitString[i].c_str());
	int pos;
	//if(number<=0||number>ID)
	//	return false;
	try {
		pos=findIDPos(number,TaskStorage);
		insertTaskExecuted(number,"update");
		recordRedoCommand.clear();

		Task newTask = TaskStorage[pos];
		//store the task before it is updated
		storeTask(newTask);

		for(unsigned int i=0;i<splitString.size();i++)
		{
			if(splitString[i]=="-startdate") { 
				int dateValue=stringToInt(splitString[i+1]);
				dateFlagStart = assignDate(TaskStorage[pos],dateValue,'s');
				if (dateFlagStart==false) {
					TaskStorage[pos] = newTask;
					return false;
				}
			} 
			else if(splitString[i]=="-enddate")
			{
				int dateValue=stringToInt(splitString[i+1]);
				dateFlagEnd = assignDate(TaskStorage[pos],dateValue,'e');	
				if (dateFlagEnd==false) {
					TaskStorage[pos] = newTask;
					return false;
				}
			}
			else if(splitString[i]=="-starttime")
			{ 
				int timeValue=stringToInt(splitString[i+1]);
				timeFlagStart = assignTime (TaskStorage[pos],timeValue,'s');
				if (timeFlagStart==false) {
					TaskStorage[pos] = newTask;
					return false;
				}
			} 
			else if(splitString[i]=="-endtime")
			{ 
				int timeValue=stringToInt(splitString[i+1]);
				timeFlagEnd = assignTime (TaskStorage[pos],timeValue,'e');
				if (timeFlagEnd==false) {
					TaskStorage[pos] = newTask;
					return false;
				}
			} 
			else if(splitString[i]=="-details")
			{ 
				string details=extractDetails(i,splitString);
				TaskStorage[pos].assignDetails(details); 
			} 				
			else if(splitString[i]=="-status")
			{
				TaskStorage[pos].changeStatus(splitString[i+1][0]);
				if(!TaskStorage[pos].changeStatus(splitString[i+1][0]))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
				statusFlag = 1;
			}

			if (dateFlagStart==0 && timeFlagStart==1) {
				assignSystemDate(newTask,'s');
			}
			else if (dateFlagStart==0 && timeFlagStart==0) {
				assignSystemDate(newTask,'s');
				assignSystemTime(newTask,'s');
			}

			// Checking if time and date have logical values
			if((dateFlagStart)&&(dateFlagEnd)) {
				date date1 = newTask.returnDate('s'), date2 = newTask.returnDate('e');
				if(newTask.checkDate(date1, date2) == 1)
					return false;
			}

			if((timeFlagStart)&&(timeFlagEnd)) {
				time_s time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
				if(newTask.checkTime(time1, time2) == 1)
					return false;
			}

			if (dateFlagStart==1 && dateFlagEnd==1 && timeFlagStart==1 &&timeFlagEnd==1) {
				newTask.assignKind('t');
			}
			else if (dateFlagEnd==1 && timeFlagEnd==1) {
				newTask.assignKind('d');
			}
			else {
				newTask.assignKind('f');
			}

			if(!statusFlag)
			{
				char statusAssign = initStatus(newTask);
				newTask.changeStatus(statusAssign);
			}
		}
		return true;
	} catch (const char* msg) {
		throw msg;
	}
	return false;
}


bool TaskManager::deleteTask(vector<string> splitString, vector<Task> &TaskStorage)
{
	int deleteTaskID = stringToInt(splitString[1].c_str()); 

	int delPos=findIDPos(deleteTaskID,TaskStorage);

	storeTask(TaskStorage.at(delPos));
	insertTaskExecuted(TaskStorage.at(delPos).getTaskID(),"delete");
	TaskStorage.erase(TaskStorage.begin()+delPos);

	return true;
}

void TaskManager::searchkey(vector<Task> &taskStorage,vector<Task> &searchResults, string key) {
	try {
		if (searchKeyBlank(taskStorage,searchResults,key)) {
			throw "Search completed";
		}
	}
	catch(const char* except){
		throw except;
	}
}

void TaskManager::undoTask(vector<Task> &TaskStorage) {
	try{
		if (checkRecordUndoCommand()) {
			int toUndoID=recordUndoCommand.back();
			int getCommand=toUndoID%10;
			int determinePos;

			if (getCommand==1) {
				determinePos=findIDPos(toUndoID-1,TaskStorage);
				recordRedoTask.push_back(TaskStorage.at(determinePos));
				TaskStorage.erase(TaskStorage.begin()+determinePos);
				recordRedoCommand.push_back(toUndoID);
				recordUndoCommand.pop_back();
			}
			else if (getCommand==2) {
				TaskStorage.push_back(recordUndoTask.back());
				recordUndoTask.pop_back();
				recordRedoCommand.push_back(toUndoID);
				recordUndoCommand.pop_back();
			}
			else if (getCommand==3) {
				determinePos=findIDPos(toUndoID-3,TaskStorage);
				recordRedoTask.push_back(TaskStorage[determinePos]);
				TaskStorage[determinePos]=recordUndoTask.back();
				recordUndoTask.pop_back();
				recordRedoCommand.push_back(toUndoID);
				recordUndoCommand.pop_back();
			}
			throw "Undo successful";
		}
	}
	catch(const char* except){
		throw except;
	}
}

void TaskManager::redoTask(vector<Task> &taskStorage) {
	try {
		if (checkRecordRedoCommand()){
			int toRedoID=recordRedoCommand.back();
			int getCommand=toRedoID%10;
			int determinePos;

			if (getCommand==1) {
				taskStorage.push_back(recordRedoTask.back());
				recordRedoTask.pop_back();
				recordUndoCommand.push_back(toRedoID);
				recordRedoCommand.pop_back();
			}
			else if (getCommand==2) {
				determinePos=findIDPos(toRedoID-2,taskStorage);
				recordUndoTask.push_back(taskStorage[determinePos]);
				recordUndoCommand.push_back(toRedoID);
				taskStorage.erase(taskStorage.begin()+determinePos);
				recordRedoCommand.pop_back();
			}
			else if (getCommand==3) {
				determinePos=findIDPos(toRedoID-3,taskStorage);
				recordUndoTask.push_back(taskStorage[determinePos]);
				taskStorage[determinePos]=recordRedoTask.back();
				recordRedoTask.pop_back();
				recordUndoCommand.push_back(toRedoID);
				recordRedoCommand.pop_back();
			}
			throw "Redo Successful";
		}
	}
	catch(const char* except){
		throw except;
	}
}

bool TaskManager::searchKeyBlank(vector<Task> &taskStorage,vector<Task> &searchResults, string key) {
		size_t found;
		int size=taskStorage.size();
		for (int i=0;i<size;i++) {
			found=taskStorage.at(i).getDetailsAsString().find(key);
			if (found!=std::string::npos)
				searchResults.push_back(taskStorage.at(i));
		}
		if (!searchResults.empty())
			return true;
		else 
			throw "No search results found";
}

void TaskManager::updateIDNumber() {
	ID+=10;
}

void TaskManager::reupdateIDNumber(vector<Task> &taskStorage) {
	int size=taskStorage.size();
	int number=10;
	for (int i=0;i<size;i++) {
		taskStorage.at(i).assignIDNumber(number);
		number+=10;
	}
	ID=number-10;
}

void TaskManager::insertTaskExecuted(int commandNumber, string command) {
	if (command=="create")
		recordUndoCommand.push_back(commandNumber+1);
	else if (command=="delete")
		recordUndoCommand.push_back(commandNumber+2);
	else if (command=="update")
		recordUndoCommand.push_back(commandNumber+3);
}

void TaskManager::storeTask(Task toStore) {
	recordUndoTask.push_back(toStore);
}

void TaskManager::testingRecordCommand() {
	for (unsigned int i=0;i<recordUndoCommand.size();i++) {
		cout<<recordUndoCommand.at(i)<<endl;
	}
}

int TaskManager::findIDPos(int number,vector<Task> TaskStorage) {
	int toReturn;
	if (checkID(number,TaskStorage,toReturn))
			return toReturn;
	else throw "Invalid task ID entered";	
	//if (checkID(number,TaskStorage,toReturn))
	/*	for (unsigned int i=0;i<TaskStorage.size();i++) {
	if (TaskStorage.at(i).getTaskID()==number) 
	toReturn=i;
	}*/
	//return toReturn;
}

bool TaskManager::checkID(int number,vector<Task>TaskStorage,int &toReturn) {
	for (unsigned int i=0;i<TaskStorage.size();i++) {
		if (TaskStorage.at(i).getTaskID()==number) {
			toReturn=i;
			return true;
		}
	}
	return false;

}

bool TaskManager::checkRecordUndoCommand(){
	if (recordUndoCommand.empty())
		throw "No more commands to undo";
	return true;
}


bool TaskManager::checkRecordRedoCommand(){
	if (recordRedoCommand.empty())
		throw "No more commands to redo";
	return true;
}

int TaskManager::stringToInt(string toConvert) {
	int value = atoi(toConvert.c_str());
	 return value;
}

bool TaskManager::assignDate(Task &newTask,int dateValue,char dateOption) {
	date newDate;
	if (!checkDateValue(dateValue)) {
		return false;
	}

	if (!getDayMonthYear(dateValue,newDate)) {
		return false;
	}

	if(!newTask.assignDateValue(newDate, dateOption)) { 
		return false; 
	}
	return true;
}

bool TaskManager::getDayMonthYear(int dateValue, date &newDate) {
	newDate.year = dateValue%100; 
	dateValue/=100; 
	newDate.month = dateValue%100; 
	dateValue/=100; 
	newDate.day = dateValue%100;
	dateValue/=100;

	if (dateValue>0) {
		return false;
	}
	return true;
}

bool TaskManager::checkDateValue(int timeValue) {
	if (timeValue/10000 > 1)
		return true;
	return false;
}

bool TaskManager::assignTime(Task &newTask,int timeValue,char timeOption) {
	time_s newTime;
	if (!checkTimeValue(timeValue)) {
		return false;
	}

	if (!getHourMin(timeValue,newTime)) {
		return false;
	}

	if(!newTask.assignTimeValue(newTime, timeOption)) { 
		return false; 
	}
	return true;
}

bool TaskManager::getHourMin(int timeValue, time_s &newTime) {
	newTime.min = timeValue%100; 
	timeValue/=100; 
	newTime.hr = timeValue%100; 
	timeValue/=100;

	if (timeValue)
		return false;
	return true;
}

bool TaskManager::checkTimeValue(int timeValue) {
	if (timeValue/100 > 1)
		return true;
	return false;
}

string TaskManager::extractDetails(int i, vector<string> splitString) {
	string text = ""; 
	int j;
	j=i+1; 

	// Checks if the first letter of the next string is a '-' 
	// if yes, the loop breaks else the words are assigned to the variable details 

	while(splitString[j][0]!='-') 
	{ 
		text += splitString[j]; 
		text += " "; 
		j++; 
		if(j==splitString.size()) 
			break; 
		if(splitString[j][0]=='-') 
			break; 
	} 

	// Deleting the last extra space in the string  
	text = text.substr(0, text.size()-1);
	return text;
}

void TaskManager::assignSystemTime(Task &newTask, char timeOption) {
	time_t now = time(0);
    tm *ltm = localtime(&now);

	time_s temp;
    temp.hr = ltm->tm_hour;
    temp.min = 1 + ltm->tm_min;

	newTask.assignTimeValue(temp,timeOption);
}

void TaskManager::assignSystemDate(Task &newTask, char dateOption) {
	time_t now = time(0);
    tm *ltm = localtime(&now);

	date temp;
    temp.day = ltm->tm_mday;
    temp.month = 1 + ltm->tm_mon;
    temp.year = (1900 + ltm->tm_year)%100;

	newTask.assignDateValue(temp,dateOption);
}