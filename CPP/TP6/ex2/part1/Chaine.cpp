#include "Chaine.hpp"

Chaine::Chaine():
	_capa(-1),_tab(nullptr)
{
}

Chaine::Chaine(const int taille):
	_capa(taille > 0 ? taille : 0)
{
	if (_capa)
	{
		_tab = new char [_capa];
		_tab[0] = 0;
	} else  _tab = nullptr;
}

Chaine::Chaine(const char * inCs):
	Chaine(strlen(inCs))
{
	delete[] _tab;
	_tab = new char[_capa];
	strcpy(_tab, inCs);
}

Chaine::Chaine(const Chaine& chaine):
	Chaine(chaine.getCapacite())
{
	if (_tab != nullptr)
	{
		strcpy(_tab, chaine.c_str());
	}

	std::clog << "Constructeur de copie appelé " << std::endl;
}

Chaine::~Chaine()
{
	delete[] _tab;
}

char * Chaine::c_str() const
{
	return _tab;
}

int Chaine::getCapacite() const
{
	return _capa;
}

void Chaine::afficher(std::ostream & stream) const
{
	stream << c_str();
}

Chaine& Chaine::operator=(const Chaine& c)
{
	delete[] _tab; // Suppression de l'ancien str.

	_capa = c._capa; // Mise en place de la nouvelle taille.
	_tab = new char[_capa]; // Allocation du nouveau char*.
	strcpy(_tab, c._tab); // Copie du str vers le char* créé.

	return *this; // Renvoie de la nouvelle valeur.
}

char& Chaine::operator[](const int & i)
{
	if(_tab == nullptr)
		throw Null_pointer("Erreur");
	else if (i < 0)
		throw std::out_of_range("indice inférieur à 0");
	else if (i > _capa)
		throw std::bad_alloc();
	return _tab[i];
}

char& Chaine::operator[](const int & i) const
{
	return _tab[i];
}

std::ostream& operator<<(std::ostream& os, const Chaine &c)
{
	for (int i = 0; i < c.getCapacite(); ++i)
		os << c[i];
	return os;
}

Chaine operator+(const Chaine& c1, const Chaine& c2)
{
	Chaine c(strlen(c1.c_str()) + strlen(c2.c_str()) - 1);

	strcpy(c._tab, c1.c_str());
	strcpy(c._tab + strlen(c._tab), c2.c_str());
	return c;
}

void Chaine::afficherParValeur(Chaine c)
{
	c.afficher();
}

void Chaine::afficherParReference(Chaine& c)
{
	c.afficher();
}