#pragma once

namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class SubmissionsScreen : public System::Windows::Forms::Form
    {
    public:
        SubmissionsScreen(void)
        {
            InitializeComponent();
        }

    protected:
        ~SubmissionsScreen()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::DataGridView^ submissionsGrid;
        System::Windows::Forms::ProgressBar^ progressBar;
        System::Windows::Forms::ComboBox^ filterCombo;
        System::ComponentModel::Container^ components;

        int totalSubmissions = 3;
        int submittedCount = 1;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // Title
            titleLabel = gcnew Label();
            titleLabel->Text = L"Student Submissions";
            titleLabel->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            titleLabel->Location = Point(30, 30);
            titleLabel->AutoSize = true;
            this->Controls->Add(titleLabel);

            // Filter Dropdown
            filterCombo = gcnew ComboBox();
            filterCombo->Items->AddRange(gcnew cli::array<Object^> { "All", "Submitted", "Late", "Missing" });
            filterCombo->SelectedIndex = 0;
            filterCombo->DropDownStyle = ComboBoxStyle::DropDownList;
            filterCombo->Location = Point(600, 35);
            filterCombo->Width = 150;
            filterCombo->SelectedIndexChanged += gcnew EventHandler(this, &SubmissionsScreen::filterCombo_SelectedIndexChanged);
            this->Controls->Add(filterCombo);

            // ProgressBar
            progressBar = gcnew ProgressBar();
            progressBar->Location = Point(30, 450);
            progressBar->Size = Drawing::Size(720, 20);
            progressBar->Value = (int)((submittedCount / (float)totalSubmissions) * 100);
            this->Controls->Add(progressBar);

            // DataGridView
            submissionsGrid = gcnew DataGridView();
            submissionsGrid->Location = Point(30, 80);
            submissionsGrid->Size = Drawing::Size(720, 350);
            submissionsGrid->ColumnCount = 3;
            submissionsGrid->Columns[0]->Name = "Student Name";
            submissionsGrid->Columns[1]->Name = "Sheet Name";
            submissionsGrid->Columns[2]->Name = "Status";

            // Add Buttons Columns
            DataGridViewButtonColumn^ downloadBtnCol = gcnew DataGridViewButtonColumn();
            downloadBtnCol->Name = "Download";
            downloadBtnCol->HeaderText = "";
            downloadBtnCol->Text = "Download File";
            downloadBtnCol->UseColumnTextForButtonValue = true;
            submissionsGrid->Columns->Add(downloadBtnCol);

            DataGridViewButtonColumn^ evalBtnCol = gcnew DataGridViewButtonColumn();
            evalBtnCol->Name = "Evaluate";
            evalBtnCol->HeaderText = "";
            evalBtnCol->Text = "Evaluate";
            evalBtnCol->UseColumnTextForButtonValue = true;
            submissionsGrid->Columns->Add(evalBtnCol);

            submissionsGrid->AllowUserToAddRows = false;
            submissionsGrid->ReadOnly = true;

            submissionsGrid->CellContentClick += gcnew DataGridViewCellEventHandler(this, &SubmissionsScreen::submissionsGrid_CellContentClick);
            submissionsGrid->CellMouseEnter += gcnew DataGridViewCellEventHandler(this, &SubmissionsScreen::submissionsGrid_CellMouseEnter);
            submissionsGrid->CellMouseLeave += gcnew DataGridViewCellEventHandler(this, &SubmissionsScreen::submissionsGrid_CellMouseLeave);

            this->Controls->Add(submissionsGrid);

            // Sample Data
            AddRow("Rahma Sameh", "Sheet 1", "Submitted");
            AddRow("Mona Yasser", "Sheet 2", "Late");
            AddRow("Menna Ahmed ", "Sheet 1", "Missing");

            // Form Settings
            this->ClientSize = System::Drawing::Size(800, 500);
            this->Name = L"SubmissionsScreen";
            this->Text = L"Submissions";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

            this->MaximizeBox = false;
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void AddRow(String^ student, String^ sheet, String^ status)
        {
            submissionsGrid->Rows->Add(student, sheet, status);
            int rowIdx = submissionsGrid->Rows->Count - 1;

            DataGridViewCellStyle^ style = gcnew DataGridViewCellStyle();
            if (status == "Submitted") {
                style->BackColor = Color::FromArgb(40, 160, 100);
                style->ForeColor = Color::White;
                submittedCount++;
            }
            else if (status == "Late") {
                style->BackColor = Color::FromArgb(220, 170, 20);
                style->ForeColor = Color::White;
            }
            else if (status == "Missing") {
                style->BackColor = Color::FromArgb(200, 50, 50);
                style->ForeColor = Color::White;
            }

            submissionsGrid->Rows[rowIdx]->Cells[2]->Style = style;
        }

        void submissionsGrid_CellContentClick(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                if (submissionsGrid->Columns[e->ColumnIndex]->Name == "Download")
                {
                    MessageBox::Show("Downloading file for: " + submissionsGrid->Rows[e->RowIndex]->Cells[0]->Value->ToString());
                }
                else if (submissionsGrid->Columns[e->ColumnIndex]->Name == "Evaluate")
                {
                    MessageBox::Show("Evaluating submission of: " + submissionsGrid->Rows[e->RowIndex]->Cells[0]->Value->ToString());
                }
            }
        }

        void submissionsGrid_CellMouseEnter(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && (submissionsGrid->Columns[e->ColumnIndex]->Name == "Download" || submissionsGrid->Columns[e->ColumnIndex]->Name == "Evaluate"))
            {
                submissionsGrid->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = Color::FromArgb(30, 60, 120);
                submissionsGrid->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->ForeColor = Color::White;
            }
        }

        void submissionsGrid_CellMouseLeave(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0 && (submissionsGrid->Columns[e->ColumnIndex]->Name == "Download" || submissionsGrid->Columns[e->ColumnIndex]->Name == "Evaluate"))
            {
                submissionsGrid->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = submissionsGrid->DefaultCellStyle->BackColor;
                submissionsGrid->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->ForeColor = Color::Black;
            }
        }

        void filterCombo_SelectedIndexChanged(Object^ sender, EventArgs^ e)
        {
            String^ selectedStatus = filterCombo->SelectedItem->ToString();

            for (int i = 0; i < submissionsGrid->Rows->Count; i++)
            {
                bool showRow = (selectedStatus == "All") || (submissionsGrid->Rows[i]->Cells[2]->Value->ToString() == selectedStatus);
                submissionsGrid->Rows[i]->Visible = showRow;
            }
        }
    };
}
