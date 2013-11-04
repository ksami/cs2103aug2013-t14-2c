#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "MainWindow.h"
#include <cctype>
#include "Facade.h"

//to switch off logging
//#define NLOG
#include "Log.h"

#define AVAILABLE_CMDS "-add", "-delete", "-update", "-search", "-all", "-undo", "-redo", "-quit", "-startdate", "-enddate", "-starttime", "-endtime", "-kind", "-status", "-details"
#define CMD_DELIMITER_CHAR '-'
#define CMD_DELIMITER_STR "-"
#define NULL_STRING ""

#define PATH_ICON_SUCCESS "resource/pika.ico"
#define PATH_ICON_FAIL "resource/pikared.ico"
#define PATH_SOUND_STARTUP "resource/pikaatk.wav"
#define PATH_SOUND_CLOSING "resource/pikaslp.wav"

#pragma region Public Methods
// Public Methods

// Converts a String^ into a std::string
std::string DaOrganiser::MainWindow::sysStringToStdString(String^ stringToConvert)
{
	return msclr::interop::marshal_as <std::string> (stringToConvert);
}

// Converts a std::string into a String^
String^ DaOrganiser::MainWindow::stdStringToSysString(std::string stringToConvert)
{
	return msclr::interop::marshal_as <String^> (stringToConvert);
}

// Creates a ListViewItem from a Task and adds it to listView1
void DaOrganiser::MainWindow::addTaskToList(Task taskToAdd)
{
	ListViewItem^ itemToAdd=gcnew ListViewItem(stdStringToSysString(taskToAdd.getIdAsString()));

	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartDateTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndDateTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getDetailsAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStatusAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getKindAsString()));

	//change color of listviewitem before adding it in
	changeColor(taskToAdd, itemToAdd);

	listView1->Items->Add(itemToAdd);
}

// Refreshes listView1 with all the tasks
void DaOrganiser::MainWindow::updateList(void)
{
	static vector<Task> allTasks;
	Facade* controller = (Facade*)progController;
	allTasks=controller->getTaskStorage();
	listView1->Items->Clear();
	for(unsigned int i=0; i<allTasks.size(); i++)
	{
		addTaskToList(allTasks[i]);
	}
}

// Displays search results in listView1
void DaOrganiser::MainWindow::displaySearchResult(vector<Task> searchResult)
{
	listView1->Items->Clear();
	for(unsigned int i=0; i<searchResult.size(); i++)
	{
		addTaskToList(searchResult[i]);
	}
}

// Sorts listView1 by column user chooses
void DaOrganiser::MainWindow::sortListColumn(unsigned int col)
{
	//for changing sort order from ascending to descending and vice versa
	static int sortColumnInv = 1;
	listView1->ListViewItemSorter = gcnew ListViewItemComparer( col, -1*sortColumnInv);
	sortColumnInv*=-1;
}

// Returns input user has keyed in into comboBox1 as std::string
std::string DaOrganiser::MainWindow::getUserInput(void)
{
	std::string userInput = sysStringToStdString(comboBox1->Text);
	logging("Input captured: " + userInput, LogLevel::Info);
	return userInput;
}

// Clears the input field comboBox1
void DaOrganiser::MainWindow::clearInputField(void)
{
	comboBox1->Text=NULL_STRING;
}

// Displays text output to the user in richTextBox1
void DaOrganiser::MainWindow::appendToOutput(std::string userFeedback)
{
	//check if richTextBox1 overflow
	//if so, delete first 90000 characters
	if(richTextBox1->Text->Length > 100000)
	{
		richTextBox1->Text = richTextBox1->Text->Remove(0, 90000);
	}

	//add visual effect based on success or failure of operation
	successOrFailure(userFeedback);

	richTextBox1->Text+=stdStringToSysString(userFeedback);

	//scroll to last line in richTextBox1
	richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
	richTextBox1->ScrollToCaret();
	richTextBox1->Text+="\n";
}

// Closes this window
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

