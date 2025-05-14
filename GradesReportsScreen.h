#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <msclr/marshal_cppstd.h>

namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace msclr::interop;

    public ref class GradesReportsScreen : public System::Windows::Forms::Form
    {
    public:
        GradesReportsScreen(void)
        {
            InitializeComponent();
            LoadSampleStudents();
        }

    protected:
        ~GradesReportsScreen()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::ProgressBar^ averageGradeCircle;
        System::Windows::Forms::Button^ uploadExcelBtn;
        System::Windows::Forms::Button^ exportBtn;
        System::Windows::Forms::DataGridView^ studentsTable;
        System::Windows::Forms::TextBox^ gradeInput;
        System::Windows::Forms::ComboBox^ sortOption;
        System::Windows::Forms::Label^ averageLabel;
        System::ComponentModel::Container^ components;
        int currentStudentIndex = 0;

        ref struct Student
        {
            String^ ID;
            String^ Name;
            int Grade;

            Student(String^ id, String^ name, int grade)
            {
                ID = id;
                Name = name;
                Grade = grade;
            }
        };

        System::Collections::Generic::List<Student^>^ studentList = gcnew System::Collections::Generic::List<Student^>();

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // Title
            titleLabel = gcnew Label();
            titleLabel->Text = L"Grades Report";
            titleLabel->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            titleLabel->Location = Point(30, 20);
            this->Controls->Add(titleLabel);

            // Sort Option
            sortOption = gcnew ComboBox();
            sortOption->Items->AddRange(gcnew array<String^>{ "Sort by Name", "Sort by ID" });
            sortOption->SelectedIndex = 0;
            sortOption->DropDownStyle = ComboBoxStyle::DropDownList;
            sortOption->Location = Point(200, 25);
            sortOption->SelectedIndexChanged += gcnew EventHandler(this, &GradesReportsScreen::SortStudents);
            this->Controls->Add(sortOption);

            // Students Table
            studentsTable = gcnew DataGridView();
            studentsTable->Location = Point(30, 60);
            studentsTable->Size = Drawing::Size(500, 250);
            studentsTable->ColumnCount = 3;
            studentsTable->Columns[0]->Name = "ID";
            studentsTable->Columns[1]->Name = "Name";
            studentsTable->Columns[2]->Name = "Grade";
            studentsTable->ReadOnly = true;
            this->Controls->Add(studentsTable);

            // Grade Input TextBox
            gradeInput = gcnew TextBox();
            gradeInput->Location = Point(550, 80);
            gradeInput->Size = Drawing::Size(150, 25);
            gradeInput->Text = "Enter grade...";
            gradeInput->ForeColor = Color::Gray;
            gradeInput->GotFocus += gcnew EventHandler(this, &GradesReportsScreen::gradeInput_Enter);
            gradeInput->LostFocus += gcnew EventHandler(this, &GradesReportsScreen::gradeInput_Leave);
            gradeInput->KeyDown += gcnew KeyEventHandler(this, &GradesReportsScreen::gradeInput_KeyDown);
            this->Controls->Add(gradeInput);

            // Upload Excel Button
            uploadExcelBtn = gcnew Button();
            uploadExcelBtn->Text = "Upload Excel";
            uploadExcelBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);
            uploadExcelBtn->Location = Point(550, 130);
            uploadExcelBtn->Size = Drawing::Size(150, 40);
            uploadExcelBtn->BackColor = Color::FromArgb(40, 100, 200);
            uploadExcelBtn->ForeColor = Color::White;
            uploadExcelBtn->FlatStyle = FlatStyle::Flat;
            uploadExcelBtn->Click += gcnew EventHandler(this, &GradesReportsScreen::uploadExcelBtn_Click);
            uploadExcelBtn->MouseEnter += gcnew EventHandler(this, &GradesReportsScreen::uploadExcelBtn_Hover);
            uploadExcelBtn->MouseLeave += gcnew EventHandler(this, &GradesReportsScreen::uploadExcelBtn_Leave);
            this->Controls->Add(uploadExcelBtn);

            // Export Button
            exportBtn = gcnew Button();
            exportBtn->Text = "Export to Excel";
            exportBtn->Location = Point(550, 190);
            exportBtn->Size = Drawing::Size(150, 40);
            exportBtn->BackColor = Color::Green;
            exportBtn->ForeColor = Color::White;
            exportBtn->Click += gcnew EventHandler(this, &GradesReportsScreen::exportBtn_Click);
            this->Controls->Add(exportBtn);

            // Average Label
            averageLabel = gcnew Label();
            averageLabel->Text = L"Average: -";
            averageLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            averageLabel->Location = Point(550, 250);
            averageLabel->Size = Drawing::Size(150, 30);
            this->Controls->Add(averageLabel);

            // Form Settings
            this->ClientSize = System::Drawing::Size(750, 350);
            this->Name = L"GradesReportsScreen";
            this->Text = L"Grades Reports";
            this->ResumeLayout(false);
        }
