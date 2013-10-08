#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "MainWindow.h"

/*void MainWindow::addTaskToList(Task task)
{
	// ASSUMPTION: user does not add tasks within 1 second of another
	// use datetime stamp as unique identifier for each task
	System::DateTime timeAdded=System::DateTime::Now;
	ListViewItem^ taskToAdd=gcnew ListViewItem(timeAdded.ToString());
	item->SubItems->Add(task.detail.ToString());
}*/

std::string DaOrganiser::MainWindow::getUserInput(void)
{
	return msclr::interop::marshal_as<std::string> (textBox1->Text);
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

	richTextBox1->Text+=msclr::interop::marshal_as<String^> (userFeedback);
	richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
	richTextBox1->ScrollToCaret();
	richTextBox1->Text+="\n";
}

void DaOrganiser::MainWindow::addToList(String^ details)
{
	System::DateTime timeAdded = System::DateTime::Now;
	ListViewItem^ item = gcnew ListViewItem(timeAdded.ToString());
	item->SubItems->Add(details);
	item->SubItems->Add("Not done");
	listView1->Items->Add(item);
	delete item;
}

/////////////////////////
//    Event Handlers   //
/////////////////////////

System::Void DaOrganiser::MainWindow::textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if(e->KeyCode == System::Windows::Forms::Keys::Enter)
	{
		richTextBox1->Text += "\n";
		richTextBox1->Text += textBox1->Text;
		addToList(textBox1->Text);
		textBox1->Text = "";

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