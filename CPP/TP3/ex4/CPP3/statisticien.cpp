#include "statisticien.hpp"

Statisticien::Statisticien():calcul(false), _somme(0)
{
}

void Statisticien::acquerir(std::string nom) {
	std::ifstream f(nom.c_str());

	if (f)
	{
		calcul = true;
		int nb(0);
		int tmp(0);
		int moyenne(0);
		f >> nb;
		for (int i = 0; i < nb; ++i)
		{
			f >> tmp;
			_somme += tmp;
		}
		moyenne = _somme/nb;
		std::cout << "La moyenne est : " << moyenne << std::endl;
		f.close();
	}
}

bool Statisticien::aCalcule()
{
	return calcul;
}

int Statisticien::somme()
{
	return _somme;
}