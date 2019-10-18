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