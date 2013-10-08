#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "newtask.h"
#include "newprocess.h"

using namespace std;

void main()
{
	process p;
	vector<int> spaceInString;
	vector<string> splitString;
	task temporary;
	string userTask, singleWord;
	cout<<"Welcome to TeamNote!\n";
	cout<<"Enter your tasks (Enter \"quit\" to exit the program) :\n";
	cout<<endl;

	do
	{
		getline(cin, userTask);

		if(userTask == "quit" || userTask == "Quit")
			exit(0);

		int i, j;
		spaceInString.push_back(0);

		for(i=0;i<userTask.length();i++)
		{
			if(userTask[i]==' ')
				spaceInString.push_back(i);
		}
		
		spaceInString.push_back(userTask.length());

		for(i=0;i<spaceInString.size();i++)
		{
			singleWord = userTask.substr(spaceInString[i], spaceInString[i+1]-1);
			splitString.push_back(singleWord);
		}

		for(i=0;i<splitString.size();i++)
			if(splitString[i]=="-add")
			{
				p.createTask(userTask);
				break;
			}
			else if(splitString[i]=="-update")
			{
				p.updateTask();
				break;
			}
			else if(splitString[i]=="-delete")
			{
				p.deleteTask();
				break;
			}
			else if (splitString[i]=="-read")
			{
				p.readTask();
				break;
			}

	}while(userTask!="quit"||userTask!="Quit");

}