// Changes color of background and/or text of the ListViewItem
void DaOrganiser::MainWindow::changeColor(Task taskToAdd, ListViewItem^& itemToAdd)
{
	std::string taskStatus = taskToAdd.getStatusAsString();
	std::string taskKind = taskToAdd.getKindAsString();
	itemToAdd->UseItemStyleForSubItems = false;

	//alternate colors of columns
	itemToAdd->SubItems[0]->BackColor = Color::LightGray;
	itemToAdd->SubItems[1]->BackColor = Color::LightGray;
	itemToAdd->SubItems[4]->BackColor = Color::LightGray;

	//change background color based on status of task
	if(taskStatus.find("Not done")!=std::string::npos)
	{
		itemToAdd->SubItems[0]->ForeColor = Color::DarkSlateGray;
		itemToAdd->SubItems[1]->ForeColor = Color::DarkSlateGray;
		itemToAdd->SubItems[2]->ForeColor = Color::DarkSlateGray;
		itemToAdd->SubItems[4]->ForeColor = Color::DarkSlateGray;
	}
	else if(taskStatus.find("Done")!=std::string::npos)
	{
		itemToAdd->UseItemStyleForSubItems = true;
		itemToAdd->BackColor = Color::WhiteSmoke;
		itemToAdd->ForeColor = Color::Gainsboro;
	}
	else if(taskStatus.find("Approaching")!=std::string::npos)
	{
		itemToAdd->BackColor = Color::LightYellow;
		itemToAdd->SubItems[4]->ForeColor = Color::DarkMagenta;
		itemToAdd->SubItems[4]->BackColor = Color::LightYellow;
	}
	else if(taskStatus.find("Missed")!=std::string::npos)
	{
		itemToAdd->BackColor = Color::OrangeRed;
		itemToAdd->SubItems[4]->ForeColor = Color::Maroon;
		itemToAdd->SubItems[4]->BackColor = Color::OrangeRed;
	}

	//change font color of task's kind
	if(taskKind.find("Floating")!=std::string::npos)
	{
		itemToAdd->SubItems[5]->ForeColor = Color::DarkGreen;
	}
	else if(taskKind.find("Timed")!=std::string::npos)
	{
		itemToAdd->SubItems[5]->ForeColor = Color::DarkBlue;
	}
	else if(taskKind.find("Deadline")!=std::string::npos)
	{
		itemToAdd->SubItems[5]->ForeColor = Color::DarkRed;
	}
}

// Changes background color of comboBox1 and icon based on operation success or failure
void DaOrganiser::MainWindow::successOrFailure(std::string userFeedback)
{
	//if message contains hints of success
	if(userFeedback.find("uccess")!=string::npos||userFeedback.find("complete")!=string::npos||userFeedback.find("Display")!=string::npos)
	{
		try
		{
			System::Drawing::Icon^ succIcon = gcnew System::Drawing::Icon(PATH_ICON_SUCCESS);
			this->Icon = succIcon;
		}
		catch(System::IO::DirectoryNotFoundException^)
		{
			logging("/resource folder not found", LogLevel::Error);
		}
		catch(System::IO::FileNotFoundException^)
		{
			logging(PATH_ICON_SUCCESS " not found", LogLevel::Error);
		}
		richTextBox1->BackColor = System::Drawing::Color::PaleGreen;
	}
	//if message contains hints of failure
	else if(userFeedback.find("fail")!=string::npos||userFeedback.find("Error")!=string::npos||userFeedback.find("Invalid")!=string::npos||userFeedback.find("No")!=string::npos)
	{
		try
		{
			System::Drawing::Icon^ failIcon = gcnew System::Drawing::Icon(PATH_ICON_FAIL);
			this->Icon = failIcon;
		}
		catch(System::IO::DirectoryNotFoundException^)
		{
			logging("/resource folder not found", LogLevel::Error);
		}
		catch(System::IO::FileNotFoundException^)
		{
			logging(PATH_ICON_FAIL " not found", LogLevel::Error);
		}
		richTextBox1->BackColor = System::Drawing::Color::Tomato;
	}
}

