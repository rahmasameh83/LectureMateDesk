#pragma once
#include "AddLectureForm.h"
#include "SubmissionsScreen.h"
#include "GradesReportsScreen.h"
#include "QuizManageScreen.h"
#include "UploadAssignmentForm.h"

namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class DashboardForm : public System::Windows::Forms::Form
    {
    public:
        DashboardForm(void)
        {
            InitializeComponent();
            UpdateDateTime();
        }

    protected:
        ~DashboardForm()
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
        System::Windows::Forms::Label^ dateLabel;
        System::Windows::Forms::Label^ lectureCountLabel;
        System::Windows::Forms::Label^ subjectLabel;
        System::Windows::Forms::Timer^ dateTimer;
        System::Windows::Forms::Button^ uploadLectureBtn;
        int lectureCardY = 140;
        int lectureCounter = 0;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->SuspendLayout();

            upBar = gcnew Panel();
            upBar->BackColor = Color::FromArgb(20, 40, 80);
            upBar->Dock = DockStyle::Top;
            upBar->Height = 120;
            this->Controls->Add(upBar);

            sideBar = gcnew Panel();
            sideBar->BackColor = Color::FromArgb(60, 60, 60);
            sideBar->Dock = DockStyle::Left;
            sideBar->Width = 200;
            this->Controls->Add(sideBar);

            mainContent = gcnew Panel();
            mainContent->Dock = DockStyle::Fill;
            mainContent->BackColor = Color::FromArgb(240, 240, 240);
            this->Controls->Add(mainContent);

            int labelStartX = 20;
            int currentY = 20;

            welcomeLabel = gcnew Label();
            welcomeLabel->Text = L"Welcome Dr. Rahma";
            welcomeLabel->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
            welcomeLabel->ForeColor = Color::White;
            welcomeLabel->AutoSize = true;
            welcomeLabel->Location = Point(labelStartX, currentY);
            upBar->Controls->Add(welcomeLabel);

            currentY += 30;
            dateLabel = gcnew Label();
            dateLabel->Text = L"Date: " + DateTime::Now.ToString("dd-MM-yyyy");
            dateLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            dateLabel->ForeColor = Color::White;
            dateLabel->AutoSize = true;
            dateLabel->Location = Point(labelStartX, currentY);
            upBar->Controls->Add(dateLabel);

            currentY += 20;
            lectureCountLabel = gcnew Label();
            lectureCountLabel->Text = L"Lectures Uploaded: 0";
            lectureCountLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            lectureCountLabel->ForeColor = Color::White;
            lectureCountLabel->AutoSize = true;
            lectureCountLabel->Location = Point(labelStartX, currentY);
            upBar->Controls->Add(lectureCountLabel);

            currentY += 20;
            subjectLabel = gcnew Label();
            subjectLabel->Text = L"Subject: Data Structures";
            subjectLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            subjectLabel->ForeColor = Color::White;
            subjectLabel->AutoSize = true;
            subjectLabel->Location = Point(labelStartX, currentY);
            upBar->Controls->Add(subjectLabel);

            int buttonStartY = 30;

            Button^ addAssignmentBtn = gcnew Button();
            addAssignmentBtn->Text = L"📝 Add Quiz";
            addAssignmentBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            addAssignmentBtn->Size = Drawing::Size(180, 40);
            addAssignmentBtn->Location = Point(10, buttonStartY);
            addAssignmentBtn->BackColor = Color::FromArgb(30, 60, 120);
            addAssignmentBtn->ForeColor = Color::White;
            addAssignmentBtn->TextAlign = ContentAlignment::MiddleLeft;
            addAssignmentBtn->FlatStyle = FlatStyle::Flat;
            addAssignmentBtn->FlatAppearance->BorderSize = 0;
            addAssignmentBtn->MouseEnter += gcnew EventHandler(this, &DashboardForm::OnButtonHover);
            addAssignmentBtn->MouseLeave += gcnew EventHandler(this, &DashboardForm::OnButtonLeave);
            addAssignmentBtn->Click += gcnew EventHandler(this, &DashboardForm::OnAddQuizButtonClick);
            sideBar->Controls->Add(addAssignmentBtn);

            buttonStartY += 50;
            Button^ gradesBtn = gcnew Button();
            gradesBtn->Text = L"📊 Grades";
            gradesBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            gradesBtn->Size = Drawing::Size(180, 40);
            gradesBtn->Location = Point(10, buttonStartY);
            gradesBtn->BackColor = Color::FromArgb(30, 60, 120);
            gradesBtn->ForeColor = Color::White;
            gradesBtn->TextAlign = ContentAlignment::MiddleLeft;
            gradesBtn->FlatStyle = FlatStyle::Flat;
            gradesBtn->FlatAppearance->BorderSize = 0;
            gradesBtn->MouseEnter += gcnew EventHandler(this, &DashboardForm::OnButtonHover);
            gradesBtn->MouseLeave += gcnew EventHandler(this, &DashboardForm::OnButtonLeave);
            gradesBtn->Click += gcnew EventHandler(this, &DashboardForm::OnGradesButtonClick);
            sideBar->Controls->Add(gradesBtn);

            buttonStartY += 50;
            Button^ submissionsBtn = gcnew Button();
            submissionsBtn->Text = L"📥 Submissions";
            submissionsBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            submissionsBtn->Size = Drawing::Size(180, 40);
            submissionsBtn->Location = Point(10, buttonStartY);
            submissionsBtn->BackColor = Color::FromArgb(30, 60, 120);
            submissionsBtn->ForeColor = Color::White;
            submissionsBtn->TextAlign = ContentAlignment::MiddleLeft;
            submissionsBtn->FlatStyle = FlatStyle::Flat;
            submissionsBtn->FlatAppearance->BorderSize = 0;
            submissionsBtn->MouseEnter += gcnew EventHandler(this, &DashboardForm::OnButtonHover);
            submissionsBtn->MouseLeave += gcnew EventHandler(this, &DashboardForm::OnButtonLeave);
            submissionsBtn->Click += gcnew EventHandler(this, &DashboardForm::OnSubmissionsButtonClick);
            sideBar->Controls->Add(submissionsBtn);

            buttonStartY += 50;
            Button^ assignmentUploadBtn = gcnew Button();
            assignmentUploadBtn->Text = L"📄 Upload Assignment";
            assignmentUploadBtn->Font = gcnew Drawing::Font(L"Segoe UI", 10);
            assignmentUploadBtn->Size = Drawing::Size(180, 40);
            assignmentUploadBtn->Location = Point(10, buttonStartY);
            assignmentUploadBtn->BackColor = Color::FromArgb(30, 60, 120);
            assignmentUploadBtn->ForeColor = Color::White;
            assignmentUploadBtn->TextAlign = ContentAlignment::MiddleLeft;
            assignmentUploadBtn->FlatStyle = FlatStyle::Flat;
            assignmentUploadBtn->FlatAppearance->BorderSize = 0;
            assignmentUploadBtn->MouseEnter += gcnew EventHandler(this, &DashboardForm::OnButtonHover);
            assignmentUploadBtn->MouseLeave += gcnew EventHandler(this, &DashboardForm::OnButtonLeave);
            assignmentUploadBtn->Click += gcnew EventHandler(this, &DashboardForm::OnAssignmentUploadClick);
            sideBar->Controls->Add(assignmentUploadBtn);

            uploadLectureBtn = gcnew Button();
            uploadLectureBtn->Text = L"⬆ Upload Lecture";
            uploadLectureBtn->Font = gcnew Drawing::Font(L"Segoe UI", 9);
            uploadLectureBtn->Size = Drawing::Size(140, 30);
            uploadLectureBtn->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;
            uploadLectureBtn->BackColor = Color::FromArgb(20, 120, 80);
            uploadLectureBtn->ForeColor = Color::White;
            uploadLectureBtn->FlatStyle = FlatStyle::Flat;
            uploadLectureBtn->Click += gcnew EventHandler(this, &DashboardForm::OnUploadLectureClick);
            mainContent->Controls->Add(uploadLectureBtn);

            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(900, 600);
            this->Name = L"DashboardForm";
            this->Text = L"LectureMateDesk - Dashboard";
            this->Load += gcnew EventHandler(this, &DashboardForm::OnFormLoad);
            this->Resize += gcnew EventHandler(this, &DashboardForm::OnFormResize);
            this->ResumeLayout(false);

            dateTimer = gcnew Timer();
            dateTimer->Interval = 1000;
            dateTimer->Tick += gcnew EventHandler(this, &DashboardForm::OnTimerTick);
            dateTimer->Start();
        }

        void OnFormLoad(Object^ sender, EventArgs^ e)
        {
            uploadLectureBtn->Location = Point(
                mainContent->Width - uploadLectureBtn->Width - 20,
                mainContent->Height - uploadLectureBtn->Height - 20
            );
            uploadLectureBtn->BringToFront();
        }

        void OnFormResize(Object^ sender, EventArgs^ e)
        {
            uploadLectureBtn->Location = Point(
                mainContent->Width - uploadLectureBtn->Width - 20,
                mainContent->Height - uploadLectureBtn->Height - 20
            );
        }

        void UpdateDateTime()
        {
            dateLabel->Text = L"Date: " + DateTime::Now.ToString("dd-MM-yyyy");
        }

        void OnTimerTick(Object^ sender, EventArgs^ e)
        {
            UpdateDateTime();
        }

        void OnButtonHover(Object^ sender, EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr)
            {
                btn->BackColor = Color::FromArgb(50, 90, 180);
            }
        }

        void OnButtonLeave(Object^ sender, EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr)
            {
                btn->BackColor = Color::FromArgb(30, 60, 120);
            }
        }

        void OnAddQuizButtonClick(Object^ sender, EventArgs^ e)
        {
            QuizManageScreen^ quizManageScreen = gcnew QuizManageScreen();
            quizManageScreen->Show();
        }

        void OnGradesButtonClick(Object^ sender, EventArgs^ e)
        {
            GradesReportsScreen^ gradesReportsScreen = gcnew GradesReportsScreen();
            gradesReportsScreen->Show();
        }

        void OnSubmissionsButtonClick(Object^ sender, EventArgs^ e)
        {
            SubmissionsScreen^ submissionsScreen = gcnew SubmissionsScreen();
            submissionsScreen->Show();
        }

        void OnAssignmentUploadClick(Object^ sender, EventArgs^ e)
        {
            UploadAssignmentForm^ uploadForm = gcnew UploadAssignmentForm();
            uploadForm->ShowDialog();
        }

        void OnUploadLectureClick(Object^ sender, EventArgs^ e)
        {
            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Filter = "PDF Files|*.pdf|All Files|*.*";
            if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                String^ fileName = Path::GetFileName(ofd->FileName);
                Panel^ card = gcnew Panel();
                card->BackColor = Color::White;
                card->BorderStyle = BorderStyle::FixedSingle;
                card->Size = Drawing::Size(300, 60);

                // ✅ هنا التعديل: خلي الكارد يبدأ بعد الـ sidebar + هامش
                int cardStartX = sideBar->Width + 20;
                card->Location = Point(cardStartX, lectureCardY);

                Label^ fileLabel = gcnew Label();
                fileLabel->Text = fileName;
                fileLabel->Location = Point(10, 10);
                fileLabel->Size = Drawing::Size(180, 20);
                card->Controls->Add(fileLabel);

                Button^ editBtn = gcnew Button();
                editBtn->Text = "Edit";
                editBtn->Location = Point(200, 10);
                editBtn->Size = Drawing::Size(40, 20);
                card->Controls->Add(editBtn);

                Button^ deleteBtn = gcnew Button();
                deleteBtn->Text = "X";
                deleteBtn->Location = Point(250, 10);
                deleteBtn->Size = Drawing::Size(20, 20);
                deleteBtn->Click += gcnew EventHandler(this, &DashboardForm::OnDeleteLectureClick);
                deleteBtn->Tag = card;
                card->Controls->Add(deleteBtn);

                mainContent->Controls->Add(card);

                lectureCardY += 70;
                lectureCounter++;
                lectureCountLabel->Text = L"Lectures Uploaded: " + lectureCounter.ToString();
            }
        }


        void OnDeleteLectureClick(Object^ sender, EventArgs^ e)
        {
            Button^ btn = dynamic_cast<Button^>(sender);
            if (btn != nullptr && btn->Tag != nullptr)
            {
                Panel^ card = dynamic_cast<Panel^>(btn->Tag);
                if (card != nullptr)
                {
                    mainContent->Controls->Remove(card);
                    lectureCounter--;
                    lectureCountLabel->Text = L"Lectures Uploaded: " + lectureCounter.ToString();
                }
            }
        }
    };
}
