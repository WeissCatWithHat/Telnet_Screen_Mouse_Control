#include "stdafx.h"
#include "MyForm.h"

using namespace TelnetClient;
using namespace System;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	
	Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyForm());
	
	return 0;
}