// Adds matching items to the suggestion box
void DaOrganiser::MainWindow::suggestResults(void)
{
	array <String^>^ availableCmds = {AVAILABLE_CMDS};

	for(int i=0; i<availableCmds->Length; i++)
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
	//if empty, add dummy element to bypass error
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

// Appends the selected suggestion to the text in the input field comboBox1
void DaOrganiser::MainWindow::commitSelectedSuggestion(void)
{
	comboBox1->Text = userPrevInput;
	comboBox1->Text += comboBox1->SelectedItem;
}

// Focuses comboBox1, sets caret to end
void DaOrganiser::MainWindow::setCaretToEnd(void)
{
	comboBox1->Select(comboBox1->Text->Length, 0);
}

#pragma endregion

#pragma region Event Handlers
/////////////////////////
//    Event Handlers   //
/////////////////////////

// Startup sound
System::Void DaOrganiser::MainWindow::MainWindow_Load(System::Object^  sender, System::EventArgs^  e)
{
	updateList();
	try
	{
		//for embed resource
		//System::Reflection::Assembly^ a = System::Reflection::Assembly::GetExecutingAssembly();
		//System::IO::Stream^ s = a->GetManifestResourceStream(PATH_SOUND_STARTUP);
		//System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(s);
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(PATH_SOUND_STARTUP);
		sound->Play();
	}
	catch(System::IO::DirectoryNotFoundException^)
	{
		logging("/resource folder not found", LogLevel::Error);
	}
	catch(System::IO::FileNotFoundException^)
	{
		logging(PATH_SOUND_STARTUP " not found", LogLevel::Error);
	}
}

// Closing sound
System::Void DaOrganiser::MainWindow::MainWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	try
	{
		//for embed resource
		//System::Reflection::Assembly^ a = System::Reflection::Assembly::GetExecutingAssembly();
		//System::IO::Stream^ s = a->GetManifestResourceStream(PATH__SOUND_CLOSING);
		//System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(s);
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(PATH_SOUND_CLOSING);
		sound->Play();

		//delay ending of the program to allow the sound to finish playing
		Sleep(2000);
	}
	catch(System::IO::DirectoryNotFoundException^)
	{
		logging("/resource folder not found", LogLevel::Error);
	}
	catch(System::IO::FileNotFoundException^)
	{
		logging(PATH_SOUND_CLOSING " not found", LogLevel::Error);
	}
}

// Following comboBox1 key events implement Autocomplete for commands among others
// Order of events called: PreviewKeyDown > KeyDown > KeyPress > KeyUp

