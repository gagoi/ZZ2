#include "Cercle.hpp"

Cercle::Cercle() :
    Forme(0, 0, 0, 0)
{
}

Cercle::Cercle(int x, int y, int w, int h) :
    Forme(x, y, w, h)
{
}

Cercle::Cercle(int x, int y, int rayon) :
    Forme(x - rayon, y - rayon, 2*rayon, 2*rayon)
{
}

void Cercle::setRayon(int r)
{
    int x = getPoint().getX() + getRayon();
    int y = getPoint().getY() + getRayon();

    setX(x - r);
    setY(y - r);
    setLargeur(2 * r);
    setHauteur(2 * r);
}

int Cercle::getRayon() const
{
    return getLargeur() / 2;
}

std::string Cercle::toString() const
{
    return "CERCLE " + std::to_string(getId()) + "(" + std::to_string(_origin.getX()) + "," + std::to_string(_origin.getY()) + "," + std::to_string(_width) + "," + std::to_string(_height) + ")";
}

Cercle* Cercle::clone() const
{
    return new Cercle(*this);
}