#include "stdafx.h"
#include "newprocess.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "MainWindow.h"

using namespace std;

vector<task> process::getTasks()
{
	return toBeDone;
}

//take the string split into a vector of parameters and creates a task
//TODO return value for?
bool process::createTask(vector<string> splitString)
{
	task newTask;
	date d;
	time t;
	int i, j;
	string text;
	bool returnvalue = true;

	for(i=0;i<splitString.size();i++)
	{
		if(splitString[i]=="-startdate")
		{
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
			
			int value = atoi(splitString[i+1].c_str());
			d.year = value%100;
			value/=100;
			d.month = value%100;
			value/=100;
			d.day = value;
			if(!newTask.assignDateValue(d, 'e'))
				returnvalue = false;
		}
		else if(splitString[i]=="-startime")
		{
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;
			if(!newTask.assignTimeValue(t, 's'))
				returnvalue = false;
		}
		else if(splitString[i]=="-endtime")
		{
			int value = atoi(splitString[i+1].c_str());
			t.min = value%100;
			value/=100;
			t.hr = value%100;
			if(!newTask.assignTimeValue(t, 'e'))
				returnvalue = false;
		}
		else if(splitString[i]=="-details")
		{
			j=i+1;
			while(splitString[j][0]!='-')
			{
				text += splitString[j];
				j++;
			}

			newTask.assignDetails(text);
		}
		else if(splitString[i]=="-status")
		{
			newTask.changeStatus(splitString[i+1][0]);
		}
		else if(splitString[i]=="-kind")
		{
			if(!newTask.assignKind(splitString[i+1][0]))
				returnvalue = false;
		}
	}
	toBeDone.push_back(newTask);

	return returnvalue;
}

void process::readTask()
{
	for(int i=0;i<toBeDone.size();i++)
	{
		cout<<i+1<<" .";
		toBeDone[i].displayDetail();
		cout<<endl;
	}
}

bool process::updateTask()
{
	int choice, number;
	date d;
	time t;
	string text;
	char temporary;
	cout<<"Enter task number to be updated: ";
	cin>>number;

	if(number<=0 || (number>toBeDone.size()))
		return false;

	cout<<"What to update?"<<endl;
	if(toBeDone[number-1].returnKind() == 't') 
	{
		cout<<"1. Start date"<<endl;
		cout<<"2. End date"<<endl;
		cout<<"3. Start time"<<endl;
		cout<<"4. End time"<<endl;
		cout<<"5. Detail"<<endl;
		cout<<"6. Status"<<endl;
		cout<<"Enter choice: ";
		cin>>choice;

		switch(choice)
		{
		case 1:	cout<<"Enter date: ";
			cin>>d.day>>d.month>>d.month;
			toBeDone[number-1].assignDateValue(d, 's'); 
			break;

		case 2: cout<<"Enter date: ";
			cin>>d.day>>d.month>>d.month;
			toBeDone[number-1].assignDateValue(d, 'e');
			break;

		case 3: cout<<"Enter time: ";
			cin>>t.hr>>t.min;
			toBeDone[number-1].assignTimeValue(t, 's');
			break;

		case 4:cout<<"Enter time: ";
			cin>>t.hr>>t.min;
			toBeDone[number-1].assignTimeValue(t, 'e');
			break;

		case 5: cout<<"Enter detail: ";
			getline(cin, text);
			toBeDone[number-1].assignDetails(text);
			break;

		case 6: cout<<"Enter status: ";
			cin>>temporary;
			toBeDone[number-1].changeStatus(temporary);
		}

	}
	else if(toBeDone[number-1].returnKind() == 'd')
	{
		cout<<"1. End date"<<endl;
		cout<<"2. End time"<<endl;
		cout<<"3. Detail"<<endl;
		cout<<"4. Status"<<endl;
		cout<<"Enter choice: ";
		cin>>choice;

		switch(choice)
		{
		case 1: cout<<"Enter date: ";
			cin>>d.day>>d.month>>d.month;
			toBeDone[number-1].assignDateValue(d, 'e');
			break;

		case 2:cout<<"Enter time: ";
			cin>>t.hr>>t.min;
			toBeDone[number-1].assignTimeValue(t, 'e');
			break;

		case 3: cout<<"Enter detail: ";
			getline(cin, text);
			toBeDone[number-1].assignDetails(text);
			break;

		case 4: cout<<"Enter status: ";
			cin>>temporary;
			toBeDone[number-1].changeStatus(temporary);

		}

	}
	else
	{
		cout<<"1. Detail"<<endl;
		cout<<"2. Status"<<endl;
		cout<<"Enter choice: ";
		cin>>choice;

		switch(choice)
		{
		case 1: cout<<"Enter detail: ";
			getline(cin, text);
			toBeDone[number-1].assignDetails(text);
			break;

		case 2: cout<<"Enter status: ";
			cin>>temporary;
			toBeDone[number-1].changeStatus(temporary);

		}

	}

	return true;
}

bool process::deleteTask(int number)
{
	//cout<<"Enter task number to be deleted: ";
	//cin>>number;

	if(number<=0 || (number>toBeDone.size()))
		return false;

	toBeDone.erase(toBeDone.begin()+number-1);
	return true;
}