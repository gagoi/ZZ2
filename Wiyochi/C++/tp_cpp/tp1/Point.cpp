#include "Point.hpp"

int Point::compteur = 0;

Point::Point() :
    Point(0, 0)
{
}

Point::Point(int nX, int nY) :
    x(nX),
    y(nY)
{
    compteur += 1;
}

Point::~Point()
{
}

int Point::getX()
{
    return x;
}

void Point::setX(int nX)
{
    x = nX;
}

int Point::getY()
{
    return y;
}

void Point::setY(int nY)
{
    y = nY;
}

void Point::deplacerDe(int dX, int dY)
{
    x += dX;
    y += dY;
}

void Point::deplacerVers(int nX, int nY)
{
    x = nX;
    y = nY;
}

int Point::nombreDePoints()
{
    // x = 40; <- impossible, x est un attribut non static donc inaccessible depuis une méthode de classe
    return compteur;
}

std::ostream& operator<<(std::ostream& out, Point& p)
{
    out << "(";
    out << p.getX();
    out << ",";
    out << p.getY();
    out << ")";
    return out;
}