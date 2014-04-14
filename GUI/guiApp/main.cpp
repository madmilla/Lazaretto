#include "MyForm.h"
/**
## Autor Daan Joling.
## - Original setup.
## Author Lars Veenendaal
## - Added WinMain for releasemode.
## - WinMain is needed by the Linker.
*/
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	guiApp::MyForm form;
	Application::Run(%form);
	return 0;
}
INT Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	guiApp::MyForm form;
	Application::Run(%form);
	return 0;
}