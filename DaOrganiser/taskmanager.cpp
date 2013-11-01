#include "stdafx.h"
#include "TaskManager.h"

TaskManager::TaskManager() {
	ID=0;
}

TaskManager::~TaskManager() {
}

bool TaskManager::createTask(vector<string>splitString,vector<Task> &TaskStorage) 
{ 
	updateIDNumber();
    Task newTask; 
    date d, zeroDate; 
    time_s t, zeroTime; 
    int i, j, dateFlag1, dateFlag2, timeFlag1, timeFlag2; 
    string singleWord, text; 
  
    dateFlag1 = dateFlag2 = timeFlag1 = timeFlag2 = 0;

    for(i=0;i<splitString.size();i++) 
    { 
        if(splitString[i]=="-startdate") 
        { 
            // Converts the string to int and saves it as a date of format ddmmyy 
            int value = atoi(splitString[i+1].c_str()); 
            d.year = value%100; 
            value/=100; 
            d.month = value%100; 
            value/=100; 
            d.day = value; 
  
            if(!newTask.assignDateValue(d, 's')) 
                return false; 
            dateFlag1 = 1;
        } 
        else if(splitString[i]=="-enddate") 
        { 
            // Converts the string to int and saves it as a date of format ddmmyy 
            int value = atoi(splitString[i+1].c_str()); 
            d.year = value%100; 
            value/=100; 
            d.month = value%100; 
            value/=100; 
            d.day = value; 
  
            if(!newTask.assignDateValue(d, 'e')) 
                return false;
             dateFlag2 = 1; 
        } 
        else if(splitString[i]=="-starttime") 
        { 
            // Converts the string to int and saves it as a time of format hhmm 
            int value = atoi(splitString[i+1].c_str()); 
            t.min = value%100; 
            value/=100; 
            t.hr = value%100; 
  
            if(!newTask.assignTimeValue(t, 's')) 
                return false; 
            timeFlag1 = 1;
        } 
        else if(splitString[i]=="-endtime") 
        { 
            // Converts the string to int and saves it as a time of format hhmm 
            int value = atoi(splitString[i+1].c_str()); 
            t.min = value%100; 
            value/=100; 
            t.hr = value%100; 
  
            if(!newTask.assignTimeValue(t, 'e')) 
                return false; 
            timeFlag2 = 1;
        } 
        else if(splitString[i]=="-details") 
        { 
            string text = ""; 
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

			newTask.assignDetails(text); 
		} 
		else if(splitString[i]=="-status") 
		{ 
			newTask.changeStatus(splitString[i+1][0]); 
			if(!newTask.changeStatus(splitString[i+1][0])) 
				return false; 
		} 
		else if(splitString[i]=="-kind") 
		{ 
			if(!newTask.assignKind(splitString[i+1][0])) 
				return false; 
		} 
	} 

  	// Checking if time and date have logical values
	if((dateFlag1)&&(dateFlag2))
	{
		date date1 = newTask.returnDate('s'), date2 = newTask.returnDate('e');
		if(newTask.checkDate(date1, date2) == 1)
			return false;
	}

	if((timeFlag1)&&(timeFlag2))
	{
		time_s time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
		if(newTask.checkTime(time1, time2) == 1)
			return false;
	}

	
  
    // Checking if time and date have logical values 
      
    /* 
    if(newTask.returnDate('s') != newTask.returnDate('0')) 
        if(newTask.returnDate('e') != newTask.returnDate('0')) 
            if(newTask.checkDate(newTask.returnDate('s'), newTask.returnDate('e')) == -1) 
                return false; 
    */
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
	int i, j, dateFlag1, dateFlag2, timeFlag1, timeFlag2;
	string singleWord, text;

	dateFlag1 = dateFlag2 = timeFlag1 = timeFlag2 = 0;

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
			if(splitString[i]=="-startdate")
			{
				// Converts the string to int and saves it as a date of format ddmmyy
				int value = atoi(splitString[i+1].c_str());
				d.year = value%100;
				value/=100;
				d.month = value%100;
				value/=100;
				d.day = value;

				if(!TaskStorage[pos].assignDateValue(d, 's'))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
				dateFlag1 = 1;
			}
			else if(splitString[i]=="-enddate")
			{
				// Converts the string to int and saves it as a date of format ddmmyy
				int value = atoi(splitString[i+1].c_str());
				d.year = value%100;
				value/=100;
				d.month = value%100;
				value/=100;
				d.day = value;

				if(!TaskStorage[pos].assignDateValue(d, 'e'))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
				 dateFlag2 = 1;
			}
			else if(splitString[i]=="-starttime")
			{
				// Converts the string to int and saves it as a time of format hhmm
				int value = atoi(splitString[i+1].c_str());
				t.min = value%100;
				value/=100;
				t.hr = value%100;

				if(!TaskStorage[pos].assignTimeValue(t, 's'))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
				timeFlag1 = 1;
			}
			else if(splitString[i]=="-endtime")
			{
				// Converts the string to int and saves it as a time of format hhmm
				int value = atoi(splitString[i+1].c_str());
				t.min = value%100;
				value/=100;
				t.hr = value%100;

				if(!TaskStorage[pos].assignTimeValue(t, 'e'))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
				timeFlag2 = 1;
			}
			else if(splitString[i]=="-details")
			{
				string text = "";
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

				TaskStorage[pos].assignDetails(text);
			}
			else if(splitString[i]=="-status")
			{
				TaskStorage[pos].changeStatus(splitString[i+1][0]);
				if(!TaskStorage[pos].changeStatus(splitString[i+1][0]))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
			}
			else if(splitString[i]=="-kind")
			{
				if(!TaskStorage[pos].assignKind(splitString[i+1][0]))
				{
					TaskStorage[pos] = newTask;
					return false;
				}
			}
			  if((dateFlag1)&&(dateFlag2))
                {
                        date date1 = newTask.returnDate('s'), date2 = newTask.returnDate('e');
                        if(newTask.checkDate(date1, date2) == 1)
                                return false;
                }

                if((timeFlag1)&&(timeFlag2))
                {
                        time_s time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
                        if(newTask.checkTime(time1, time2) == 1)
                                return false;
                }
		}
		return true;
	} catch (const char* msg) {
		cout<<msg;  // TODO: thrown from where??
	}
	return false;
}


bool TaskManager::deleteTask(vector<string> splitString, vector<Task> &TaskStorage)
{
	int number = atoi(splitString[1].c_str());

	if(number<=0 || (number>ID))
		return false;

	int delPos=findIDPos(number,TaskStorage);


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