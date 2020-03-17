#include "Rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(int x, int y, int w, int h, int type):Forme(Point(x, y), w, h)
{
	if (type != SIZE)
	{
		_w -= x;
		_h -= y;
	}
}

std::string Rectangle::toString() const
{
	std::ostringstream oss;
	oss << "RECTANGLE " << _p.getX() << ' ' << _p.getY() << ' ' << _w << ' ' << _h;
	return oss.str();
}

Rectangle* Rectangle::clone() const
{
	Rectangle * r = new Rectangle;
	r->_couleur = _couleur;
	r->_h = _h;
	r->_w = _w;
	r->setX(getPoint().getX());
	r->setY(getPoint().getY());
	nbFormes++;
	return r;
}