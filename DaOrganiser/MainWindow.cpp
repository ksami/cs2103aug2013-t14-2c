#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "MainWindow.h"
#include <cctype>
#include "Facade.h"

//to switch off logging
//#define NLOG
#include "Log.h"

#define AVAILABLE_CMDS "-add", "-delete", "-update", "-undo", "-quit", "-startdate", "-enddate", "-starttime", "-endtime", "-kind", "-status", "-details"
#define AVAILABLE_CMDS_NUM 12
#define CMD_DELIMITER_CHAR '-'
#define CMD_DELIMITER_STR "-"
#define NULL_STRING ""
#define TEXT_INDEX_START 0

#pragma region Public Methods
//<summary>
//Public Methods
//</summary>

std::string DaOrganiser::MainWindow::sysStringToStdString(String^ stringToConvert)
{
	return msclr::interop::marshal_as <std::string> (stringToConvert);
}

String^ DaOrganiser::MainWindow::stdStringToSysString(std::string stringToConvert)
{
	return msclr::interop::marshal_as <String^> (stringToConvert);
}

void DaOrganiser::MainWindow::addTaskToList(Task taskToAdd)
{
	//assumption: taskid is unique
	ListViewItem^ itemToAdd=gcnew ListViewItem(stdStringToSysString(taskToAdd.getIdAsString()));

	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartDateAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndDateAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getDetailsAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStatusAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getKindAsString()));

	listView1->Items->Add(itemToAdd);
}

void DaOrganiser::MainWindow::updateList(void)
{
	static vector<Task> allTasks;
	Facade* controller = (Facade*)progController;
	allTasks=controller->getTaskStorage();
	listView1->Items->Clear();
	for(int i=0; i<allTasks.size(); i++)
	{
		addTaskToList(allTasks[i]);
	}
}

std::string DaOrganiser::MainWindow::getUserInput(void)
{
	std::string userInput = sysStringToStdString(comboBox1->Text);
	logging("Input captured: " + userInput, LogLevel::Info);
	return userInput;
}

void DaOrganiser::MainWindow::clearInputField(void)
{
	comboBox1->Text=NULL_STRING;
}

void DaOrganiser::MainWindow::appendToOutput(std::string userFeedback)
{
	//check if richTextBox1 overflow
	//if so, delete first 1000 characters
	if(richTextBox1->Text->Length > 100000)
	{
		richTextBox1->Text = richTextBox1->Text->Remove(0, 1000);
	}

	richTextBox1->Text+=stdStringToSysString(userFeedback);
	richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
	richTextBox1->ScrollToCaret();
	richTextBox1->Text+="\n";
}

void DaOrganiser::MainWindow::exitProgram(void)
{
	logging("Exit program sequence initiated", LogLevel::Debug);
	//write goodbye messages (or not)
	//save to file first
	this->Close();
}

#pragma endregion

#pragma region Private Methods
// Private Methods

//adds matching items to the suggestion box
void DaOrganiser::MainWindow::suggestResults(void)
{
	array <String^>^ availableCmds = {AVAILABLE_CMDS};

	for(int i=0; i<AVAILABLE_CMDS_NUM; i++)
	{
		comboBox1->Items->Remove(availableCmds[i]);

		if(availableCmds[i]->StartsWith(userInputWord))
		{
			comboBox1->Items->Add(availableCmds[i]);
		}
	}
}

void DaOrganiser::MainWindow::openSuggestionBox(void)
{
	comboBox1->DroppedDown = true;
}

void DaOrganiser::MainWindow::closeSuggestionBox(void)
{
	if(comboBox1->Items->Count == 0)
	{
		comboBox1->Items->Add("");
		comboBox1->DroppedDown = false;
		comboBox1->Items->Remove("");
	}
	else
	{
		comboBox1->DroppedDown = false;
	}
}

void DaOrganiser::MainWindow::commitSelectedSuggestion(void)
{
	comboBox1->Text = userPrevInput;
	comboBox1->Text += comboBox1->SelectedItem;
}

//focuses combobox1, sets caret to end
void DaOrganiser::MainWindow::setCaretToEnd(void)
{
	comboBox1->Select(comboBox1->Text->Length, TEXT_INDEX_START);
}

#pragma endregion

//stub
/*void DaOrganiser::MainWindow::addToList(String^ details)
{
	System::DateTime timeAdded = System::DateTime::Now;
	ListViewItem^ item = gcnew ListViewItem(timeAdded.ToString());
	item->SubItems->Add(details);
	item->SubItems->Add("Not done");
	listView1->Items->Add(item);
	delete item;
}*/

