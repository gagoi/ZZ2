#include "Cercle.hpp"

#include <iostream>
#include <sstream>

Cercle::Cercle(int x, int y, int w, int h):Forme(Point(x, y), w, h)
{
	_r = (w - x) /2;
}

Cercle::Cercle(const Point& point, int w, int h):Forme(point, w, h)
{
	_r = (w - point.getX()) / 2;
}

Cercle::Cercle(const Point& p, int r):Forme(p , r*2, r*2)
{
	_r = r;
	_p.setX(p.getX() - r);
	_p.setY(p.getY() - r);
}

Cercle::Cercle(int x, int y, int r):Forme(Point((x - r), (y - r)), 2 * r, 2 * r)
{
	_r = r;
}

std::string Cercle::toString() const
{
	std::ostringstream oss;
	oss << "CERCLE " << _p.getX() << ' ' << _p.getY() << ' ' << _r;
	return oss.str();
}

int Cercle::getRayon() const
{
	return _r;
}

void Cercle::setRayon(int r)
{
	getPoint().setX(getPoint().getX() + getRayon());
	getPoint().setY(getPoint().getY() + getRayon());
	_w = 2*r;
	_h = 2*r;
	_r = r;
}