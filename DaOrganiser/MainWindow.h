#pragma once

#include "stdafx.h"
#include <vector>
#include "ListViewItemComparer.h"
#include "Task.h"

namespace DaOrganiser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		void* progController;
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  id;



	private: System::Windows::Forms::ColumnHeader^  details;
	private: System::Windows::Forms::ColumnHeader^  status;
	private: System::Windows::Forms::ColumnHeader^  start;
	private: System::Windows::Forms::ColumnHeader^  end;








	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ColumnHeader^  kind;



	private: System::ComponentModel::IContainer^  components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->id = (gcnew System::Windows::Forms::ColumnHeader());
			this->start = (gcnew System::Windows::Forms::ColumnHeader());
			this->end = (gcnew System::Windows::Forms::ColumnHeader());
			this->details = (gcnew System::Windows::Forms::ColumnHeader());
			this->status = (gcnew System::Windows::Forms::ColumnHeader());
			this->kind = (gcnew System::Windows::Forms::ColumnHeader());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::Azure;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->DetectUrls = false;
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Verdana", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(1, 420);
			this->richTextBox1->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->richTextBox1->Size = System::Drawing::Size(1049, 126);
			this->richTextBox1->TabIndex = 2;
			this->richTextBox1->TabStop = false;
			this->richTextBox1->Text = L"Welcome to DaOrganiser!\n";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::SystemColors::Control;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				50)));
			this->tableLayoutPanel1->Controls->Add(this->comboBox1, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->richTextBox1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->listView1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 76.82481F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 23.17518F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 34)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1051, 581);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// comboBox1
			// 
			this->comboBox1->AllowDrop = true;
			this->comboBox1->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox1->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->comboBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Verdana", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(0, 549);
			this->comboBox1->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(1051, 30);
			this->comboBox1->Sorted = true;
			this->comboBox1->TabIndex = 0;
			this->comboBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::comboBox1_KeyDown);
			this->comboBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::comboBox1_KeyPress);
			this->comboBox1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::comboBox1_KeyUp);
			this->comboBox1->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainWindow::comboBox1_PreviewKeyDown);
			// 
			// listView1
			// 
			this->listView1->AllowColumnReorder = true;
			this->listView1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->id, this->start, 
				this->end, this->details, this->status, this->kind});
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->Font = (gcnew System::Drawing::Font(L"Verdana", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listView1->ForeColor = System::Drawing::Color::Black;
			this->listView1->FullRowSelect = true;
			this->listView1->Location = System::Drawing::Point(1, 0);
			this->listView1->Margin = System::Windows::Forms::Padding(1, 0, 1, 1);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(1049, 419);
			this->listView1->TabIndex = 1;
			this->listView1->TileSize = System::Drawing::Size(228, 36);
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &MainWindow::listView1_ColumnClick);
			this->listView1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::listView1_KeyDown);
			// 
			// id
			// 
			this->id->Text = L"ID";
			this->id->Width = 73;
			// 
			// start
			// 
			this->start->DisplayIndex = 2;
			this->start->Text = L"Start";
			this->start->Width = 205;
			// 
			// end
			// 
			this->end->DisplayIndex = 3;
			this->end->Text = L"End";
			this->end->Width = 188;
			// 
			// details
			// 
			this->details->DisplayIndex = 1;
			this->details->Text = L"Details";
			this->details->Width = 264;
			// 
			// status
			// 
			this->status->Text = L"Status";
			this->status->Width = 147;
			// 
			// kind
			// 
			this->kind->Text = L"Kind";
			this->kind->Width = 126;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1051, 581);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(5, 3, 5, 3);
			this->MaximizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"DaOrganiser";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainWindow::MainWindow_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		// Private Members
	private: String^ userInputWord;
	private: String^ userPrevInput;

		// Public Methods
	//public: void addToList(String^ details);
	public: std::string getUserInput(void);
	public: void clearInputField(void);
	public: void appendToOutput(std::string feedbackToUser);
	public: void addTaskToList(Task taskToAdd);
	public: void updateList(void);
	public: void displaySearchResult(std::vector<Task> searchResult);
	public: void sortListColumn(unsigned int col);
	public: std::string sysStringToStdString(String ^ stringToConvert);
	public: String^ stdStringToSysString(std::string stringToConvert);
	public: void exitProgram(void);

		// Private Methods
	private: System::Drawing::Color changeColor(String^);
	private: void suggestResults(void);
	private: void openSuggestionBox(void);
	private: void closeSuggestionBox(void);
	private: void commitSelectedSuggestion(void);
	private: void setCaretToEnd(void);

		// Events
	private: System::Void listView1_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);
	private: System::Void comboBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	private: System::Void comboBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void comboBox1_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e);
	private: System::Void MainWindow_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void comboBox1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
	private: System::Void listView1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
};
}

