// ConsoleApplication1.cpp : fichier projet principal.

#include "stdafx.h"
#include "form_main.h"
#include "job_shop.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Hello World");

	t_instance instance;
	t_solution solution;
	lire_fichier("testcours.txt", instance);

	//generer_vb(solution, instance);
	solution.taille = 9;
	solution.vb[0] = 1;
	solution.vb[1] = 2;
	solution.vb[2] = 2;
	solution.vb[3] = 1;
	solution.vb[4] = 1;
	solution.vb[5] = 3;
	solution.vb[6] = 3;
	solution.vb[7] = 3;
	solution.vb[8] = 2;

	evaluer(solution, instance);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ConsoleApplication1::form_main main_form;
	Application::Run(%main_form);



	return 0;
}

