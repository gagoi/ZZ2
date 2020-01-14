#include "MyForm.h"

#include <Windows.h>

using namespace Project1; // This is your project name

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew form_main());

	return 0;

}