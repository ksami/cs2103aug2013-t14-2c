#pragma once

#include "MainWindow.h"
#include "logic.h"

class Interface
{
public:
	logic* progController;
	DaOrganiser::MainWindow^* userInterface;
public:
	Interface(void);
	~Interface(void);
	void toDisplay(string sentence);
	string toGetInput(void);
};

