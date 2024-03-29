//@author A0097075W

#include "stdafx.h"
#include "Interface.h"
#include "Log.h"


Interface::Interface(void)
{
	DaOrganiser::MainWindow^ ui = gcnew DaOrganiser::MainWindow;
	userInterface = &ui;
	(*userInterface)->progController = new Facade(this);
	logging("application run", LogLevel::Debug);
	Application::Run(ui);
}


Interface::~Interface(void)
{
}

void Interface::toDisplay(string sentence)
{
	//cout<<sentence;	
	(*userInterface)->appendToOutput(sentence);
}

string Interface::toGetInput()
{
	//string input;
	//getline(std::cin, input);
	//return input;
	return (*userInterface)->getUserInput();
}

void Interface::displayGuiSearchResults(vector<Task>& searchResults)
{
	(*userInterface)->displaySearchResult(searchResults);
}

void Interface::updateGuiList()
{
	(*userInterface)->updateList();
}