// Disable tab from changing focus to listView1
// Autocomplete commit: Tab
System::Void DaOrganiser::MainWindow::comboBox1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e)
{
	logging("comboBox1_PreviewKeyDown called", LogLevel::Event);

	//if suggestion box is open and it is not empty
	if((e->KeyCode == System::Windows::Forms::Keys::Tab) && (comboBox1->DroppedDown == true) && (comboBox1->Items->Count > 0))
	{
		listView1->TabStop = false;

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

// Autocomplete commit: Right arrow, Enter
// Autocomplete suggest: Backspace
// Autocomplete close suggestion box: Backspace, Space, Escape
// Scroll through input history: Up arrow, Down arrow
// Exit program: Escape
System::Void DaOrganiser::MainWindow::comboBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	logging("comboBox1_KeyDown called", LogLevel::Event);

	static vector<std::string> inputHistory;
	static int inputHistoryIndex = 0;

	int caretPos = comboBox1->SelectionStart;
	String^ currentChar = NULL_STRING;

	//get the character in the input field comboBox1 just before this event was called
	if (caretPos > 0)
	{
		currentChar = comboBox1->Text->Substring(caretPos-1,1);
	}

	// Backspace Key
	if(e->KeyCode == System::Windows::Forms::Keys::Back)
	{
		if (comboBox1->Text->Length > 0 && comboBox1->DroppedDown == true)
		{	
			//if character deleted by backspace was '-', close suggestion box
			if (currentChar == CMD_DELIMITER_STR)
			{
				closeSuggestionBox();
				userInputWord = NULL_STRING;
			}

			//resuggest results without character delete by backspace
			else if(userInputWord->Length > 0)
			{
				userInputWord = userInputWord->Substring(0, userInputWord->Length -1);
				suggestResults();	
			}
		}
	}

	// Space Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Space)
	{
		if(comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
			setCaretToEnd();
		}
	}

	// Up arrow Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Up)
	{
		e->Handled = true;
		if (comboBox1->DroppedDown == true)
		{
			//scroll through suggestions
			if(comboBox1->SelectedIndex > 0)
			{
				comboBox1->SelectedIndex--;
			}
			commitSelectedSuggestion();
			setCaretToEnd();
		}
		else
		{
			//scroll through history of user input
			if(inputHistoryIndex == 0 && inputHistory.empty() == false)
			{
				comboBox1->Text=stdStringToSysString(inputHistory[inputHistoryIndex]);
				setCaretToEnd();
			}
			else if(inputHistoryIndex-1 >= 0)
			{
				comboBox1->Text=stdStringToSysString(inputHistory[--inputHistoryIndex]);
				setCaretToEnd();
			}
		}
	}

	// Down arrow Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Down)
	{
		e->Handled = true;
		if (comboBox1->DroppedDown == true)
		{
			//scroll through suggestions
			if(comboBox1->SelectedIndex < comboBox1->Items->Count -1)
			{
				comboBox1->SelectedIndex++;
			}
			commitSelectedSuggestion();
			setCaretToEnd();
		}
		else
		{
			//scroll through history of user input
			if(inputHistoryIndex == 0 && inputHistory.empty() == false)
			{
				comboBox1->Text=stdStringToSysString(inputHistory[++inputHistoryIndex]);
				setCaretToEnd();
			}
			else if(inputHistoryIndex < inputHistory.size())
			{
				comboBox1->Text=stdStringToSysString(inputHistory[inputHistoryIndex++]);
				setCaretToEnd();
			}
		}
	}

	// Right arrow Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Right)
	{
		if (comboBox1->DroppedDown == true)
		{
			closeSuggestionBox();
		}
	}

	// Escape Key
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

	// Enter Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Enter)
	{
		e->Handled = true;

		//if true, exit program
		static bool toExit = false;

		string userInput = sysStringToStdString(comboBox1->Text);

		//check for input history overflow, delete oldest 200 inputs
		if(inputHistory.size() > 300)
		{
			for(unsigned int i=0; i<100; i++)
			{
				inputHistory[i] = inputHistory[i+200];
			}
			inputHistory.resize(100);
		}

		inputHistory.push_back(userInput);
		inputHistoryIndex = inputHistory.size();

		appendToOutput(userInput);
		logging("Input entered: " + userInput, LogLevel::Info);

		//run the rest of the programme
		Facade* controller = (Facade*)progController;
		controller->executeProgramme(toExit);

		clearInputField();

		//scroll to last line in richTextBox1
		richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
		richTextBox1->ScrollToCaret();

		//check for richTextBox1 overflow
		if(richTextBox1->Text->Length > 100000)
		{
			richTextBox1->Text = richTextBox1->Text->Remove(0, 90000);
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

// Autocomplete suggest: CMD_DELIMITER_CHAR or alphaNumeric char
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

// Enable tab to change focus to listView1
System::Void DaOrganiser::MainWindow::comboBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if((e->KeyCode == System::Windows::Forms::Keys::Tab) && (comboBox1->DroppedDown == false))
	{
		listView1->TabStop = true;
	}
}

// Sort listView1 based on column user clicked on
System::Void DaOrganiser::MainWindow::listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e)
{
	sortListColumn(e->Column);
}

// Keyboard navigation for listView1
// Sort listView1 based on column user chooses: 1, 2, 3, 4, 5, 6
// Exit program: Escape
System::Void DaOrganiser::MainWindow::listView1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	// Escape Key
	if(e->KeyCode == System::Windows::Forms::Keys::Escape)
	{
		exitProgram();
	}
	// Q Key
	else if(e->KeyCode == System::Windows::Forms::Keys::Q)
	{
		static bool alternate = true;
		if(alternate)
		{
			listView1->TileSize = Drawing::Size((this->Width - 100)/5, 200);
			listView1->View = System::Windows::Forms::View::Tile;
		}
		else
		{
			listView1->View = System::Windows::Forms::View::Details;
		}
		alternate=!alternate;
	}
	// 1 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D1)
	{
		//taskID
		sortListColumn(0);
	}
	// 2 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D2)
	{
		//Details
		sortListColumn(3);
	}
	// 3 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D3)
	{
		//Start datetime
		sortListColumn(1);
	}
	// 4 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D4)
	{
		//End datetime
		sortListColumn(2);
	}
	// 5 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D5)
	{
		//Status
		sortListColumn(4);
	}
	// 6 Key
	else if(e->KeyCode == System::Windows::Forms::Keys::D6)
	{
		//Kind
		sortListColumn(5);
	}
}

#pragma endregion