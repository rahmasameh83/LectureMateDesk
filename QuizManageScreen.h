#pragma once


namespace LectureMateDesk {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class QuizManageScreen : public System::Windows::Forms::Form
    {
    public:
        QuizManageScreen(void)
        {
            InitializeComponent();
        }

    protected:
        ~QuizManageScreen()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::DataGridView^ quizTable;
        System::Windows::Forms::Button^ addQuestionBtn;
        System::Windows::Forms::Button^ deleteQuestionBtn;
        System::Windows::Forms::GroupBox^ previewBox;
        System::Windows::Forms::Label^ previewQuestion;
        System::Windows::Forms::RadioButton^ optionA;
        System::Windows::Forms::RadioButton^ optionB;
        System::Windows::Forms::Button^ submitBtn;
        System::Windows::Forms::Label^ resultLabel;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // Quiz Table
            quizTable = gcnew DataGridView();
            quizTable->Location = Point(30, 30);
            quizTable->Size = Drawing::Size(800, 300);
            quizTable->Columns->Add("Question", "Question");
            quizTable->Columns->Add("CorrectAnswer", "Correct Answer");
            quizTable->Rows->Add("What is OOP?", "Object Oriented");
            quizTable->SelectionChanged += gcnew EventHandler(this, &QuizManageScreen::quizTable_SelectionChanged);
            quizTable->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &QuizManageScreen::quizTable_CellDoubleClick);
            this->Controls->Add(quizTable);

            // Add Question Button
            addQuestionBtn = gcnew Button();
            addQuestionBtn->Text = "➕ Add Question";
            addQuestionBtn->Location = Point(30, 350);
            addQuestionBtn->Size = Drawing::Size(150, 40);
            addQuestionBtn->BackColor = Color::FromArgb(40, 120, 180);
            addQuestionBtn->ForeColor = Color::White;
            addQuestionBtn->FlatStyle = FlatStyle::Flat;
            addQuestionBtn->Click += gcnew EventHandler(this, &QuizManageScreen::addQuestionBtn_Click);
            this->Controls->Add(addQuestionBtn);

            // Delete Question Button
            deleteQuestionBtn = gcnew Button();
            deleteQuestionBtn->Text = "🗑️ Delete Question";
            deleteQuestionBtn->Location = Point(200, 350);
            deleteQuestionBtn->Size = Drawing::Size(150, 40);
            deleteQuestionBtn->BackColor = Color::FromArgb(180, 40, 40);
            deleteQuestionBtn->ForeColor = Color::White;
            deleteQuestionBtn->FlatStyle = FlatStyle::Flat;
            deleteQuestionBtn->Click += gcnew EventHandler(this, &QuizManageScreen::deleteQuestionBtn_Click);
            this->Controls->Add(deleteQuestionBtn);

            // Preview Box
            previewBox = gcnew GroupBox();
            previewBox->Text = L"Quiz Preview";
            previewBox->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            previewBox->Location = Point(30, 420);
            previewBox->Size = Drawing::Size(800, 180);
            this->Controls->Add(previewBox);

            // Preview Question
            previewQuestion = gcnew Label();
            previewQuestion->Text = L"Q: What is OOP?";
            previewQuestion->Location = Point(20, 30);
            previewQuestion->Size = Drawing::Size(500, 25);
            previewBox->Controls->Add(previewQuestion);

            // Option A
            optionA = gcnew RadioButton();
            optionA->Text = "Object Oriented";
            optionA->Location = Point(40, 70);
            previewBox->Controls->Add(optionA);

            // Option B
            optionB = gcnew RadioButton();
            optionB->Text = "Old Operation";
            optionB->Location = Point(40, 100);
            previewBox->Controls->Add(optionB);

            // Submit Button
            submitBtn = gcnew Button();
            submitBtn->Text = "Submit Answer";
            submitBtn->Location = Point(600, 70);
            submitBtn->Size = Drawing::Size(150, 40);
            submitBtn->BackColor = Color::FromArgb(40, 120, 180);
            submitBtn->ForeColor = Color::White;
            submitBtn->FlatStyle = FlatStyle::Flat;
            submitBtn->Click += gcnew EventHandler(this, &QuizManageScreen::submitBtn_Click);
            previewBox->Controls->Add(submitBtn);

            // Result Label
            resultLabel = gcnew Label();
            resultLabel->Text = "";
            resultLabel->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            resultLabel->ForeColor = Color::Green;
            resultLabel->Location = Point(40, 140);
            previewBox->Controls->Add(resultLabel);

            // Form Settings
            this->ClientSize = System::Drawing::Size(900, 650);
            this->Name = L"QuizManageScreen";
            this->Text = L"LectureMateDesk - Quiz Management";
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        void addQuestionBtn_Click(Object^ sender, EventArgs^ e)
        {
            quizTable->Rows->Add("New Question?", "Correct Answer");
        }

        void deleteQuestionBtn_Click(Object^ sender, EventArgs^ e)
        {
            if (quizTable->SelectedRows->Count > 0)
            {
                quizTable->Rows->RemoveAt(quizTable->SelectedRows[0]->Index);
            }
        }

        void submitBtn_Click(Object^ sender, EventArgs^ e)
        {
            if (optionA->Checked)
            {
                resultLabel->ForeColor = Color::Green;
                resultLabel->Text = "✅ Correct! Well done.";
            }
            else if (optionB->Checked)
            {
                resultLabel->ForeColor = Color::Red;
                resultLabel->Text = "❌ Wrong answer. Try again!";
            }
            else
            {
                MessageBox::Show("Please select an answer first!", "No Selection");
            }
        }

        void quizTable_SelectionChanged(Object^ sender, EventArgs^ e)
        {
            if (quizTable->SelectedRows->Count > 0)
            {
                updatePreview();
            }
        }

        void quizTable_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                DataGridViewRow^ selectedRow = quizTable->Rows[e->RowIndex];
                String^ currentQuestion = selectedRow->Cells[0]->Value->ToString();
                String^ currentAnswer = selectedRow->Cells[1]->Value->ToString();

                // Simple InputBox Style Dialog for Edit
               // String^ newQuestion = Microsoft::VisualBasic::Interaction::InputBox("Edit Question:", "Edit", currentQuestion);
                //if (newQuestion != "")
                //{
                //    selectedRow->Cells[0]->Value = newQuestion;
               // }

              //  String^ newAnswer = Microsoft::VisualBasic::Interaction::InputBox("Edit Correct Answer:", "Edit", currentAnswer);
               // if (newAnswer != "")
               // {
                //    selectedRow->Cells[1]->Value = newAnswer;
               // }

                updatePreview();
            }
        }

        void updatePreview()
        {
            if (quizTable->SelectedRows->Count > 0)
            {
                String^ question = quizTable->SelectedRows[0]->Cells[0]->Value->ToString();
                String^ correctAnswer = quizTable->SelectedRows[0]->Cells[1]->Value->ToString();

                previewQuestion->Text = "Q: " + question;
                optionA->Text = correctAnswer;
                optionB->Text = "Wrong Option";
                resultLabel->Text = "";
                optionA->Checked = false;
                optionB->Checked = false;
            }
        }
    };
}

