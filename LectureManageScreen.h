#pragma once

#include <Windows.h>
#include <iostream>

namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class LectureManageScreen : public System::Windows::Forms::Form
    {
    public:
        LectureManageScreen(void)
        {
            InitializeComponent();
        }

    protected:
        ~LectureManageScreen()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::Button^ uploadLectureBtn;
        System::Windows::Forms::DataGridView^ lecturesTable;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // Title
            titleLabel = gcnew Label();
            titleLabel->Text = L"Lecture Management";
            titleLabel->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            titleLabel->Location = Point(30, 30);
            this->Controls->Add(titleLabel);

            // Upload Lecture Button
            uploadLectureBtn = gcnew Button();
            uploadLectureBtn->Text = "Upload New Lecture";
            uploadLectureBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);
            uploadLectureBtn->Location = Point(30, 80);
            uploadLectureBtn->Size = Drawing::Size(200, 40);
            uploadLectureBtn->BackColor = Color::FromArgb(40, 150, 200);
            uploadLectureBtn->ForeColor = Color::White;
            uploadLectureBtn->FlatStyle = FlatStyle::Flat;
            uploadLectureBtn->Click += gcnew EventHandler(this, &LectureManageScreen::uploadLectureBtn_Click);
            this->Controls->Add(uploadLectureBtn);

            // Lectures Table
            lecturesTable = gcnew DataGridView();
            lecturesTable->Location = Point(30, 150);
            lecturesTable->Size = Drawing::Size(700, 300);
            lecturesTable->ColumnCount = 5;
            lecturesTable->Columns[0]->Name = "Lecture Name";
            lecturesTable->Columns[1]->Name = "Date";
            lecturesTable->Columns[2]->Name = "Type";
            lecturesTable->Columns[3]->Name = "Actions";
            lecturesTable->Columns[4]->Name = "Quiz";

            // Sample Data
            AddLectureRow("OOP Basics", "2025-05-01", "Video");
            AddLectureRow("Data Structures", "2025-05-10", "PDF");
            AddLectureRow("Algorithms", "2025-05-15", "Video");

            this->Controls->Add(lecturesTable);

            // Form Settings
            this->ClientSize = System::Drawing::Size(780, 500);
            this->Name = L"LectureManageScreen";
            this->Text = L"Lecture Management";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void AddLectureRow(String^ name, String^ date, String^ type)
        {
            int rowIndex = lecturesTable->Rows->Add(name, date, type);

            DataGridViewButtonCell^ actionsCell = gcnew DataGridViewButtonCell();
            actionsCell->Value = "Edit | Delete | Preview";
            lecturesTable->Rows[rowIndex]->Cells[3] = actionsCell;

            DataGridViewButtonCell^ quizCell = gcnew DataGridViewButtonCell();
            quizCell->Value = "Manage Quiz";
            lecturesTable->Rows[rowIndex]->Cells[4] = quizCell;

            lecturesTable->CellContentClick += gcnew DataGridViewCellEventHandler(this, &LectureManageScreen::lecturesTable_CellContentClick);
        }

        void uploadLectureBtn_Click(Object^ sender, EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Lecture Files|*.mp4;*.pdf";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                MessageBox::Show("Lecture uploaded: " + openFileDialog->FileName);
                // Future: Add to table logic here
            }
        }

        void lecturesTable_CellContentClick(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                String^ lectureName = lecturesTable->Rows[e->RowIndex]->Cells[0]->Value->ToString();

                if (e->ColumnIndex == 3)
                {
                    MessageBox::Show("Edit/Delete/Preview clicked for: " + lectureName);
                    // Future: Implement edit, delete, preview logic
                }
                else if (e->ColumnIndex == 4)
                {
                    MessageBox::Show("Manage Quiz clicked for: " + lectureName);
                    // Future: Open Quiz Management Screen
                }
            }
        }
    };
}
