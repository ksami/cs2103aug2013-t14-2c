#include "stdafx.h"
#include "TaskManager.h"
#include "Log.h"

//difference in hours before a task is considered approaching its deadline
#define APPROACHING_DIFFERENCE 48.0

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
	tempTime.min = ltm->tm_min;

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
	bool dateFlagStart, dateFlagEnd, timeFlagStart, timeFlagEnd; 
	string singleWord; 

	dateFlagStart = dateFlagEnd = timeFlagStart = timeFlagEnd = false;

	for(unsigned int i=0;i<splitString.size();i++) 
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
			if (!checkTime(splitString[i+1])) {
				return false;
			}
			int timeValue=stringToInt(splitString[i+1]);
			timeFlagStart = assignTime (newTask,timeValue,'s');
			if (timeFlagStart==false)
				return false;
		} 
		else if(splitString[i]=="-endtime") 
		{ 
			if (!checkTime(splitString[i+1])) {
				return false;
			}
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

	if (dateFlagStart==1 && dateFlagEnd==1 && timeFlagStart==1 &&timeFlagEnd==1) {
		newTask.assignKind('t');
		if (!checkDateTimeLogic(newTask,'t')) {
			return false;
		}
	}
	else if (dateFlagEnd==1 && timeFlagEnd==1) {
		newTask.assignKind('d');
		if (!checkDateTimeLogic(newTask,'d')) {
			return false;
		}
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
			//TaskStorage[i].displayDetail();
			cout<<endl;
		}
	}
}

bool TaskManager::updateTask(vector<string> splitString,vector<Task> &TaskStorage)
{       
	int taskID;
	bool dateFlagStart, dateFlagEnd, timeFlagStart, timeFlagEnd, statusFlag;
	string singleWord, text;

	dateFlagStart = dateFlagEnd = timeFlagStart = timeFlagEnd = statusFlag = 0;

	taskID=searchIDToBeUpdated(splitString);
	//------------------------------------------
	//please change and refactor the code below 
	if (taskID>=splitString.size())
		return false;
	// Converts the string to number
	int number = stringToInt(splitString[taskID].c_str()); 
	int pos;
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
				if (!checkTime(splitString[i+1])) {
					return false;
				}
				int timeValue=stringToInt(splitString[i+1]);
				timeFlagStart = assignTime (TaskStorage[pos],timeValue,'s');
				if (timeFlagStart==false) {
					TaskStorage[pos] = newTask;
					return false;
				}
			} 
			else if(splitString[i]=="-endtime")
			{ 
				if (!checkTime(splitString[i+1])) {
					return false;
				}
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

			if (dateFlagStart==1 && dateFlagEnd==1 && timeFlagStart==1 &&timeFlagEnd==1) {
				newTask.assignKind('t');
				if (!checkDateTimeLogic(newTask,'t')) {
					return false;
				}
			}
			else if (dateFlagEnd==1 && timeFlagEnd==1) {
				newTask.assignKind('d');
				if (!checkDateTimeLogic(newTask,'d')) {
					return false;
				}
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
bool TaskManager::checkTime(string toCheckTime) {
	int size=toCheckTime.size();
	if (size!=4)
		return false;
	else {
		for (int i=0;i<4;i++) {
			if (toCheckTime[i]<'0'||toCheckTime[i]>'9')
				return false;
		}
	}
	return true;
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
	temp.min = ltm->tm_min;

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

// Updates status to approaching/missed deadline
void TaskManager::reupdateStatus(vector<Task>& taskStorage)
{
	time_t now = time(0);
	tm *timeNow = localtime(&now);

	for(unsigned int i=0; i<taskStorage.size(); i++)
	{
		if((taskStorage[i].returnStatus() != 'd') && (taskStorage[i].returnKind() != 'f'))
		{
			date endDate = taskStorage[i].returnDate('e');
			time_s endTime = taskStorage[i].returnTime('e');
			tm dateLine = {0};
			dateLine.tm_year = endDate.year + 100;
			dateLine.tm_mon = endDate.month - 1;
			dateLine.tm_mday = endDate.day;
			dateLine.tm_hour = endTime.hr;
			dateLine.tm_min = endTime.min;

			double diffHours = hoursBtwnTimes(*timeNow, dateLine);

			if(diffHours <= 0.0)
			{
				taskStorage[i].changeStatus('m');
			}
			else if(diffHours <= APPROACHING_DIFFERENCE)
			{
				taskStorage[i].changeStatus('a');
			}
			else 
			{
				taskStorage[i].changeStatus('n');
			}
		}
	}
}

// Returns number of hours between compare date and a dateline
// ie. dateline - compare date
// if negative, missed dateline
double TaskManager::hoursBtwnTimes(std::tm compare, std::tm dateLine)
{
	std::time_t timeCompare = std::mktime(&compare);
	std::time_t timeDateLine = std::mktime(&dateLine);

	return std::difftime(timeDateLine, timeCompare) / (60 * 60);
}

bool TaskManager::checkDateTimeLogic(Task &newTask,char kind) {
	date dateStart = newTask.returnDate('s');
	date dateEnd = newTask.returnDate('e');
	time_s timeStart = newTask.returnTime('s');
	time_s timeEnd = newTask.returnTime('e');

	if (kind=='t'||kind=='d') {
		if(newTask.checkDate(dateStart, dateEnd)==0) {
			if(newTask.checkTime(timeStart, timeEnd)==1) {
				return false;
			}
		}
		else if (newTask.checkDate(dateStart, dateEnd)==1) {
			return false;
		}
	}
	return true;
}

int TaskManager::searchIDToBeUpdated(vector<string> splitString) {
	int ID=0;
	while(splitString[ID]!="-update")
	{
		ID++;
	}
	ID++;
	return ID;
}