#pragma region Event Handlers
/////////////////////////
//    Event Handlers   //
/////////////////////////

//column click sorting for entire inventory
System::Void DaOrganiser::MainWindow::listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e)
{
	static int _sortColumnInv = 1;
	listView1->ListViewItemSorter = gcnew ListViewItemComparer( e->Column, -1*_sortColumnInv);
	_sortColumnInv*=-1;
}

// Following events implement Autocomplete for commands
// Order of events called: PreviewKeyDown > KeyDown > KeyPress > KeyUp
System::Void DaOrganiser::MainWindow::comboBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	logging("comboBox1_KeyPress called", LogLevel::Event);
	const bool nonAlphaNumeric = (e->KeyChar < 48 || ( e->KeyChar >= 58 && e->KeyChar <= 64) || ( e->KeyChar >= 91 && e->KeyChar <= 96) || e->KeyChar > 122);

	if(e->KeyChar == CMD_DELIMITER_CHAR)
	{
		userPrevInput = comboBox1->Text;

		openSuggestionBox();
		
		std::string charToConvert = NULL_STRING;
		charToConvert += tolower((char) e->KeyChar);
		userInputWord = stdStringToSysString(charToConvert);

		suggestResults();
	}
	else if(!nonAlphaNumeric)
	{
		std::string charToConvert = NULL_STRING;
		charToConvert += tolower((char) e->KeyChar);
		userInputWord += stdStringToSysString(charToConvert);
		
		suggestResults();
	}
}

System::Void DaOrganiser::MainWindow::comboBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	logging("comboBox1_KeyDown called", LogLevel::Event);
	int i = comboBox1->SelectionStart;
	String^ currentChar = NULL_STRING;

	if ( i > 0 )
	{
		currentChar = comboBox1->Text->Substring(i-1,1);
	}

	if(e->KeyCode == System::Windows::Forms::Keys::Back)
	{
		if (comboBox1->Text->Length > 0 && comboBox1->DroppedDown == true)
		{	
			if (currentChar == CMD_DELIMITER_STR)
			{
				closeSuggestionBox();
				userInputWord = NULL_STRING;
			}
			else if(userInputWord->Length > 0)
			{
				userInputWord = userInputWord->Substring(0, userInputWord->Length -1);
				suggestResults();	
			}
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Space)
	{
		if(comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
			setCaretToEnd();
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Up)
	{
		e->Handled = true;
		if (comboBox1->DroppedDown == true)
		{
			if(comboBox1->SelectedIndex > 0)
			{
				comboBox1->SelectedIndex--;
			}
			commitSelectedSuggestion();
			setCaretToEnd();
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Down)
	{
		e->Handled = true;
		if (comboBox1->DroppedDown == true)
		{
			if(comboBox1->SelectedIndex < comboBox1->Items->Count -1)
			{
				comboBox1->SelectedIndex++;
			}
			commitSelectedSuggestion();
			setCaretToEnd();
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Right)
	{
		if (comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Escape)
	{
		e->Handled = true;
		if(comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
			commitSelectedSuggestion();
			setCaretToEnd();
		}
		else
		{
			exitProgram();
		}
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Enter)
	{
		e->Handled = true;
		static bool toExit = false;
		string userInput = sysStringToStdString(comboBox1->Text);
		appendToOutput(userInput);
		logging("Input entered: " + userInput, LogLevel::Info);

		Facade* controller = (Facade*)progController;
		controller->executeProgramme(toExit);
		//facade will take care of user feedback here

		clearInputField();

		richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
		richTextBox1->ScrollToCaret();

		//check if richTextBox1 overflow
		if(richTextBox1->Text->Length > 100000)
		{
			richTextBox1->Text = richTextBox1->Text->Remove(0, 1000);
		}

		if(comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
		}

		if(toExit)
		{
			exitProgram();
		}
	}
}

System::Void DaOrganiser::MainWindow::comboBox1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e)
{
	logging("comboBox1_PreviewKeyDown called", LogLevel::Event);
	if((e->KeyCode == System::Windows::Forms::Keys::Tab) && (comboBox1->DroppedDown == true) && (comboBox1->Items->Count > 0))
	{
		if(comboBox1->SelectedIndex > 0)
		{
			closeSuggestionBox();
			commitSelectedSuggestion();
			setCaretToEnd();
		}
		else
		{
			comboBox1->SelectedIndex = 0;
			closeSuggestionBox();
			commitSelectedSuggestion();
			setCaretToEnd();
		}
	}
}

#pragma endregion