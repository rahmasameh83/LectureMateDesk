#pragma once

namespace LectureMateDesk {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class UploadAssignmentForm : public System::Windows::Forms::Form
	{
	public:
		UploadAssignmentForm(void)
		{
			InitializeComponent();
		}

	protected:
		~UploadAssignmentForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::Label^ labelSheetName;
		System::Windows::Forms::Label^ labelDueDate;
		System::Windows::Forms::Label^ labelFile;

		System::Windows::Forms::TextBox^ sheetNameTextBox;
		System::Windows::Forms::DateTimePicker^ dueDatePicker;
		System::Windows::Forms::TextBox^ filePathTextBox;
		System::Windows::Forms::Button^ browseButton;
		System::Windows::Forms::Button^ submitButton;
		System::Windows::Forms::OpenFileDialog^ openFileDialog;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();

			// Title Label
			labelTitle = gcnew Label();
			labelTitle->Text = L"Upload New Assignment";
			labelTitle->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
			labelTitle->Location = Point(30, 20);
			labelTitle->AutoSize = true;
			this->Controls->Add(labelTitle);

			// Sheet Name
			labelSheetName = gcnew Label();
			labelSheetName->Text = L"Sheet Name:";
			labelSheetName->Location = Point(30, 80);
			this->Controls->Add(labelSheetName);

			sheetNameTextBox = gcnew TextBox();
			sheetNameTextBox->Location = Point(150, 80);
			sheetNameTextBox->Width = 200;
			this->Controls->Add(sheetNameTextBox);

			// Due Date
			labelDueDate = gcnew Label();
			labelDueDate->Text = L"Due Date:";
			labelDueDate->Location = Point(30, 120);
			this->Controls->Add(labelDueDate);

			dueDatePicker = gcnew DateTimePicker();
			dueDatePicker->Location = Point(150, 120);
			dueDatePicker->Width = 200;
			this->Controls->Add(dueDatePicker);

			// File Picker
			labelFile = gcnew Label();
			labelFile->Text = L"Assignment File:";
			labelFile->Location = Point(30, 160);
			this->Controls->Add(labelFile);

			filePathTextBox = gcnew TextBox();
			filePathTextBox->Location = Point(150, 160);
			filePathTextBox->Width = 200;
			filePathTextBox->ReadOnly = true;
			this->Controls->Add(filePathTextBox);

			browseButton = gcnew Button();
			browseButton->Text = L"Browse";
			browseButton->Location = Point(360, 160);
			browseButton->Click += gcnew EventHandler(this, &UploadAssignmentForm::BrowseButton_Click);
			this->Controls->Add(browseButton);

			// Submit Button
			submitButton = gcnew Button();
			submitButton->Text = L"Submit";
			submitButton->Location = Point(150, 210);
			submitButton->Click += gcnew EventHandler(this, &UploadAssignmentForm::SubmitButton_Click);
			this->Controls->Add(submitButton);

			// OpenFileDialog
			openFileDialog = gcnew OpenFileDialog();
			openFileDialog->Filter = "PDF Files|*.pdf|Word Documents|*.docx|All Files|*.*";

			// Form settings
			this->ClientSize = System::Drawing::Size(500, 300);
			this->Text = L"Upload Assignment";
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		void BrowseButton_Click(Object^ sender, EventArgs^ e)
		{
			if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				filePathTextBox->Text = openFileDialog->FileName;
			}
		}

		void SubmitButton_Click(Object^ sender, EventArgs^ e)
		{
			String^ sheetName = sheetNameTextBox->Text;
			String^ filePath = filePathTextBox->Text;
			DateTime due = dueDatePicker->Value;

			if (sheetName->Length == 0 || filePath->Length == 0)
			{
				MessageBox::Show("Please fill in all fields!");
				return;
			}

			// Simulate saving assignment info
			MessageBox::Show("Assignment uploaded:\nName: " + sheetName + "\nDue: " + due.ToShortDateString());

			this->Close();
		}
	};
}
