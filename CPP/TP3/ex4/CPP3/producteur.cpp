#include "producteur.hpp"
#include <fstream>

Producteur::Producteur():travail(0)
{
}

int Producteur::getTravail()
{
	return travail;
}