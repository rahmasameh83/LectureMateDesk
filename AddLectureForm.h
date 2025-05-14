#pragma once

namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AddLectureForm : public System::Windows::Forms::Form
    {
    public:
        AddLectureForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~AddLectureForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ titleLabel;
        System::Windows::Forms::TextBox^ lectureNameBox;
        System::Windows::Forms::TextBox^ lectureDescBox;
        System::Windows::Forms::ComboBox^ subjectComboBox;
        System::Windows::Forms::Button^ uploadFileBtn;
        System::Windows::Forms::Button^ saveBtn;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // Title
            titleLabel = gcnew Label();
            titleLabel->Text = L"Add New Lecture";
            titleLabel->Font = gcnew Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            titleLabel->Location = Point(30, 30);
            this->Controls->Add(titleLabel);

            // Lecture Name
            Label^ nameLbl = gcnew Label();
            nameLbl->Text = L"Lecture Name:";
            nameLbl->Location = Point(30, 80);
            this->Controls->Add(nameLbl);

            lectureNameBox = gcnew TextBox();
            lectureNameBox->Size = Drawing::Size(300, 25);
            lectureNameBox->Location = Point(150, 75);
            this->Controls->Add(lectureNameBox);

            // Lecture Description
            Label^ descLbl = gcnew Label();
            descLbl->Text = L"Description:";
            descLbl->Location = Point(30, 130);
            this->Controls->Add(descLbl);

            lectureDescBox = gcnew TextBox();
            lectureDescBox->Size = Drawing::Size(300, 60);
            lectureDescBox->Location = Point(150, 125);
            lectureDescBox->Multiline = true;
            this->Controls->Add(lectureDescBox);

            // Subject ComboBox
            Label^ subjectLbl = gcnew Label();
            subjectLbl->Text = L"Subject:";
            subjectLbl->Location = Point(30, 210);
            this->Controls->Add(subjectLbl);

            subjectComboBox = gcnew ComboBox();
            subjectComboBox->Items->AddRange(gcnew cli::array< Object^  >(3) { L"Data Structures", L"Algorithms", L"Operating Systems" });
            subjectComboBox->Size = Drawing::Size(200, 25);
            subjectComboBox->Location = Point(150, 205);
            this->Controls->Add(subjectComboBox);

            // Upload File Button
            uploadFileBtn = gcnew Button();
            uploadFileBtn->Text = L"Upload Lecture File";
            uploadFileBtn->Size = Drawing::Size(200, 35);
            uploadFileBtn->Location = Point(150, 260);
            uploadFileBtn->BackColor = Color::FromArgb(50, 120, 200);
            uploadFileBtn->ForeColor = Color::White;
            uploadFileBtn->FlatStyle = FlatStyle::Flat;
            uploadFileBtn->FlatAppearance->BorderSize = 0;
            uploadFileBtn->Click += gcnew EventHandler(this, &AddLectureForm::uploadFileBtn_Click);
            this->Controls->Add(uploadFileBtn);

            // Save Button
            saveBtn = gcnew Button();
            saveBtn->Text = L"Save Lecture";
            saveBtn->Size = Drawing::Size(150, 40);
            saveBtn->Location = Point(150, 320);
            saveBtn->BackColor = Color::FromArgb(40, 160, 100);
            saveBtn->ForeColor = Color::White;
            saveBtn->FlatStyle = FlatStyle::Flat;
            saveBtn->FlatAppearance->BorderSize = 0;
            saveBtn->Click += gcnew EventHandler(this, &AddLectureForm::saveBtn_Click);
            this->Controls->Add(saveBtn);

            // Form Settings
            this->ClientSize = System::Drawing::Size(500, 400);
            this->Name = L"AddLectureForm";
            this->Text = L"Add Lecture";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void uploadFileBtn_Click(Object^ sender, EventArgs^ e)
        {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "PDF Files|*.pdf|All Files|*.*";
            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                MessageBox::Show("File Selected: " + openFileDialog->FileName);
            }
        }

        void saveBtn_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show("Lecture Saved Successfully!");
        }
    };
}
