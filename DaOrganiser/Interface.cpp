#include "stdafx.h"
#include "Interface.h"
#include "Log.h"


Interface::Interface(void)
{
	DaOrganiser::MainWindow^ ui = gcnew DaOrganiser::MainWindow;
	userInterface = &ui;
	progController = new Facade(this);
	(*userInterface)->progController = progController;
	logging("application run", LogLevel::Debug);
	Application::Run(ui);
}


Interface::~Interface(void)
{
	delete progController;
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

void Interface::updateGuiList()
{
	(*userInterface)->updateList();
}