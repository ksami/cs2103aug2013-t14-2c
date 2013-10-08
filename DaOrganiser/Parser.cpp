#include "stdafx.h"
#include "Parser.h"

using namespace std;

Parser::Parser(void)
{
}

string Parser::parseString(string userTask)
{
	vector<int> spaceInString;
	vector<string> splitString;
	string singleWord;

	if(userTask == "quit" || userTask == "Quit")
	{
		//TODO
		return "why did you quit! :(";
		//exit(0); choose something else
	}

	spaceInString.push_back(0);

	for(int i=0;i<userTask.length();i++)
	{
		if(userTask[i]==' ')
			spaceInString.push_back(i);
	}

	spaceInString.push_back(userTask.length());

	for(int i=0;i<spaceInString.size()-1;i++)
	{
		//BUG
		//substr 1st parameter is position to start, 2nd is length
		singleWord = userTask.substr(spaceInString[i]+1, spaceInString[i+1]-(spaceInString[i]+1));
		splitString.push_back(singleWord);
	}

	for(int i=0;i<splitString.size();i++)
	{
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
	}
	//TODO
	//stub
	return "kkeut!!";
}
