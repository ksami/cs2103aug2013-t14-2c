/*

Author: Priya

*/
#include<iostream>
#include<conio.h>
#include<string>
#include<string.h>
#include<vector>
#include<sstream>
#include "task.h"
#include "process.h"

using namespace std;

void main()
{
	process p;
	vector<string> splitString;
	string userTask, singleWord;
	cout<<"Welcome to TeamNote!\n";
	cout<<"Enter your tasks (Enter \"quit\" to exit the program) :";
	cout<<endl;

	do
	{
start:

		// Clears all the previously stored values in the vector
		if(!splitString.empty())
		{
			while(!splitString.empty())
				splitString.pop_back();
		}

		// Gets the main string from the user
		getline(cin, userTask);

		// flag is used to break the loop
		int flag = 0;

		// If user wishes to quit
		if(userTask == "quit" || userTask == "Quit")
			exit(0);

		// To split the string
		//------------------------------------------------------------
		istringstream toSplitString(userTask);

		do
		{
			toSplitString>>singleWord;
			splitString.push_back(singleWord);
		}while(toSplitString);

		splitString.pop_back();
		//-------------------------------------------------------------

	/*
	*	
	*	// To display the split string
	*	for(int i=0;i<splitString.size();i++)
	*		cout<<splitString[i]<<endl;
	*	
	**/

		// Calls the process to add/ update/ read/ delete
		for(int i=0;i<splitString.size();i++)
		{
			if(splitString[i]=="-add")
			{
				bool value = p.createTask(splitString);
				if(value)
					cout<<"Task added successfully"<<endl;
				else 
					cout<<"Error found while adding task"<<endl;
				goto start;
			}
			else if(splitString[i]=="-update")
			{
				bool value = p.updateTask(splitString);
					if(value)
						cout<<"Task updated successfully"<<endl;
					else
						cout<<"Error found while updating the task" <<endl;
				goto start;
			}
			else if(splitString[i]=="-delete")
			{
				bool value = p.deleteTask(splitString);
				if(value)
					cout<<"Task deleted successfully"<<endl;
				else
					cout<<"Error found while deleting the task"<<endl;
				goto start;
			}
			else if (splitString[i]=="-read")
			{
				p.readTask();
				goto start;
			}
		}

	}while(userTask!="quit"||userTask!="Quit");

}