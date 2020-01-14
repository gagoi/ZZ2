#include "Forme.hpp"

int Forme::nbFormes = 0;

Forme::Forme() :
    Forme(0, 0, 0, 0)
{
}

Forme::Forme(int x, int y, int w, int h) :
    _origin(x, y),
    _width(w),
    _height(h),
    _couleur(COULEURS::BLEU),
    _id(nbFormes),
    _display(true)
{
    nbFormes++;
}

Forme::Forme(Point p, COULEURS c) :
    _origin(p),
    _width(0),
    _height(0),
    _couleur(c),
    _id(nbFormes),
    _display(true)
{
    nbFormes++;
}

Forme::~Forme()
{
}

Point& Forme::getPoint()
{
    return _origin;
}

void Forme::setX(int x)
{
    _origin.setX(x);
}

void Forme::setY(int y)
{
    _origin.setY(y);
}

COULEURS Forme::getCouleur() const
{
    return _couleur;
}

void Forme::setCouleur(COULEURS c)
{
    _couleur = c;
}

int Forme::getId() const
{
    return _id;
}

void Forme::setLargeur(int w)
{
    _width = w;
}

void Forme::setHauteur(int h)
{
    _height = h;
}

int Forme::getLargeur() const
{
    return _width;
}

int Forme::getHauteur() const
{
    return _height;
}

int Forme::prochainId()
{
    return nbFormes;
}

void Forme::setDisplay(bool d)
{
    _display = d;
}

bool Forme::getDisplay() const
{
    return _display;
}