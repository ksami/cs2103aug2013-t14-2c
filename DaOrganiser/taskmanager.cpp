#include "stdafx.h"
#include "taskmanager.h"

bool taskManager::createTask(vector<string>splitString,vector<task> &taskStorage)
{
	task newTask;
	date d;
	time_s t;
	int j;
	string singleWord, text;
	bool returnvalue = true;

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

			if(!newTask.assignDateValue(d, 's'))
				returnvalue = false;
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
				returnvalue = false;
		}
		else if(splitString[i]=="-starttime")
		{
			// Converts the string to int and saves it as a time of format hhmm
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;

			if(!newTask.assignTimeValue(t, 's'))
				returnvalue = false;
		}
		else if(splitString[i]=="-endtime")
		{
			// Converts the string to int and saves it as a time of format hhmm
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;

			if(!newTask.assignTimeValue(t, 'e'))
				returnvalue = false;
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
				returnvalue = false;
		}
		else if(splitString[i]=="-kind")
		{
			if(!newTask.assignKind(splitString[i+1][0]))
				returnvalue = false;
		}
	}

	taskStorage.push_back(newTask);
	return returnvalue;
}

//for CLI
void taskManager::readTask(vector<task> &taskStorage)
{
	for(unsigned int i=0;i<taskStorage.size();i++)
	{
		cout<<"--------------Task"<<i+1<<"--------------"<<endl;;
		taskStorage[i].displayDetail();
		cout<<endl;
	}
}

bool taskManager::updateTask(vector<string> splitString,vector<task> &taskStorage)
{       
	date d;
	time_s t;
	int i, j;
	string singleWord, text;


	// Searchs for the task number to be updated 
	//------------------------------------------
	i=0;
	while(splitString[i]!="-update")
	{
		i++;
	}
	i++;
	//------------------------------------------

	// Converts the string to number
	int number = atoi(splitString[i].c_str());

	if(number<=0||number>taskStorage.size())
		return false;

	number--;

	task newTask = taskStorage[number];

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

			if(!taskStorage[number].assignDateValue(d, 's'))
			{
				taskStorage[number] = newTask;
				return false;
			}
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

			if(!taskStorage[number].assignDateValue(d, 'e'))
			{
				taskStorage[number] = newTask;
				return false;
			}
		}
		else if(splitString[i]=="-starttime")
		{
			// Converts the string to int and saves it as a time of format hhmm
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;

			if(!taskStorage[number].assignTimeValue(t, 's'))
			{
				taskStorage[number] = newTask;
				return false;
			}
		}
		else if(splitString[i]=="-endtime")
		{
			// Converts the string to int and saves it as a time of format hhmm
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;

			if(!taskStorage[number].assignTimeValue(t, 'e'))
			{
				taskStorage[number] = newTask;
				return false;
			}
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

			taskStorage[number].assignDetails(text);
		}
		else if(splitString[i]=="-status")
		{
			taskStorage[number].changeStatus(splitString[i+1][0]);
			if(!taskStorage[number].changeStatus(splitString[i+1][0]))
			{
				taskStorage[number] = newTask;
				return false;
			}
		}
		else if(splitString[i]=="-kind")
		{
			if(!taskStorage[number].assignKind(splitString[i+1][0]))
			{
				taskStorage[number] = newTask;
				return false;
			}
		}
	}
	return true;
}

bool taskManager::deleteTask(vector<string> splitString, vector<task> &taskStorage)
{
	int number = atoi(splitString[1].c_str());

	if(number<=0 || (number>taskStorage.size()))
		return false;

	taskStorage.erase(taskStorage.begin()+number-1);
	return true;
}