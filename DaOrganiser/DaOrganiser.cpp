// DaOrganiser.cpp : main project file.

#include "stdafx.h"
#include "MainWindow.h"
#include "Interface.h"
#include "Log.h"

using namespace DaOrganiser;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	logging("creating interface", LogLevel::Debug);
	Interface guiLogicInterface;

	return 0;
}
