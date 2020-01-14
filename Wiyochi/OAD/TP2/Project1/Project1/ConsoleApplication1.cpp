// ConsoleApplication1.cpp : fichier projet principal.

#include "stdafx.h"
#include "MyForm.h"
/*
#include "form_main.h"
#include "job_shop.h"
*/
using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Hello World");

	//t_instance instance;
	//lire_fichier("LA01.txt", instance);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project1::form_main main_form;
	Application::Run(%main_form);



	return 0;
}

