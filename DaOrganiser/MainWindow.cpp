#include "stdafx.h"
#include "MainWindow.h"
#include <msclr\marshal_cppstd.h>

using namespace DaOrganiser;
using namespace msclr::interop;

/*void MainWindow::addTaskToList(Task task)
{
	// ASSUMPTION: user does not add tasks within 1 second of another
	// use datetime stamp as unique identifier for each task
	System::DateTime timeAdded=System::DateTime::Now;
	ListViewItem^ taskToAdd=gcnew ListViewItem(timeAdded.ToString());
	item->SubItems->Add(task.detail.ToString());
}*/

std::string MainWindow::getUserInput(void)
{
	return marshal_as<std::string> (textBox1->Text);
}

void MainWindow::clearInputField(void)
{
	textBox1->Text="";
}

void MainWindow::appendToOutput(std::string userFeedback)
{
	//check if richTextBox1 overflow
	//if so, delete first 1000 characters
	if(richTextBox1->Text->Length > 100000)
	{
		richTextBox1->Text = richTextBox1->Text->Remove(0, 1000);
	}

	richTextBox1->Text+=marshal_as<String^> (userFeedback);
	richTextBox1->Select(richTextBox1->Text->Length - 1, 0);
	richTextBox1->ScrollToCaret();
	richTextBox1->Text+="\n";
}

void MainWindow::addToList(String^ details)
{
	System::DateTime timeAdded = System::DateTime::Now;
	ListViewItem^ item = gcnew ListViewItem(timeAdded.ToString());
	item->SubItems->Add(details);
	item->SubItems->Add("Not done");
	listView1->Items->Add(item);
	delete item;
}

System::Void MainWindow::textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
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