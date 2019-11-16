#include "Groupe.hpp"
Groupe::Groupe(): Forme(ORIGINE, 0, 0)
{
	nbFormes++;
}
/*
Groupe::Groupe(Groupe& g): Groupe()
{
	this->setX(g.getPoint().getX());
	this->setY(g.getPoint().getY());
	memcpy(this->_formes, g._formes, nbFormes * sizeof(Forme*));
}
*/
void Groupe::ajouterForme(Forme& f)
{
	if (f.getPoint().getX() < getPoint().getX()) setX(f.getPoint().getX());
	if (f.getPoint().getY() < getPoint().getY()) setY(f.getPoint().getY());
	if (f.getLargeur() + f.getPoint().getX() > getLargeur() + getPoint().getX()) _w = f.getLargeur() + f.getPoint().getX();
	if (f.getHauteur() + f.getPoint().getY() > getHauteur() + getPoint().getY()) _h = f.getHauteur() + f.getPoint().getY();
	_formes.push_back(&f);
}

void Groupe::afficher()
{
	for (auto f : _formes)
		std::cout << f->toString()  << "(" << f << ")" << std::endl;
}

Groupe::~Groupe()
{
	for (auto f : _formes)
		delete f;
	//for (int i = 0; i < _nbFormes; ++i)
	//	delete _formes[i];
}

std::string Groupe::toString() const
{
	std::ostringstream oss;
	oss << "GROUPE " << _p.getX() << ' ' << _p.getY() << ' ' << _w << ' ' << _h << ' ' << nbFormes << " { ";
	for (auto f : _formes)
		oss << f->toString() << "; ";
	oss << "}";
	return oss.str();
}

Groupe* Groupe::clone() const
{
	Groupe * g = new Groupe;
	std::copy(_formes.begin(), _formes.end(), g->_formes.begin());

	std::cout << "cloné" << std::endl;
	nbFormes++;
	return g;
}