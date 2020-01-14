// ConsoleApplication1.cpp : fichier projet principal.

#include "stdafx.h"
#include "form_main.h"
#include "hvrp.h"
#include <ctime>

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String ^> ^args)
{
	srand(time(0));
	Console::WriteLine(L"Hello World");

	t_instance * ptr_instance = new t_instance;
	t_instance& instance = *ptr_instance;

	charger_instance_coordonnees(instance, "HVRP13.txt");

	int tour_geant[nb_max_sommets];
	generer_tour_geant_alea(instance.nb_sommets, tour_geant);

	delete ptr_instance;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ConsoleApplication1::form_main main_form;
	Application::Run(%main_form);



	return 0;
}

