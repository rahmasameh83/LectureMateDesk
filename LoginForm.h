#pragma once
#include "DashboardForm.h"
#include "StudentDashboard.h"


namespace LectureMateDesk {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
		}

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		PictureBox^ bannerPictureBox;
		Label^ usernameLabel;
		TextBox^ usernameTextBox;
		Label^ passwordLabel;
		TextBox^ passwordTextBox;
		Label^ roleLabel;
		ComboBox^ roleComboBox;
		Button^ loginButton;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();

			// Form settings
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Text = L"Login - LectureMateDesk";
			this->BackColor = Color::FromArgb(245, 245, 245);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;

			// PictureBox (Banner)
			bannerPictureBox = gcnew PictureBox();
			bannerPictureBox->Image = Image::FromFile(Application::StartupPath + "\\Computer login-amico (3).png");
			bannerPictureBox->Location = Point(100, 20);
			bannerPictureBox->Size = Drawing::Size(300, 200);
			bannerPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
			this->Controls->Add(bannerPictureBox);

			// Username Label
			usernameLabel = gcnew Label();
			usernameLabel->Text = L"Username:";
			usernameLabel->Location = Point(100, 240);
			usernameLabel->AutoSize = true;
			this->Controls->Add(usernameLabel);

			// Username TextBox
			usernameTextBox = gcnew TextBox();
			usernameTextBox->Location = Point(100, 260);
			usernameTextBox->Width = 300;
			this->Controls->Add(usernameTextBox);

			// Password Label
			passwordLabel = gcnew Label();
			passwordLabel->Text = L"Password:";
			passwordLabel->Location = Point(100, 290);
			passwordLabel->AutoSize = true;
			this->Controls->Add(passwordLabel);

			// Password TextBox
			passwordTextBox = gcnew TextBox();
			passwordTextBox->Location = Point(100, 310);
			passwordTextBox->Width = 300;
			passwordTextBox->UseSystemPasswordChar = true;
			this->Controls->Add(passwordTextBox);

			// Role Label
			roleLabel = gcnew Label();
			roleLabel->Text = L"Role:";
			roleLabel->Location = Point(100, 340);
			roleLabel->AutoSize = true;
			this->Controls->Add(roleLabel);

			// Role ComboBox
			roleComboBox = gcnew ComboBox();
			roleComboBox->Location = Point(100, 360);
			roleComboBox->Width = 300;
			roleComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
			roleComboBox->Items->AddRange(gcnew array<Object^> { L"Doctor", L"Student" });
			this->Controls->Add(roleComboBox);

			// Login Button
			loginButton = gcnew Button();
			loginButton->Text = L"Login";
			loginButton->Location = Point(100, 410);
			loginButton->Width = 300;
			loginButton->BackColor = Color::FromArgb(0, 120, 215);
			loginButton->ForeColor = Color::White;
			loginButton->FlatStyle = FlatStyle::Flat;
			loginButton->Click += gcnew EventHandler(this, &LoginForm::LoginButton_Click);
			this->Controls->Add(loginButton);

			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		void LoginButton_Click(Object^ sender, EventArgs^ e)
		{
			String^ username = usernameTextBox->Text;
			String^ password = passwordTextBox->Text;
			String^ role = roleComboBox->Text;

			if ((username == "Rahma" && password == "123" && role == "Doctor") ||
				(username == "Student1" && password == "123" && role == "Student"))
			{
				this->Hide();

				if (role == "Doctor")
				{
					DashboardForm^ dashboard = gcnew DashboardForm();
					dashboard->ShowDialog();
				}
				else if (role == "Student")
				{
					StudentDashboard^ studentDash = gcnew StudentDashboard();
					studentDash->ShowDialog();
				}
				 
				this->Close();
			}
			else
			{
				MessageBox::Show(L"Invalid credentials or role!");
			}
		}

	};
}
