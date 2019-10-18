#include "Groupe.hpp"
Groupe::Groupe(): Forme(ORIGINE, 0, 0)
{
    _nbFormes = 0;
}

void Groupe::ajouterForme(Forme& f)
{
	if (_nbFormes < size)
	{
        if (f.getPoint().getX() < getPoint().getX()) setX(f.getPoint().getX());
        if (f.getPoint().getY() < getPoint().getY()) setY(f.getPoint().getY());
        if (f.getLargeur() + f.getPoint().getX() > getLargeur() + getPoint().getX()) _w = f.getLargeur() + f.getPoint().getX();
        if (f.getHauteur() + f.getPoint().getY() > getHauteur() + getPoint().getY()) _h = f.getHauteur() + f.getPoint().getY();
		_formes[_nbFormes] = &f;
		_nbFormes++;
	}
}

void Groupe::afficher()
{
	for (unsigned int i = 0; i < _nbFormes; ++i)
	{
		std::cout << _formes[i]->toString() << std::endl;
	}	
}

Groupe::~Groupe()
{
}

std::string Groupe::toString() const
{
	std::ostringstream oss;
	oss << "GROUPE " << _p.getX() << ' ' << _p.getY() << ' ' << _w << ' ' << _h;
	return oss.str();
}