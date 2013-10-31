/*

Author: Priya

Assumptions:

By default all tasks have:
status - not done 
kind - floating
start date - 000000
end date - 000000
start time - 0000
end time - 0000
deatils - ""

*/
#include"process.h"
#include<string>
#include<iostream>
#include<vector>
#include<stdio.h>

using namespace std;

bool process::createTask(vector<string>splitString)
{
	task newTask;
	date d, zeroDate;
	time t, zeroTime;
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
		time time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
		if(newTask.checkTime(time1, time2) == 1)
			return false;
	}

	toBeDone.push_back(newTask);
	return true;
}

void process::readTask()
{
	if(toBeDone.empty())
		cout<<"No tasks exist";

	for(int i=0;i<toBeDone.size();i++)
	{
		cout<<i+1<<" .";
		toBeDone[i].displayDetail();
		cout<<endl;
	}
}

bool process::updateTask(vector<string> splitString)
{	
	date d;
	time t;
	int i, j, dateFlag1, dateFlag2, timeFlag1, timeFlag2;
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

	if(number<=0||number>toBeDone.size())
		return false;

	number--;

	task newTask = toBeDone[number];

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

			if(!toBeDone[number].assignDateValue(d, 's'))
			{
				toBeDone[number] = newTask;
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

			if(!toBeDone[number].assignDateValue(d, 'e'))
			{
				toBeDone[number] = newTask;
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

			if(!toBeDone[number].assignTimeValue(t, 's'))
			{
				toBeDone[number] = newTask;
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

			if(!toBeDone[number].assignTimeValue(t, 'e'))
			{
				toBeDone[number] = newTask;
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

			toBeDone[number].assignDetails(text);
		}
		else if(splitString[i]=="-status")
		{
			toBeDone[number].changeStatus(splitString[i+1][0]);
			if(!toBeDone[number].changeStatus(splitString[i+1][0]))
			{
				toBeDone[number] = newTask;
				return false;
			}
		}
		else if(splitString[i]=="-kind")
		{
			if(!toBeDone[number].assignKind(splitString[i+1][0]))
			{
				toBeDone[number] = newTask;
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
			time time1 = newTask.returnTime('s'), time2 = newTask.returnTime('e');
			if(newTask.checkTime(time1, time2) == 1)
				return false;
		}

		toBeDone.push_back(newTask);
		return true;

	}

	return true;

}

bool process::deleteTask(vector<string> splitString)
{
	int number = atoi(splitString[1].c_str());

	if(number<=0 || (number>toBeDone.size()))
		return false;

	toBeDone.erase(toBeDone.begin()+number-1);
	return true;
}