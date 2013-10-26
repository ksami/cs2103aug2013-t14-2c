#pragma once

#include "MainWindow.h"
#include "Facade.h"

class Interface
{
public:
	Facade* progController;
	DaOrganiser::MainWindow^* userInterface;
public:
	Interface(void);
	~Interface(void);
	void toDisplay(string sentence);
	string toGetInput(void);
	void updateGuiList(void);
};

