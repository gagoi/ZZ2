#include "Point.hpp"

Point ORIGINE(0, 0);

Point::Point() :
    Point(0, 0)
{
}

Point::Point(int x, int y) :
    _x(x),
    _y(y)
{
}

Point::~Point()
{
}

int Point::getX() const
{
    return _x;
}

int Point::getY() const
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}