#pragma endregion

        void LoadSampleStudents()
        {
            studentList->Add(gcnew Student("1001", "Amina", -1));
            studentList->Add(gcnew Student("1002", "Basma", -1));
            studentList->Add(gcnew Student("1003", "Rahma", -1));
            studentList->Add(gcnew Student("1004", "Dina", -1));
            studentList->Add(gcnew Student("1005", "Ehab", -1));
            SortStudentList();
            UpdateTable();
        }

        static int CompareByName(Student^ a, Student^ b) {
            return String::Compare(a->Name, b->Name);
        }

        static int CompareByID(Student^ a, Student^ b) {
            return String::Compare(a->ID, b->ID);
        }

        void SortStudentList() {
            array<Student^>^ arr = studentList->ToArray();
            if (sortOption->SelectedIndex == 0)
                Array::Sort(arr, gcnew Comparison<Student^>(CompareByName));
            else
                Array::Sort(arr, gcnew Comparison<Student^>(CompareByID));
            studentList = gcnew System::Collections::Generic::List<Student^>(arr);
        }

        void SortStudents(Object^ sender, EventArgs^ e)
        {
            SortStudentList();
            UpdateTable();
            currentStudentIndex = 0;
        }

        void UpdateTable()
        {
            studentsTable->Rows->Clear();
            for each (Student ^ s in studentList)
            {
                studentsTable->Rows->Add(s->ID, s->Name, s->Grade >= 0 ? s->Grade.ToString() : "");
            }
            UpdateAverageGrade();
        }

        void UpdateAverageGrade()
        {
            int total = 0, count = 0;
            for each (Student ^ s in studentList)
            {
                if (s->Grade >= 0)
                {
                    total += s->Grade;
                    count++;
                }
            }
            if (count > 0)
                averageLabel->Text = "Average: " + (total / count).ToString();
            else
                averageLabel->Text = "Average: -";
        }

        void gradeInput_Enter(Object^ sender, EventArgs^ e)
        {
            if (gradeInput->Text == "Enter grade...")
            {
                gradeInput->Text = "";
                gradeInput->ForeColor = Color::Black;
            }
        }

        void gradeInput_Leave(Object^ sender, EventArgs^ e)
        {
            if (gradeInput->Text == "")
            {
                gradeInput->Text = "Enter grade...";
                gradeInput->ForeColor = Color::Gray;
            }
        }

        void gradeInput_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter && currentStudentIndex < studentList->Count)
            {
                int grade;
                if (Int32::TryParse(gradeInput->Text, grade))
                {
                    studentList[currentStudentIndex]->Grade = grade;
                    currentStudentIndex++;
                    UpdateTable();
                    gradeInput->Clear();
                }
                e->SuppressKeyPress = true;
            }
        }

        void uploadExcelBtn_Click(Object^ sender, EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Excel Files|*.xlsx;*.xls";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                MessageBox::Show("Excel file uploaded: " + openFileDialog->FileName);
            }
        }

        void uploadExcelBtn_Hover(Object^ sender, EventArgs^ e)
        {
            uploadExcelBtn->BackColor = Color::FromArgb(30, 80, 160);
        }

        void uploadExcelBtn_Leave(Object^ sender, EventArgs^ e)
        {
            uploadExcelBtn->BackColor = Color::FromArgb(40, 100, 200);
        }

        void exportBtn_Click(Object^ sender, EventArgs^ e)
        {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = "CSV File|*.csv";
            if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    System::String^ managedFilename = saveDialog->FileName;
                    std::string filename = marshal_as<std::string>(managedFilename);

                    std::ofstream file(filename);
                    file << "ID,Name,Grade\n";

                    for each (Student ^ s in studentList)
                    {
                        System::String^ managedID = s->ID;
                        System::String^ managedName = s->Name;

                        std::string id = marshal_as<std::string>(managedID);
                        std::string name = marshal_as<std::string>(managedName);
                        std::string grade = (s->Grade >= 0) ? std::to_string(s->Grade) : "";

                        file << id << "," << name << "," << grade << "\n";
                    }

                    file.close();
                    MessageBox::Show("Grades exported successfully.");
                }
                catch (const std::exception& ex)
                {
                    MessageBox::Show("Error exporting file: " + gcnew String(ex.what()));
                }
            }
        }
    };
}
