#pragma once
//#include "LectureScreen.h"
//#include "AssignmentsScreen.h"
//#include "SubmissionsScreen.h"

namespace LectureMateDesk {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class StudentDashboard : public System::Windows::Forms::Form
	{
	public:
		StudentDashboard(void)
		{
			InitializeComponent();
			UpdateDateTime();
		}

	protected:
		~StudentDashboard()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ upBar;
		System::Windows::Forms::Panel^ sideBar;
		System::Windows::Forms::Panel^ mainContent;
		System::Windows::Forms::Label^ welcomeLabel;
		System::Windows::Forms::Label^ idLabel;
		System::Windows::Forms::Label^ dateLabel;
		System::Windows::Forms::ComboBox^ courseSelector;
		System::Windows::Forms::Timer^ dateTimer;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->SuspendLayout();

			upBar = gcnew Panel();
			upBar->BackColor = Color::FromArgb(230, 230, 230);
			upBar->Dock = DockStyle::Top;
			upBar->Height = 120;
			this->Controls->Add(upBar);

			sideBar = gcnew Panel();
			sideBar->BackColor = Color::FromArgb(20, 40, 80);
			sideBar->Dock = DockStyle::Left;
			sideBar->Width = 200;
			this->Controls->Add(sideBar);

			mainContent = gcnew Panel();
			mainContent->Dock = DockStyle::Fill;
			mainContent->BackColor = Color::White;
			this->Controls->Add(mainContent);

			welcomeLabel = gcnew Label();
			welcomeLabel->Text = L"Welcome Rahma";
			welcomeLabel->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
			welcomeLabel->ForeColor = Color::Black;
			welcomeLabel->AutoSize = true;
			welcomeLabel->Location = Point(20, 20);
			upBar->Controls->Add(welcomeLabel);

			idLabel = gcnew Label();
			idLabel->Text = L"ID: 2220159";
			idLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10);
			idLabel->ForeColor = Color::Black;
			idLabel->AutoSize = true;
			idLabel->Location = Point(20, 50);
			upBar->Controls->Add(idLabel);

			dateLabel = gcnew Label();
			dateLabel->Text = L"Date: " + DateTime::Now.ToString("dd-MM-yyyy HH:mm:ss");
			dateLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10);
			dateLabel->ForeColor = Color::Black;
			dateLabel->AutoSize = true;
			dateLabel->Location = Point(20, 80);
			upBar->Controls->Add(dateLabel);

			courseSelector = gcnew ComboBox();
			courseSelector->Font = gcnew Drawing::Font(L"Segoe UI", 10);
			courseSelector->DropDownStyle = ComboBoxStyle::DropDownList;
			courseSelector->Items->AddRange(gcnew array<String^>{ "Data Structures", "OOP", "Algorithms" });
			courseSelector->SelectedIndex = 0;
			courseSelector->Width = 160;
			courseSelector->Location = Point(20, 20);
			sideBar->Controls->Add(courseSelector);

			// Add sidebar buttons below selector
			int btnY = 70;
			array<String^>^ buttonTexts = { "📚 Lectures", "📄 Assignments", "📥 Submissions", "📊 Grades" };
			for each (String ^ text in buttonTexts)
			{
				Button^ btn = gcnew Button();
				btn->Text = text;
				btn->Font = gcnew Drawing::Font(L"Segoe UI", 10);
				btn->Size = Drawing::Size(180, 40);
				btn->Location = Point(10, btnY);
				btn->BackColor = Color::FromArgb(30, 60, 120);
				btn->ForeColor = Color::White;
				btn->FlatStyle = FlatStyle::Flat;
				btn->FlatAppearance->BorderSize = 0;
				sideBar->Controls->Add(btn);
				btnY += 50;
			}

			this->ClientSize = Drawing::Size(900, 600);
			this->Name = L"StudentDashboard";
			this->Text = L"LectureMateDesk - Student Dashboard";
			this->Load += gcnew EventHandler(this, &StudentDashboard::OnLoad);
			this->ResumeLayout(false);

			dateTimer = gcnew Timer();
			dateTimer->Interval = 1000;
			dateTimer->Tick += gcnew EventHandler(this, &StudentDashboard::OnTick);
			dateTimer->Start();
		}

		void OnLoad(Object^ sender, EventArgs^ e)
		{
			UpdateDateTime();
		}

		void OnTick(Object^ sender, EventArgs^ e)
		{
			UpdateDateTime();
		}

		void UpdateDateTime()
		{
			dateLabel->Text = L"Date: " + DateTime::Now.ToString("dd-MM-yyyy HH:mm:ss");
		}
	};
} // namespace
