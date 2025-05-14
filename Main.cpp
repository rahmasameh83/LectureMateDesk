#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // ????? ???? ?? LoginForm
    LectureMateDesk::LoginForm^ form = gcnew LectureMateDesk::LoginForm();

    // ????? ??????
    Application::Run(form);

    return 0;
}
