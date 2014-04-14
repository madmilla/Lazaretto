
/**
## Autor Daan Joling.		- Design
## Autor Lars Veenendaal	- Implementation of the Lazaretto controller
##							- Exceptions for empty values add
##							- Modified the design
*/#pragma once
#include <msclr/marshal_cppstd.h>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#include <string.h>
#include "controller.h"
#include "stopwatch.h"


namespace guiApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}
	private: System::Windows::Forms::TextBox^  textBox2;

	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	public:
		System::Windows::Forms::TextBox^  textBox1;
		
	protected:
			~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
		System::Windows::Forms::OpenFileDialog^  openFileDialog1;
		System::Windows::Forms::PictureBox^  pictureBox1;
		System::Windows::Forms::Button^  button1;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Location = System::Drawing::Point(12, 26);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(357, 243);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->WaitOnLoad = true;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 280);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(83, 30);
			this->button1->TabIndex = 1;
			this->button1->Text = L"find license";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(12, 323);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(357, 109);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(102, 288);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(267, 20);
			this->textBox2->TabIndex = 4;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(437, 26);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(386, 243);
			this->textBox4->TabIndex = 6;
			this->textBox4->Text = L"Originele Layout: Daan Joling\r\nModified Layout: Lars Veenendaal\r\nException handli"
				L"ng: Lars Veenendaal";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Image:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(102, 274);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Image path:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 309);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Results:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(232, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(137, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"License Plate Finder V0.6.4";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(384, 444);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"registration numbers recognition";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
				
					 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
					 openFileDialog1->ShowDialog();
					 String^ resultFileName = openFileDialog1->FileName;

					 if (resultFileName != ""){
						 pictureBox1->Load(openFileDialog1->FileName);
						 pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
						 this->textBox2->Text = openFileDialog1->FileName;
						 delete openFileDialog1;
					 }
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 // run controller to do the find plate algorithm 			
		this->textBox1->Text = "";
		Controller * processing = new Controller();
		System::String^ file = this->textBox2->Text;
		if (file == ""){
			// Kijk eens daan :)
		} else{
			this->textBox1->Text += "Processing";
			std::string filename = msclr::interop::marshal_as< std::string >(file);
			stopwatch timeKeeper;

			timeKeeper.reset_the_clock();
			string result = processing->Find_licenseplate(filename);
			this->textBox1->Text = "";
			String^ resultCadet = gcnew String(result.c_str());
			string timec = timeKeeper.printTimePast();
			String^ str2 = gcnew String(timec.c_str());
			this->textBox1->Text += "\r\n";
			this->textBox1->Text += resultCadet;
			this->textBox1->Text += "\r\n";
			this->textBox1->Text += str2;
			delete processing;
			
			timeKeeper.~stopwatch();
		}

	}			 
};
}
