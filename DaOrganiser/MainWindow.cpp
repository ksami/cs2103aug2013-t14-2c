#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "MainWindow.h"
#include <cctype>
#include "Facade.h"

//to switch off logging
//#define NLOG
#include "Log.h"

#define AVAILABLE_CMDS "-add", "-delete", "-update", "-search", "-undo", "-redo", "-quit", "-startdate", "-enddate", "-starttime", "-endtime", "-kind", "-status", "-details"
#define AVAILABLE_CMDS_NUM 14
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

	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartDateTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndDateTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getDetailsAsString()));

	String^ status = stdStringToSysString(taskToAdd.getStatusAsString());
	itemToAdd->SubItems->Add(status);

	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getKindAsString()));

	itemToAdd->BackColor = changeColor(status);
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

void DaOrganiser::MainWindow::displaySearchResult(vector<Task> searchResult)
{
	listView1->Items->Clear();
	for(int i=0; i<searchResult.size(); i++)
	{
		addTaskToList(searchResult[i]);
	}
}

void DaOrganiser::MainWindow::sortListColumn(unsigned int col)
{
	static int sortColumnInv = 1;
	listView1->ListViewItemSorter = gcnew ListViewItemComparer( col, -1*sortColumnInv);
	sortColumnInv*=-1;
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

	if(userFeedback.find("success")!=string::npos)
	{
		try
		{
			System::Drawing::Icon^ succIcon = gcnew System::Drawing::Icon("resource/pika.ico");
			this->Icon = succIcon;
		}
		catch(System::IO::DirectoryNotFoundException^)
		{
			logging("/resource folder not found", LogLevel::Error);
		}
		catch(System::IO::FileNotFoundException^)
		{
			logging("pika.ico not found", LogLevel::Error);
		}
		richTextBox1->BackColor = System::Drawing::Color::PaleGreen;
	}
	else if(userFeedback.find("fail")!=string::npos||userFeedback.find("Error")!=string::npos||userFeedback.find("Invalid")!=string::npos||userFeedback.find("No")!=string::npos)
	{
		try
		{
			System::Drawing::Icon^ failIcon = gcnew System::Drawing::Icon("resource/pikared.ico");
			this->Icon = failIcon;
		}
		catch(System::IO::DirectoryNotFoundException^)
		{
			logging("/resource folder not found", LogLevel::Error);
		}
		catch(System::IO::FileNotFoundException^)
		{
			logging("pikared.ico not found", LogLevel::Error);
		}
		richTextBox1->BackColor = System::Drawing::Color::Tomato;
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

// Changes the background color of the listviewitem based on its status
System::Drawing::Color DaOrganiser::MainWindow::changeColor(String^ status)
{
	if(status == "Not done")
	{
		return System::Drawing::Color::WhiteSmoke;
	}
	else if(status == "Done")
	{
		return System::Drawing::Color::LightGray;
	}
	else
	{
		return System::Drawing::Color::Azure;
	}
}

// Adds matching items to the suggestion box
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

// Initialise listview with contents of storage.txt
System::Void DaOrganiser::MainWindow::MainWindow_Load(System::Object^  sender, System::EventArgs^  e)
{
	updateList();
	try
	{
		/*System::Reflection::Assembly^ a = System::Reflection::Assembly::GetExecutingAssembly();
		System::IO::Stream^ s = a->GetManifestResourceStream("pikaatk.wav");
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(s);*/
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer("resource/pikaatk.wav");
		sound->Play();
	}
	catch(System::IO::DirectoryNotFoundException^)
	{
		logging("/resource folder not found", LogLevel::Error);
	}
	catch(System::IO::FileNotFoundException^)
	{
		logging("Startup sound file pikaatk.wav not found", LogLevel::Error);
	}
}

System::Void DaOrganiser::MainWindow::MainWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	try
	{
		/*System::Reflection::Assembly^ a = System::Reflection::Assembly::GetExecutingAssembly();
		System::IO::Stream^ s = a->GetManifestResourceStream("pikaslp.wav");
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer(s);*/
		System::Media::SoundPlayer^ sound = gcnew System::Media::SoundPlayer("resource/pikaslp.wav");
		sound->Play();
		Sleep(2000);
	}
	catch(System::IO::DirectoryNotFoundException^)
	{
		logging("/resource folder not found", LogLevel::Error);
	}
	catch(System::IO::FileNotFoundException^)
	{
		logging("Ending sound file pikaslp.wav not found", LogLevel::Error);
	}
}

//column click sorting for entire inventory
System::Void DaOrganiser::MainWindow::listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e)
{
	sortListColumn(e->Column);
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

System::Void DaOrganiser::MainWindow::comboBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if((e->KeyCode == System::Windows::Forms::Keys::Tab) && (comboBox1->DroppedDown == false))
	{
		listView1->TabStop = true;
	}
}

// Keyboard navigation for listView1
System::Void DaOrganiser::MainWindow::listView1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if(e->KeyCode == System::Windows::Forms::Keys::Escape)
	{
		exitProgram();
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::D1)
	{
		sortListColumn(0);
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::D2)
	{
		sortListColumn(1);
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::D3)
	{
		sortListColumn(2);
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::D4)
	{
		sortListColumn(3);
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::D5)
	{
		sortListColumn(4);
	}
}

#pragma endregion