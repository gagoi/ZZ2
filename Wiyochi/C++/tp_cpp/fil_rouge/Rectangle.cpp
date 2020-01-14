#include "Rectangle.hpp"

Rectangle::Rectangle() :
    Forme(0, 0, 0, 0)
{
}

Rectangle::Rectangle(int x, int y, int w, int h) :
    Forme(x, y, w, h)
{
}

std::string Rectangle::toString() const
{
    return "RECTANGLE " + std::to_string(getId()) + "(" + std::to_string(_origin.getX()) + "," + std::to_string(_origin.getY()) + "," + std::to_string(_width) + "," + std::to_string(_height) + ")";
}

Rectangle* Rectangle::clone() const
{
    return new Rectangle(*this);
}