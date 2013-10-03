#pragma once

#include "stdafx.h"
#include <string>

namespace DaOrganiser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
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
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  dateAdded;

	private: System::Windows::Forms::ColumnHeader^  details;
	private: System::Windows::Forms::ColumnHeader^  status;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->dateAdded = (gcnew System::Windows::Forms::ColumnHeader());
			this->details = (gcnew System::Windows::Forms::ColumnHeader());
			this->status = (gcnew System::Windows::Forms::ColumnHeader());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(4, 425);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->richTextBox1->Size = System::Drawing::Size(756, 120);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->TabStop = false;
			this->richTextBox1->Text = L"Hello! Welcome to our program! Wheeeeeeee~ :)";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				50)));
			this->tableLayoutPanel1->Controls->Add(this->richTextBox1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->textBox1, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->listView1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 76.82481F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 23.17518F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 34)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(764, 585);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(4, 552);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(756, 26);
			this->textBox1->TabIndex = 0;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::textBox1_KeyDown);
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->dateAdded, this->details, 
				this->status});
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->Location = System::Drawing::Point(4, 4);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(756, 414);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// dateAdded
			// 
			this->dateAdded->Text = L"Date Added";
			this->dateAdded->Width = 203;
			// 
			// details
			// 
			this->details->Text = L"Details";
			this->details->Width = 364;
			// 
			// status
			// 
			this->status->Text = L"Status";
			this->status->Width = 151;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(764, 585);
			this->Controls->Add(this->tableLayoutPanel1);
			this->MaximizeBox = false;
			this->Name = L"MainWindow";
			this->Text = L"MainWindow";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		// Public Methods
	public: void addToList(String^ details);
	public: std::string getUserInput(void);
	public: void clearInputField(void);
	public: void appendToOutput(std::string feedbackToUser);
	//public: void addTaskToList(Task task);  // stub function

		// Events
	private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
};
}

