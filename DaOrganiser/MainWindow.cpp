#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "MainWindow.h"
#include "Parser.h"
#include <cctype>

static Parser parseCmd;

std::string DaOrganiser::MainWindow::sysStringToStdString(String^ stringToConvert)
{
	return msclr::interop::marshal_as <std::string> (stringToConvert);
}

String^ DaOrganiser::MainWindow::stdStringToSysString(std::string stringToConvert)
{
	return msclr::interop::marshal_as <String^> (stringToConvert);
}

void DaOrganiser::MainWindow::addTaskToList(task taskToAdd)
{
	ListViewItem^ itemToAdd=gcnew ListViewItem();

	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartDateAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndDateAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStartTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getEndTimeAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getDetailsAsString()));
	itemToAdd->SubItems->Add(stdStringToSysString(taskToAdd.getStatusAsString()));

	listView1->Items->Add(itemToAdd);
}

std::string DaOrganiser::MainWindow::getUserInput(void)
{
	return sysStringToStdString(textBox1->Text);
}

void DaOrganiser::MainWindow::clearInputField(void)
{
	textBox1->Text="";
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

/////////////////////////
//    Event Handlers   //
/////////////////////////

System::Void DaOrganiser::MainWindow::textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if(e->KeyCode == System::Windows::Forms::Keys::Enter)
	{
		richTextBox1->Text += "\n";
		richTextBox1->Text += textBox1->Text;
		richTextBox1->Text += "\n";
		richTextBox1->Text += stdStringToSysString(parseCmd.parseString(getUserInput()));

		clearInputField();

		richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
		richTextBox1->ScrollToCaret();

		//check if richTextBox1 overflow
		if(richTextBox1->Text->Length > 100000)
		{
			richTextBox1->Text = richTextBox1->Text->Remove(0, 1000);
		}
	}
}

//column click sorting for entire inventory
System::Void DaOrganiser::MainWindow::listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e)
{
	static int _sortColumnInv = 1;
	listView1->ListViewItemSorter = gcnew ListViewItemComparer( e->Column, -1*_sortColumnInv);
	_sortColumnInv*=-1;
}

System::Void DaOrganiser::MainWindow::timer1_Tick(System::Object^  sender, System::EventArgs^  e)
{
	static vector<task> allTasks;
	allTasks=parseCmd.getTasks();
	listView1->Items->Clear();
	for(int i=0; i<allTasks.size(); i++)
	{
		addTaskToList(allTasks[i]);
	}
}

// Following functions implement Autocomplete for commands
System::Void DaOrganiser::MainWindow::comboBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if(e->KeyChar == '-')
	{
		temp = comboBox1->Text;
		comboBox1->DroppedDown = true;
		std::string val = "";
		val += tolower((char) e->KeyChar);
		userInputWord += stdStringToSysString(val);
	}
	else if(e->KeyChar < 48 || ( e->KeyChar >= 58 && e->KeyChar <= 64) || ( e->KeyChar >= 91 && e->KeyChar <= 96) || e->KeyChar > 122)
	{
		//hide autocomplete box if non-alphanumeric key
		userInputWord = "";
		comboBox1->DroppedDown = false;
	}
	else
	{
		std::string val = "";
		val += tolower((char) e->KeyChar);
		userInputWord += stdStringToSysString(val);
		
		array <String^>^ availableCmds = {"-hello", "-add", "-delete", "-haha", "-update"};

		for(int i=0; i<5; i++)
		{
			comboBox1->Items->Remove(availableCmds[i]);

			if(availableCmds[i]->StartsWith(userInputWord))
			{
				comboBox1->Items->Add(availableCmds[i]);
			}
		}
	}
}

System::Void DaOrganiser::MainWindow::comboBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e)
{
	if(e->KeyCode == System::Windows::Forms::Keys::Up)
	{
		if(comboBox1->SelectedIndex > 0)
		{
			comboBox1->SelectedIndex--;
		}
		comboBox1->Text = temp;
		comboBox1->Text += comboBox1->SelectedItem;
		comboBox1->Select(comboBox1->Text->Length, 0);
	}
	else if(e->KeyCode == System::Windows::Forms::Keys::Down)
	{
		if(comboBox1->SelectedIndex < comboBox1->Items->Count - 1)
		{
			comboBox1->SelectedIndex++;
		}
		comboBox1->Text = temp;
		comboBox1->Text += comboBox1->SelectedItem;
		comboBox1->Select(comboBox1->Text->Length, 0);
	}
	else if((e->KeyCode == System::Windows::Forms::Keys::Space) && (comboBox1->DroppedDown == true))
	{
		comboBox1->DroppedDown = false;
		comboBox1->Select(comboBox1->Text->Length, 0);
	}
	else if((e->KeyCode == System::Windows::Forms::Keys::Tab) && (comboBox1->DroppedDown == true))
	{
		//BUG
		//doesnt fire
		comboBox1->DroppedDown = false;
		comboBox1->Text = temp;
		comboBox1->Text += comboBox1->SelectedItem;
		comboBox1->Select(comboBox1->Text->Length, 0);
	}
}