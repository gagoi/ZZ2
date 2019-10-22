#include "Forme.hpp"

int Forme::nbFormes = 0;

Forme::Forme():Forme(ORIGINE, 0, 0)
{
}

Forme::Forme(Point p, COULEURS c):Forme(p, 0, 0)
{
	setCouleur(c);
}

Forme::Forme(const Point& p, int w, int h):
	_p(p), _w(w), _h(h), _couleur(COULEURS::BLEU), _id(nbFormes)
{
	nbFormes++;
}

Forme::Forme(const Forme& f):Forme(f.getPoint(),f.getLargeur(), f.getHauteur())
{
}

Forme::~Forme()
{

}

int Forme::prochainId()
{
	return nbFormes;
}

Point Forme::getPoint() const
{
	return _p;
}

COULEURS Forme::getCouleur() const
{
	return _couleur;
}

int Forme::getId() const
{
	return _id;
}

void Forme::setCouleur(COULEURS coleur)
{
	_couleur = coleur;
}

void Forme::setX(int x)
{
	_p.setX(x);
}

void Forme::setY(int y)
{
	_p.setY(y);
}


int Forme::getHauteur() const
{
	return _h;
}

int Forme::getLargeur() const
{
	return _w;
}

std::string Forme::toString() const
{
	std::ostringstream oss;
	oss << "Forme " << _p.getX() << ' ' << _p.getY() << ' ' << _w << ' ' << _h;
	return oss.str();
}

Forme* Forme::clone() const
{
	Forme * f = new Forme(this->getPoint(), this->_couleur);
	nbFormes++;
	return f;
}