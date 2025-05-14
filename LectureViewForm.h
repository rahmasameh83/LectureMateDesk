#pragma once

namespace LectureMateDesk {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class LectureViewForm : public System::Windows::Forms::Form
	{
	public:
		LectureViewForm(String^ studentName, String^ studentID)
		{
			InitializeComponent();
			this->studentName = studentName;
			this->studentID = studentID;
			UpdateDateTime();
		}

	protected:
		~LectureViewForm()
		{
			if (components)
				delete components;
		}

	private:
		String^ studentName;
		String^ studentID;
		System::Windows::Forms::Panel^ upBar;
		System::Windows::Forms::Panel^ lecturePanel;
		System::Windows::Forms::Label^ studentLabel;
		System::Windows::Forms::Label^ dateLabel;
		System::Windows::Forms::Timer^ dateTimer;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->SuspendLayout();

			// Up Bar
			upBar = gcnew Panel();
			upBar->Dock = DockStyle::Top;
			upBar->Height = 80;
			upBar->BackColor = Color::FromArgb(240, 240, 240);
			this->Controls->Add(upBar);

			studentLabel = gcnew Label();
			studentLabel->Text = "Welcome " + studentName + " | ID: " + studentID;
			studentLabel->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
			studentLabel->Location = Point(20, 20);
			studentLabel->AutoSize = true;
			upBar->Controls->Add(studentLabel);

			dateLabel = gcnew Label();
			dateLabel->Font = gcnew Drawing::Font("Segoe UI", 10);
			dateLabel->Location = Point(20, 50);
			dateLabel->AutoSize = true;
			upBar->Controls->Add(dateLabel);

			// Lecture Panel
			lecturePanel = gcnew Panel();
			lecturePanel->Dock = DockStyle::Fill;
			lecturePanel->BackColor = Color::White;
			this->Controls->Add(lecturePanel);

			this->Text = "Lectures";
			this->ClientSize = Drawing::Size(800, 600);
			this->Load += gcnew EventHandler(this, &LectureViewForm::OnFormLoad);
			this->ResumeLayout(false);

			dateTimer = gcnew Timer();
			dateTimer->Interval = 1000;
			dateTimer->Tick += gcnew EventHandler(this, &LectureViewForm::OnTimerTick);
			dateTimer->Start();
		}

		void OnFormLoad(Object^ sender, EventArgs^ e)
		{
			LoadLectures();
		}

		void UpdateDateTime()
		{
			dateLabel->Text = "Date: " + DateTime::Now.ToString("dd-MM-yyyy hh:mm:ss tt");
		}

		void OnTimerTick(Object^ sender, EventArgs^ e)
		{
			UpdateDateTime();
		}

		void LoadLectures()
		{
			// بيانات مؤقتة (هنربطها بالداتا بيز لاحقًا)
			array<String^>^ lectureFiles = gcnew array<String^> {
				"Week 1 - Introduction.pdf",
					"Week 2 - Arrays.pdf",
					"Week 3 - Linked Lists.pdf"
			};

			int y = 20;
			for each (String ^ fileName in lectureFiles)
			{
				Panel^ lectureCard = gcnew Panel();
				lectureCard->Size = Drawing::Size(700, 50);
				lectureCard->Location = Point(30, y);
				lectureCard->BackColor = Color::FromArgb(240, 240, 240);
				lectureCard->BorderStyle = BorderStyle::FixedSingle;

				Label^ fileLabel = gcnew Label();
				fileLabel->Text = fileName;
				fileLabel->Font = gcnew Drawing::Font("Segoe UI", 10);
				fileLabel->Location = Point(10, 15);
				fileLabel->AutoSize = true;

				Button^ downloadBtn = gcnew Button();
				downloadBtn->Text = "Download";
				downloadBtn->Size = Drawing::Size(90, 30);
				downloadBtn->Location = Point(580, 10);
				downloadBtn->BackColor = Color::FromArgb(20, 120, 80);
				downloadBtn->ForeColor = Color::White;
				downloadBtn->FlatStyle = FlatStyle::Flat;
				downloadBtn->Click += gcnew EventHandler(this, &LectureViewForm::OnDownloadClick);
				downloadBtn->Tag = fileName;

				lectureCard->Controls->Add(fileLabel);
				lectureCard->Controls->Add(downloadBtn);

				lecturePanel->Controls->Add(lectureCard);
				y += 60;
			}
		}

		void OnDownloadClick(Object^ sender, EventArgs^ e)
		{
			Button^ btn = dynamic_cast<Button^>(sender);
			if (btn != nullptr)
			{
				String^ fileName = dynamic_cast<String^>(btn->Tag);
				// لاحقًا هنا نحمل الملف فعليًا من السيرفر أو من الداتا بيز
				MessageBox::Show("Downloading: " + fileName, "Download", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
		}
	};
}
