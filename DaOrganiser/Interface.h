#pragma once

#include "MainWindow.h"
#include "Facade.h"

class Interface
{
public:
	DaOrganiser::MainWindow^* userInterface;
public:
	Interface(void);
	~Interface(void);
	void toDisplay(string sentence);
	string toGetInput(void);
	void displayGuiSearchResults(vector<Task>& searchResults);
	void updateGuiList(void);
};

