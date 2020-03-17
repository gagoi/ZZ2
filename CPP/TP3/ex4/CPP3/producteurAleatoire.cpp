#include "producteurAleatoire.hpp"
#include <fstream>

bool ProducteurAleatoire::produire(int quantite, std::string nom)
{
	std::ofstream f(nom.c_str());
	if(f)
	{
		travail++;
		f << quantite;
		for (int i = 1; i <= quantite; ++i)
			f << std::endl << rand();
		f.close();
		return true;
	} else 
	{
		return false;
	}
}